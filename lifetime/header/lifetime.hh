#include <print>
#include <ranges>
#include <source_location>

namespace flp {

void print(std::source_location location = std::source_location::current()) {
  std::println("{}", location.function_name());
}

template<typename Type>
void print(const Type& value, std::source_location location = std::source_location::current()) {
  std::println("{}\t{}", value, location.function_name());
}

template<typename Type1, typename Type2>
void print(const Type1& value1, const Type2& value2, std::source_location location = std::source_location::current()) {
  std::println("{}->{}\t{}", value1, value2, location.function_name());
}

struct Lifetime {
  static inline size_t ID_Counter = 0;
  size_t               ID         = ++ID_Counter;

  Lifetime() {
    print(ID);
  }
  Lifetime(const Lifetime& other) {
    print(other.ID, ID);
  }
  Lifetime(Lifetime&& other) noexcept
    : ID(other.ID) {
    print(ID);
  }
  Lifetime& operator=(const Lifetime& other) {
    print(other.ID, ID);
    return *this;
  }
  Lifetime& operator=(Lifetime&& other) noexcept {
    print(other.ID, ID);
    ID = other.ID;
    return *this;
  }
  ~Lifetime() noexcept {
    print(ID);
  }
};

} // namespace flp

namespace std {
template<>
struct allocator<flp::Lifetime> {
  using value_type = flp::Lifetime;
  [[nodiscard]]
  constexpr flp::Lifetime* allocate(size_t n) {
    flp::print(n);
    return reinterpret_cast<flp::Lifetime*>(new (align_val_t(alignof(flp::Lifetime))) char[n * sizeof(flp::Lifetime)]);
  }
  void deallocate(flp::Lifetime* t, size_t n) {
    flp::print(n);
    delete[] (reinterpret_cast<char*>(t));
  }
};

} // namespace std
