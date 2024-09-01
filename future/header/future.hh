#include <aligned_buffer.hh>

#include <coroutine>
#include <functional>
#include <memory>
#include <concepts>
#include <mutex>
#include <condition_variable>

namespace flp {

template<typename Type>
struct Promise;

template<typename Type>
struct SharedStateBase {
  AlignedBuffer<Type> buffer;
  bool initialized = false;
  std::exception_ptr exception;
  std::once_flag set_flag;
  std::mutex mutex;
  std::condition_variable ready_condition;
  std::function<void(Type)> continuation;

  SharedStateBase() = default;

  // what to do with the exception???
  SharedStateBase(const SharedStateBase& other)
  requires std::copy_constructible<Type> {
    buffer.get() = other.buffer.get();
    // set flag afterward, in case the above copy throws
    initialized = true;
  }

  // what to do with the exception???
  SharedStateBase& operator=(const SharedStateBase& other)
  requires std::copy_constructible<Type> {
    buffer.get() = other.buffer.get();
    // set flag afterward, in case the above copy throws
    initialized = true;

    return *this;
  }

  SharedStateBase(SharedStateBase&& other) noexcept
  requires std::move_constructible<Type> {
    buffer.get() = std::move(other.get());
    exception = std::move(other.exception);
    initialized = true;
    other.initialized = false;
  }

  SharedStateBase& operator=(SharedStateBase&& other) noexcept
  requires std::move_constructible<Type> {
    buffer.get() = std::move(other.get());
    exception = std::move(other.exception);
    initialized = true;
    other.initialized = false;

    return *this;
  }

  ~SharedStateBase() {
    if (initialized) {
      buffer.destruct();
    }
  }

  void set(const Type& value)
  requires std::copy_constructible<Type> {
    std::call_once(set_flag, static_cast<void(SharedStateBase::*)(const Type&)>(&SharedStateBase::do_set), this, value);
  }

  void set(Type&& value)
  requires std::move_constructible<Type> {
    std::call_once(set_flag, static_cast<void(SharedStateBase::*)(Type&&)>(&SharedStateBase::do_set), this, std::move(value));
  }

  void set(std::exception_ptr ep) {
    std::call_once(set_flag, static_cast<void(SharedStateBase::*)(std::exception_ptr)>(&SharedStateBase::do_set), this, std::move(ep));
  }

private:
  void do_set(const Type& value) {
    buffer.get() = value;
    initialized = true;
    ready_condition.notify_all();
    if (continuation) {
      continuation(buffer.get());
      // clear it out; it may free resources bound up in a lambda or something
      continuation = std::function<void(Type)>();
    }
  }

  void do_set(Type&& value) {
    buffer.get() = std::move(value);
    initialized = true;
    ready_condition.notify_all();
    if (continuation) {
      continuation(buffer.get());
      // clear it out; it may free resources bound up in a lambda or something
      continuation = std::function<void(Type)>();
    }
  }

  void do_set(std::exception_ptr ep) {
    exception = std::move(ep);
    ready_condition.notify_all();
    // clear it out; it may free resources bound up in a lambda or something
    continuation = std::function<void(Type)>();
  }
};

/* Multiple continuations?
 * how should that be managed...
 * raises questions about future ownership/shared_future etc
 * https://youtu.be/zULU6Hhp42w?si=_R4mO6XUeqDtbPNc&t=3520
 */
//! @TODO split/join
template<typename Type>
struct Future {
  template<typename Functor, typename ...Args>
  Future<std::invoke_result_t<std::decay_t<Functor>, std::decay_t<Type>, std::decay_t<Args>...>>
  then(Functor&& functor, Args&& ...args) {
    using ChainResult = std::invoke_result_t<std::decay_t<Functor>, std::decay_t<Type>, std::decay_t<Args>...>;
    if (ready()) {
      return {functor(get(), std::forward<Args>(args)...)};
    }

    auto then_state = std::make_shared<SharedStateBase<ChainResult>>();
    // copy/move semantics?
    state->continuation = [then_state, functor = std::move(functor), ...args = std::forward<Args>(args)](Type value) mutable {
      try {
        then_state->set(functor(value, std::forward<Args>(args)...));
      } catch(...) {
        then_state->set(std::current_exception());
      }
    };

    return {then_state};
  }

  // copy/move semantics?
  [[nodiscard]]
  Type get() {
    wait();
    if (state->exception != nullptr) {
      std::rethrow_exception(state->exception);
    }
    return state->buffer.get();
  }

  [[nodiscard]]
  bool valid() const noexcept {
    return state != nullptr;
  }

  [[nodiscard]]
  bool ready() const noexcept {
    return valid() and (state->initialized or state->exception != nullptr);
  }

  enum class TimeoutReason {
    StateInvalid,
    ValueReady,
    TimeExpired,
  };

  TimeoutReason wait() noexcept {
    std::unique_lock lk(state->mutex);
    state->ready_condition.wait(lk, [this]{ return not valid() or ready(); });

    return valid() ? TimeoutReason::ValueReady : TimeoutReason::StateInvalid;
  }

  /*TimeoutReason wait(duration) {
  }*/

private:
  template<typename Other>
  friend class Future;
  template<typename Other>
  friend class Promise;
  using State = std::shared_ptr<SharedStateBase<Type>>;

  Future(State initial_state) noexcept
      : state(std::move(initial_state))
  {}

  Future(const Type& value)
      : state(std::make_shared<SharedStateBase<Type>>())
  {
    state->set(value);
  }
  Future(Type&& value)
      : state(std::make_shared<SharedStateBase<Type>>())
  {
    state->set(std::move(value));
  }

  State state;
};

template<typename Type>
struct Promise {
  Promise()
      : state(std::make_shared<SharedStateBase<Type>>())
  {}
  // only one source can hold or fulfill a promise
  Promise(const Promise&) = delete;
  Promise& operator=(const Promise&) = delete;
  Promise(Promise&&) noexcept = default;
  Promise& operator=(Promise&&) noexcept = default;
  ~Promise() noexcept = default;

  Future<Type> get_future() const noexcept {
    return {state};
  }

  // value/exception can only ever be set once

  void set_value(const Type& value) {
    state->set(value);
  }

  void set_value(Type&& value) {
    state->set(std::move(value));
  }

  void set_exception(std::exception_ptr ep) {
    state->set(std::move(ep));
  }

  // at thread exit operations?

private:
  using State = std::shared_ptr<SharedStateBase<Type>>;

  State state;
};

template<typename Type>
struct PackagedTask {
};

// create a continuation based one
// this will:
// allow control of what execution context something runs on
// enables integration with asio
// prevents 'excessive' creation of threads
template<typename Functor, typename ...Args>
[[nodiscard]]
Future<std::invoke_result_t<std::decay_t<Functor>, std::decay_t<Args>...>>
async(Functor&& functor, Args&& ...args) {
  using Type = std::invoke_result_t<std::decay_t<Functor>, std::decay_t<Args>...>;
  Promise<Type> promise;
  auto future = promise.get_future();
  std::thread t([promise = std::move(promise), function = std::forward<Functor>(functor), ...args = std::forward<Args>(args)] mutable {
      try {
          promise.set_value(function(std::forward<Args>(args)...));
      } catch(...) {
          promise.set_exception(std::current_exception());
      }
  });
  t.detach();
  return future;
}

}
