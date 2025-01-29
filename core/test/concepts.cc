#include <catch2/catch_all.hpp>

#include "core/concepts.hh"
#include "core/traits.hh"

#include <map>
#include <set>
#include <vector>

struct Capable {
  template<typename ...Args>
  explicit
  Capable(Args&&...) {}
  Capable() noexcept = default;
  Capable(const Capable&) noexcept = default;
  Capable(Capable&&) noexcept = default;
  Capable& operator=(const Capable&) noexcept = default;
  Capable& operator=(Capable&&) noexcept = default;
  ~Capable() noexcept = default;
};

struct Unusable {
  Unusable() = delete;
  Unusable(const Unusable&) = delete;
  Unusable(Unusable&&) = delete;
  Unusable& operator=(const Unusable&) = delete;
  Unusable& operator=(Unusable&&) = delete;
  ~Unusable() = delete;
};

template<bool NOTHROW>
struct CopyOnly {
  CopyOnly(const CopyOnly&) noexcept(NOTHROW) = default;
  CopyOnly& operator=(const CopyOnly&) noexcept(NOTHROW) = default;

  CopyOnly() = delete;
  CopyOnly(CopyOnly&&) = delete;
  CopyOnly& operator=(CopyOnly&&) = delete;
  ~CopyOnly() = delete;
};
using Copyable = CopyOnly<false>;
using NothrowCopyable = CopyOnly<true>;

template<bool NOTHROW>
struct MoveOnly {
  MoveOnly(MoveOnly&&) noexcept(NOTHROW) = default;
  MoveOnly& operator=(MoveOnly&&) noexcept(NOTHROW) = default;

  MoveOnly() = delete;
  MoveOnly(const MoveOnly&) = delete;
  MoveOnly& operator=(const MoveOnly&) = delete;
  ~MoveOnly() = delete;
};
using Movable = MoveOnly<false>;
using NothrowMovable = MoveOnly<true>;

struct DefaultConstructible {
  DefaultConstructible() = default;

  DefaultConstructible(const DefaultConstructible&) = delete;
  DefaultConstructible(DefaultConstructible&&) = delete;
  DefaultConstructible& operator=(const DefaultConstructible&) = delete;
  DefaultConstructible& operator=(DefaultConstructible&&) = delete;

  ~DefaultConstructible() = delete;
};

struct Empty{};

struct ArgsConstructible {
  explicit
  ArgsConstructible(int){}
  ArgsConstructible(int, int){}
  explicit
  ArgsConstructible(Empty){}

  ArgsConstructible(const ArgsConstructible&) = delete;
  ArgsConstructible(ArgsConstructible&&) = delete;
  ArgsConstructible& operator=(const ArgsConstructible&) = delete;
  ArgsConstructible& operator=(ArgsConstructible&&) = delete;
  ~ArgsConstructible() = delete;
};

struct TemplateConstructor {
  template<typename Type>
  explicit
  TemplateConstructor(Type) {}
  template<typename Type1, typename Type2>
  TemplateConstructor(Type1, Type2) {}
  template<typename ...Args>
  explicit
  TemplateConstructor(Args ...){}

  TemplateConstructor(const TemplateConstructor&) = delete;
  TemplateConstructor(TemplateConstructor&&) = delete;
  TemplateConstructor& operator=(const TemplateConstructor&) = delete;
  TemplateConstructor& operator=(TemplateConstructor&&) = delete;
  ~TemplateConstructor() = delete;
};

template<typename ...Args>
struct CTADConstructor {
  explicit
  CTADConstructor(Args&& ...) {}

  CTADConstructor(const CTADConstructor&) = delete;
  CTADConstructor(CTADConstructor&&) = delete;
  CTADConstructor& operator=(const CTADConstructor&) = delete;
  CTADConstructor& operator=(CTADConstructor&&) = delete;
  ~CTADConstructor() = delete;
};

