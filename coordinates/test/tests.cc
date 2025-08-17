#include <coordinates.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

template<typename Type>
concept BasicOperations = requires(Type value, const Type cvalue) {
  cvalue <=> cvalue;
  cvalue <   cvalue;
  cvalue <=  cvalue;
  cvalue   > cvalue;
  cvalue  >= cvalue;
  cvalue ==  cvalue;
  cvalue !=  cvalue;
  value = cvalue;
  value = std::move(value);
};

template<typename Type, typename ValueType>
concept TypedOperations = requires(const ValueType val) {
  Type({val}, {val});
};

//! @TODO convert this to a template test

TEST_CASE("coordinates") {
  STATIC_CHECK(BasicOperations<DiscreteCoordinates>);
  STATIC_CHECK(BasicOperations<ContinuousCoordinates>);

  STATIC_CHECK(TypedOperations<DiscreteCoordinates, size_t>);
  STATIC_CHECK(TypedOperations<ContinuousCoordinates, float>);

  DiscreteCoordinates dc;
  ContinuousCoordinates cc;
}

TEST_CASE("dimensions") {
  STATIC_CHECK(BasicOperations<DiscreteDimensions>);
  STATIC_CHECK(BasicOperations<ContinuousDimensions>);

  STATIC_CHECK(TypedOperations<DiscreteDimensions, size_t>);
  STATIC_CHECK(TypedOperations<ContinuousDimensions, float>);

  DiscreteDimensions dd;
  ContinuousDimensions cd;
}
