#include <catch2/catch_all.hpp>

#include "core/concepts.hh"

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

