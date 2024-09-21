#pragma once

#include <condition_variable>
#include <deque>
#include <memory>
#include <optional>
#include <queue>

namespace flp {
template<typename Type, typename Product>
concept Producer = requires (Type t, Product p) {
  {t.push(p)} -> std::convertible_to<bool>;
};

template<typename Type, typename Product>
concept Consumer = requires (Type t, Product p) {
  {t.pop()} -> std::same_as<std::optional<Product>>;
};

template<typename Type, typename Product>
concept Store =
        Producer<Type, Product>
    and Consumer<Type, Product>
    and requires (Type t, const Type ct, Product p) {
  {t.shutdown()};

  {ct.running()} -> std::convertible_to<bool>;
  {ct.empty()} -> std::convertible_to<bool>;
  {ct.size()} -> std::convertible_to<size_t>;
};

template<typename Type, typename Product>
concept Storage = requires(const Type t) {
  {t.empty()} -> std::convertible_to<bool>;
  {t.size()} -> std::convertible_to<bool>;
};

template<typename Type, typename Product>
concept ProducerSpawner = requires(Type t) {
  {t.spawn()} -> Producer<Product>;
};

template<typename Type, typename Product>
concept ConsumerSpawner = requires(Type t) {
  {t.spawn()} -> Consumer<Product>;
};

template<typename Product, Storage<Product> Storage_t = std::deque<Product>>
struct SimpleStore_st {
private:
  Storage_t storage;
  bool shutting_down = false;

public:
  SimpleStore_st() = default;
  SimpleStore_st(const SimpleStore_st&) = default;
  SimpleStore_st(SimpleStore_st&&) noexcept = default;
  SimpleStore_st& operator=(const SimpleStore_st&) = default;
  SimpleStore_st& operator=(SimpleStore_st&&) noexcept = default;
  ~SimpleStore_st() {
    shutdown();
  }

  bool push(const Product& product) {
    storage.push_back(product);
    return true;
  }

  bool push(Product&& product) {
    storage.push_back(std::move(product));
    return true;
  }

  template<typename ...Args>
  bool emplace(Args&& ...args) {
    storage.emplace_back(std::forward<Args>(args)...);
    return true;
  }

  std::optional<Product> pop() {
    std::optional<Product> result;

    if (storage.empty()) {
      return std::nullopt;
    }

    result = std::move(storage.front());
    storage.pop_front();

    return result;
  }

  void shutdown() {
    shutting_down = true;
  }

  [[nodiscard]]
  bool running() const noexcept {
    return !shutting_down;
  }

  [[nodiscard]]
  bool empty() const {
    return storage.empty();
  }

  [[nodiscard]]
  size_t size() const {
    return storage.size();
  }
};
// just use int as a quick test case
static_assert(Store<SimpleStore_st<int>, int>);

template<typename Product, Storage<Product> Storage_t = std::deque<Product>>
struct SimpleStore_mt {
private:
  Storage_t storage;
  std::mutex mutex;
  std::condition_variable empty_condition;
  std::condition_variable full_condition;
  size_t max_size{8192};
  volatile bool shutting_down = false;

public:
  SimpleStore_mt() = default;
  SimpleStore_mt(const SimpleStore_mt&) = delete;
  SimpleStore_mt(SimpleStore_mt&&) noexcept = default;
  SimpleStore_mt& operator=(const SimpleStore_mt&) = delete;
  SimpleStore_mt& operator=(SimpleStore_mt&&) noexcept = default;
  ~SimpleStore_mt() {
    shutdown();
  }

  explicit
  SimpleStore_mt(size_t max)
    : max_size(max) {}

  explicit
  SimpleStore_mt(Storage_t initial_store)
    : storage(initial_store) {}

  bool push(const Product& product) {
    if (shutting_down) {
      return false;
    }

    std::unique_lock lock(mutex);

    if (storage.size() >= max_size) {
      full_condition.wait(lock, [this] {
        return storage.size() < max_size or shutting_down;
      });

      if (shutting_down) {
        return false;
      }
    }

    storage.push_back(product);

    empty_condition.notify_one();

    return true;
  }