TEST_CASE("Basis") {
  SECTION("Constructible") {
    SECTION("Can't construct an unusable type") {
      STATIC_CHECK(not flp::Constructible<Unusable>);
      STATIC_CHECK(not flp::Constructible<Unusable, int>);
      STATIC_CHECK(not flp::Constructible<Unusable, int, int>);
    }
    SECTION("Constructing a type with any valid constructor") {
      STATIC_CHECK(flp::Constructible<ArgsConstructible, int>);
      STATIC_CHECK(flp::Constructible<ArgsConstructible, int, int>);
      STATIC_CHECK(flp::Constructible<ArgsConstructible, Empty>);
      STATIC_CHECK(flp::Constructible<DefaultConstructible>);
      STATIC_CHECK(flp::Constructible<TemplateConstructor, int>);
      STATIC_CHECK(flp::Constructible<TemplateConstructor, int, int>);
      STATIC_CHECK(flp::Constructible<TemplateConstructor, int, int, int>);
      STATIC_CHECK(flp::Constructible<TemplateConstructor, int, int, int, int>);
      STATIC_CHECK(flp::Constructible<Capable>);
      STATIC_CHECK(flp::Constructible<Capable, int>);
      STATIC_CHECK(flp::Constructible<Capable, int, int>);
      STATIC_CHECK(flp::Constructible<Capable, Empty>);
      STATIC_CHECK(flp::Constructible<Capable, Capable>);
      // there's something wrong with this one; not sure what's going on
      //STATIC_CHECK(flp::Constructible<CTADConstructor<int, int, int, int>, int, int, int, int>);
    }
  }

  SECTION("Assignable") {
    SECTION("Can't assign an unusable type") {
      STATIC_CHECK(not flp::Assignable<Unusable, Unusable>);
      STATIC_CHECK(not flp::Assignable<Unusable, int>);
      STATIC_CHECK(not flp::Assignable<Unusable, float>);
      STATIC_CHECK(not flp::Assignable<Unusable, Empty>);
      STATIC_CHECK(not flp::Assignable<int, Unusable>);
      STATIC_CHECK(not flp::Assignable<float, Unusable>);
      STATIC_CHECK(not flp::Assignable<Empty, Unusable>);
    }

    SECTION("Copying") {
      STATIC_CHECK(flp::CopyAssignable<Copyable>);
      STATIC_CHECK(flp::CopyAssignable<NothrowCopyable>);
      STATIC_CHECK(flp::CopyAssignable<Capable>);
    }
    SECTION("Moving") {
      STATIC_CHECK(flp::MoveAssignable<Movable>);
      STATIC_CHECK(flp::MoveAssignable<NothrowMovable>);
      STATIC_CHECK(flp::MoveAssignable<Capable>);
    }
    SECTION("Convertible") {
      // in
      // out
    }
  }
}

TEST_CASE("Nothrow") {
}

template<typename>
struct Template {};

TEST_CASE("Is Specialization") {
  STATIC_CHECK(flp::IsSpecializationOf<Template<int>, Template>);
  STATIC_CHECK(not flp::IsSpecializationOf<int, Template>);
}

struct Boolean {
  operator bool(){ return true; }
};

TEST_CASE("BooleanTestable") {
  SECTION("BoolConstant") {
    STATIC_CHECK(flp::BooleanTestable<flp::BoolConstant<true>>);
    STATIC_CHECK(flp::BooleanTestable<flp::BoolConstant<false>>);
  }

  SECTION("bool") {
    STATIC_CHECK(flp::BooleanTestable<bool>);
  }

  SECTION("Boolean") {
    STATIC_CHECK(flp::BooleanTestable<Boolean>);
  }
}

template<typename>
struct AsymmetricallyComparable {
  template<typename T>
  bool operator==(const AsymmetricallyComparable<T>&) const {
    return true;
  }
};

TEST_CASE("EqualityComparableWith") {
  SECTION("Same Type") {
    STATIC_CHECK(flp::EqualityComparableWith<unsigned int, unsigned int>);
    STATIC_CHECK(flp::EqualityComparableWith<signed int, signed int>);
  }

  SECTION("Similar Types") {
    STATIC_CHECK(flp::EqualityComparableWith<unsigned int, signed int>);
    STATIC_CHECK(flp::EqualityComparableWith<signed int, unsigned int>);
  }

  SECTION("Different types") {
    STATIC_CHECK(flp::EqualityComparableWith<AsymmetricallyComparable<int>, AsymmetricallyComparable<float>>);
    STATIC_CHECK(flp::EqualityComparableWith<AsymmetricallyComparable<int>, AsymmetricallyComparable<struct X>>);
    STATIC_CHECK(flp::EqualityComparableWith<AsymmetricallyComparable<struct Y>, AsymmetricallyComparable<struct X>>);
  }
}

struct EqualityComparable {
  bool operator==(const EqualityComparable&) const { return true; }
};

TEST_CASE("EqualityComparable") {
  SECTION("By Value") {
    STATIC_CHECK(flp::EqualityComparable<int>);
    STATIC_CHECK(flp::EqualityComparable<float>);
    STATIC_CHECK(flp::EqualityComparable<EqualityComparable>);
  }

  SECTION("const") {
    STATIC_CHECK(flp::EqualityComparable<const int>);
    STATIC_CHECK(flp::EqualityComparable<const float>);
    STATIC_CHECK(flp::EqualityComparable<const EqualityComparable>);
  }

  SECTION("volatile") {
    STATIC_CHECK(flp::EqualityComparable<volatile int>);
    STATIC_CHECK(flp::EqualityComparable<volatile float>);
    // I don't want to put any hard requirement to handle volatility on user types
    //STATIC_CHECK(flp::EqualityComparable<volatile EqualityComparable>);
  }

  SECTION("pointer") {
    STATIC_CHECK(flp::EqualityComparable<int*>);
    STATIC_CHECK(flp::EqualityComparable<float*>);
    STATIC_CHECK(flp::EqualityComparable<EqualityComparable*>);
  }

  SECTION("reference") {
    STATIC_CHECK(flp::EqualityComparable<int&>);
    STATIC_CHECK(flp::EqualityComparable<float&>);
    STATIC_CHECK(flp::EqualityComparable<EqualityComparable&>);
  }
}

