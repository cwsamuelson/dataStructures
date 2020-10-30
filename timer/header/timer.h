#ifndef __TIMER_H__
#define __TIMER_H__

#include<functional>
#include<thread>
#include<future>
#include <condition_variable>

namespace gsw {

class TimerCancelled : public std::runtime_error{
public:
  TimerCancelled()
    : std::runtime_error("Timer was cancelled before it completed, and before delayed action could be taken.")
  {}
};

/*! Timer facility for delayed and scheduled function calls
 *
 * @todo see notes in cppreference async about multiple sequential async calls
 * @todo might be nice to have a cancel per event, so that I can schedule 2 events, and cancel them independently
 * this might actually call for factory pattern, where timers are created by the factory, and the only method
 * on timer is just cancel, or maybe a 'time until' counter
 */
template<typename T>
class timer {
private:
  bool mCancel = false;
  std::mutex mMutex;
  std::condition_variable mConVar;
  std::shared_future<T> mFuture;

  template<typename clock, typename duration, typename callback_function>
  friend auto schedule_timer(const std::chrono::time_point<clock, duration>&, callback_function);
  template<typename clock, typename duration>
  friend auto schedule_timer(const std::chrono::time_point<clock, duration>& tp);

  template<typename Rep, typename Period, typename callback_function>
  friend auto schedule_timer(const std::chrono::duration<Rep, Period>&, callback_function);
  template<typename Rep, typename Period>
  friend auto schedule_timer(const std::chrono::duration<Rep, Period>& d);

public:
  using callback = std::function<T()>;

  template<typename clock, typename duration, typename signature>
  explicit
  timer(const std::chrono::time_point<clock, duration>& time, signature fn)
    : mCancel(false){

    auto f = std::async(std::launch::async, [this, fn = std::move(fn), time]()
      {
        std::unique_lock lk(mMutex);
        if(!mConVar.wait_until(lk, time, [this]()
          {
            return mCancel;
          })) {
          return fn();
        } else {
          throw TimerCancelled();
        }
      });

    mFuture = f.share();
  }

  auto future() const noexcept{
    return mFuture;
  }

  void cancel() noexcept{
    mCancel = true;
    mConVar.notify_all();
  }

  void wait() const{
    mFuture.wait();
  }

  auto get() const{
    return mFuture.get();
  }
};

template<typename clock, typename duration, typename signature>
timer(const std::chrono::time_point<clock, duration>& time, signature fn) -> timer<decltype(fn())>;

template<typename clock, typename duration, typename callback_function>
auto schedule_timer(const std::chrono::time_point<clock, duration>& time, callback_function fn){
  return timer(time, fn);
}

template<typename Rep, typename Period, typename callback_function>
auto schedule_timer(const std::chrono::duration<Rep, Period>& duration, callback_function fn){
  return timer(std::chrono::steady_clock::now() + duration, fn);
}

template<typename clock, typename duration>
auto schedule_timer(const std::chrono::time_point<clock, duration>& tp){
  return schedule_timer(tp, [](){});
}

template<typename Rep, typename Period>
auto schedule_timer(const std::chrono::duration<Rep, Period>& d){
  return schedule_timer(d, [](){});
}

}

#endif