  std::optional<Product> pop() {
    if (shutting_down) {
      return std::nullopt;
    }

    std::unique_lock lock(mutex);

    std::optional<Product> result;

    if (storage.empty()) {
      empty_condition.wait(lock, [this] {
        return not storage.empty() or shutting_down;
      });

      if (shutting_down) {
        return std::nullopt;
      }
    }

    result = std::move(storage.front());
    storage.pop_front();

    full_condition.notify_one();

    return result;
  }

  void shutdown() {
    std::unique_lock lock(mutex);
    shutting_down = true;
    full_condition.notify_all();
    empty_condition.notify_all();
  }

  [[nodiscard]]
  bool running() const noexcept {
    return !shutting_down;
  }

  [[nodiscard]]
  bool empty() const {
    return storage.empty();
  }

  [[nodiscard]]
  size_t size() const {
    return storage.size();
  }
};
// just use int as a quick test case
static_assert(Store<SimpleStore_mt<int>, int>);

template<typename Product, Store<Product> StoreType, Storage<Product> Storage_t = std::deque<Product>>
struct StoreWrapper {
  std::shared_ptr<StoreType> store;

  explicit
  StoreWrapper(std::shared_ptr<StoreType> initial_store)
    : store(std::move(initial_store)) {}
  StoreWrapper(const StoreWrapper&) = default;
  StoreWrapper(StoreWrapper&&) noexcept = default;
  StoreWrapper& operator=(const StoreWrapper&) = default;
  StoreWrapper& operator=(StoreWrapper&&) noexcept = default;
  ~StoreWrapper() noexcept = default;

  bool push(const Product& product) {
    return store->push(product);
  }

  std::optional<Product> pop() {
    return store->pop();
  }

  void shutdown() {
    store->shutdown();
  }

  [[nodiscard]]
  bool running() const noexcept {
    return store->running();
  }

  [[nodiscard]]
  bool empty() const {
    return store->empty();
  }

  [[nodiscard]]
  size_t size() const {
    return store->size();
  }
};
static_assert(Store<StoreWrapper<int, SimpleStore_st<int>>, int>);
static_assert(Store<StoreWrapper<int, SimpleStore_mt<int>>, int>);

template<typename Product, Store<Product> Store, typename SpawnedType>
struct SimpleSpawner{
  std::shared_ptr<Store> store;

  SpawnedType spawn() {
    return SpawnedType{store};
  }
};

template<typename Product, Store<Product> Store, Producer<Product> ProducerType>
using SimpleProducerSpawner = SimpleSpawner<Product, Store, ProducerType>;
//static_assert(Spawner<SimpleProducerSpawner<int...>);
template<typename Product, Store<Product> Store, Consumer<Product> ConsumerType>
using SimpleConsumerSpawner = SimpleSpawner<Product, Store, ConsumerType>;
//static_assert(Spawner<SimpleProducerSpawner<int...>);

template<typename Product>
using PriorityStore_st = SimpleStore_st<Product, std::priority_queue<Product, std::vector<Product>, std::less<>>>;

template<typename Product,
         Store<Product> SType,
         ProducerSpawner<Product> PSpawner = SimpleProducerSpawner<Product, SType, StoreWrapper<Product, SType>>,
         ConsumerSpawner<Product> CSpawner = SimpleConsumerSpawner<Product, SType, StoreWrapper<Product, SType>>,
         typename ...Args>
std::pair<PSpawner, CSpawner> create_mpmc(Args&& ...args) {
  auto store = std::make_shared<SType>(std::forward<Args>(args)...);

  return {PSpawner{store}, CSpawner{store}};
}

template<typename Product,
         Store<Product> SType = SimpleStore_mt<Product>,
         Producer<Product> PType = StoreWrapper<Product, SType>,
         Consumer<Product> CType = StoreWrapper<Product, SType>,
         typename ...Args>
std::pair<PType, CType> create_spsc(Args&& ...args) {
  auto [producer_spawner, consumer_spawner] = create_mpmc<Product, SType>(std::forward<Args>(args)...);
  return std::make_pair(producer_spawner.spawn(), consumer_spawner.spawn());
}
}