template<typename Type>
struct FancyPointer {
  Type& operator*() {
    static Type value{};
    return value;
  }

  const Type& operator*() const {
    static Type value{};
    return value;
  }
};

TEST_CASE("Dereferencable") {
  SECTION("pointers") {
    STATIC_CHECK(flp::Dereferencable<int*, int>);
    STATIC_CHECK(flp::Dereferencable<float*, float>);
    STATIC_CHECK(flp::Dereferencable<int*, int&>);
    STATIC_CHECK(flp::Dereferencable<float*, float&>);
  }

  SECTION("FancyPointer") {
    STATIC_CHECK(flp::Dereferencable<const FancyPointer<const int>, int>);
    STATIC_CHECK(flp::Dereferencable<const FancyPointer<const float>, float>);
    STATIC_CHECK(flp::Dereferencable<const FancyPointer<const int>, const int&>);
    STATIC_CHECK(flp::Dereferencable<const FancyPointer<const float>, const float&>);
    STATIC_CHECK(flp::Dereferencable<const FancyPointer<const int>, int>);
    STATIC_CHECK(flp::Dereferencable<const FancyPointer<const float>, float>);
    STATIC_CHECK(flp::Dereferencable<const FancyPointer<const int>, const int&>);
    STATIC_CHECK(flp::Dereferencable<const FancyPointer<const float>, const float&>);
  }
}

template<typename Type>
struct Range {
  struct Iterator {
    Type i{};

    const Type& operator*() const {
      return i;
    }

    Type& operator*() {
      return i;
    }

    Iterator operator++(int) {
      return {};
    }

    Iterator operator++() {
      return {};
    }
  };

  Iterator begin() const {
    return {};
  }

  Iterator end() const {
    return {};
  }

  Iterator begin() {
    return {};
  }

  Iterator end() {
    return {};
  }
};

// forward iterator
// bidirectional iterator

TEST_CASE("Range") {
  SECTION("std containers") {
    STATIC_CHECK(flp::Range<std::map<int, int>, std::tuple<int, int>>);
    STATIC_CHECK(flp::Range<std::set<int>, int>);
    STATIC_CHECK(flp::Range<std::set<int>, const int&>);
    STATIC_CHECK(flp::Range<std::vector<int>, int>);

    STATIC_CHECK(flp::Range<std::map<int, int>, std::tuple<int, int>>);
    STATIC_CHECK(flp::Range<std::vector<int>, int&>);
  }

  SECTION("Custom container") {
    STATIC_CHECK(flp::Range<Range<int>, int>);
    STATIC_CHECK(flp::Range<Range<int>, int&>);
    STATIC_CHECK(flp::Range<const Range<int>, const int&>);
    STATIC_CHECK(flp::Range<Range<const int>, const int&>);
  }
}

template<typename Type>
struct RandomAccessIterator {
  Type i{};

  const Type& operator*() const {
    return i;
  }

  Type& operator*() {
    return i;
  }

  RandomAccessIterator operator++(int) {
    return {};
  }

  RandomAccessIterator operator++() {
    return {};
  }

  RandomAccessIterator operator--(int) {
    return {};
  }

  RandomAccessIterator operator--() {
    return {};
  }

  RandomAccessIterator operator+(uint64_t) const {
    return {};
  }

  RandomAccessIterator operator+(int64_t) const {
    return {};
  }

  RandomAccessIterator operator-(uint64_t) const {
    return {};
  }

  RandomAccessIterator operator-(int64_t) const {
    return {};
  }

  RandomAccessIterator operator+=(uint64_t) {
    return {};
  }

  RandomAccessIterator operator+=(int64_t) {
    return {};
  }

  RandomAccessIterator operator-=(uint64_t) {
    return {};
  }

  RandomAccessIterator operator-=(int64_t) {
    return {};
  }
};

TEST_CASE("RandomAccessIterator") {
  STATIC_CHECK(flp::RandomAccessIterator<int*, int>);
  STATIC_CHECK(flp::RandomAccessIterator<std::vector<int>::iterator, int>);
  STATIC_CHECK(flp::RandomAccessIterator<RandomAccessIterator<int>, int>);
}

