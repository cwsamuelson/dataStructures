// https://eigen.tuxfamily.org/dox/group__TutorialSlicingIndexing.html
//! @TODO compare against the other interface, too..
// the mixins might be valuable...

#include <core/tagged_type.hh>
#include <core/traits.hh>

#include <array>
#include <limits>
#include <vector>

namespace flp {

struct WidthTag;
struct HeightTag;
struct XIndexTag;
struct YIndexTag;
using Width  = TaggedType<size_t, WidthTag>;
using Height = TaggedType<size_t, HeightTag>;
using XIndex = TaggedType<size_t, XIndexTag>;
using YIndex = TaggedType<size_t, YIndexTag>;
static_assert(not std::is_same_v<Width, Height>);
static_assert(not std::is_same_v<XIndex, YIndex>);

// transposition of arguments?
constexpr auto operator+(const Width& lhs, const Height& rhs) noexcept {
  return static_cast<size_t>(lhs) + static_cast<size_t>(rhs);
}

constexpr auto operator-(const Width& lhs, const Height& rhs) noexcept {
  return static_cast<size_t>(lhs) - static_cast<size_t>(rhs);
}

constexpr auto operator*(const Width& lhs, const Height& rhs) noexcept {
  return static_cast<size_t>(lhs) * static_cast<size_t>(rhs);
}

constexpr auto operator/(const Width& lhs, const Height& rhs) noexcept {
  return static_cast<size_t>(lhs) / static_cast<size_t>(rhs);
}

// dimensions.hpp
struct Dimensions {
  constexpr Dimensions() noexcept = default;
  constexpr Dimensions(Width w, Height h) noexcept
    : width(w)
    , height(h) {}

  constexpr Dimensions(const Dimensions&) noexcept = default;
  constexpr Dimensions(Dimensions&&) noexcept      = default;

  constexpr Dimensions& operator=(const Dimensions&) noexcept = default;
  constexpr Dimensions& operator=(Dimensions&&) noexcept      = default;

  constexpr ~Dimensions() noexcept = default;

  constexpr friend auto operator<=>(const Dimensions&, const Dimensions&) noexcept = default;

  Width  width;
  Height height;
};

struct Dynamic_t {
  template<typename Type>
  constexpr static Type MAX_VALUE = std::numeric_limits<Type>::max();

  constexpr operator Width() const noexcept {
    return Width { MAX_VALUE<Width::value_type> };
  }
  constexpr operator Height() const noexcept {
    return Height { MAX_VALUE<Height::value_type> };
  }
  constexpr operator Dimensions() const noexcept {
    return Dimensions { Width(*this), Height(*this) };
  }
};

constexpr Dynamic_t Dynamic {};
// constexpr Dimensions Dynamic { std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max() };

// allocator.hpp
template<typename>
struct Allocator_t {};

template<typename Type>
inline constexpr bool is_allocator = flp::is_specialization_of<Type, Allocator_t>;

template<typename Type>
concept Allocator = flp::is_specialization_of<Type, Allocator_t>;

struct DynamicTag;
struct StaticTag;
struct DeducedTag;
using DynamicAllocator = Allocator_t<DynamicTag>;
using StaticAllocator  = Allocator_t<StaticTag>;
using DeducedAllocator = Allocator_t<DeducedTag>;

// storage.hpp
template<typename Type, Dimensions dimensions, Allocator AllocTag>
struct Storage;

template<typename Type>
struct Storage<Type, Dynamic, DynamicAllocator> {
  using value_type = std::vector<Type>;
};

template<typename Type, Dimensions dimensions>
struct Storage<Type, dimensions, StaticAllocator> {
  using value_type = std::array<Type, dimensions.width * dimensions.height>;
};

template<typename Type, Dimensions dimensions>
struct Storage<Type, dimensions, DeducedAllocator> {
  template<typename T = Type>
  using value_type = std::vector<T>;
};

template<typename Type>
concept BasicMatrix = requires(Type matrix, size_t index, XIndex xindex, YIndex yindex) {
  // the single parameter versions especially can also return a slice
  {
    matrix[index]
  } /*-> std::convertible_to<typename Type::value_type>*/;
  {
    matrix[index, index]
  } /*-> std::convertible_to<typename Type::value_type>*/;
  {
    matrix[xindex, yindex]
  } /*-> std::convertible_to<typename Type::value_type>*/;
  {
    matrix[xindex]
  } /*-> std::convertible_to<typename Type::value_type>*/;
  {
    matrix[yindex]
  } /*-> std::convertible_to<typename Type::value_type>*/;

  {
    matrix.width()
  } -> std::same_as<Width>;
  {
    matrix.height()
  } -> std::same_as<Height>;
};

template<typename Type>
concept MatrixLike = BasicMatrix<Type> and requires(Type matrix) {
  {
    matrix + matrix
  } /*-> BasicMatrix*/;
  {
    matrix - matrix
  } /*-> BasicMatrix*/;
  {
    matrix* matrix
  } /*-> BasicMatrix*/;
  {
    matrix / matrix
  } /*-> BasicMatrix*/;
};

struct Slicer {};
// static_assert(MatrixLike<Slicer>);

// matrix.hpp
constexpr size_t to_1D(const size_t index) {
  return index;
}
constexpr size_t to_1D(const size_t, const size_t index) {
  return to_1D(index);
}
constexpr size_t to_1D(const size_t width, const size_t xindex, const size_t yindex) {
  return (yindex * width) + xindex;
}
constexpr size_t to_1D(const Width width, const XIndex xindex, const YIndex yindex) {
  return to_1D(width.value, xindex.value, yindex.value);
}

template<typename Type, Dimensions Dimensions = Dynamic, Allocator = DynamicAllocator>
struct MatrixStore;

template<typename Type, Dimensions dims>
  requires(dims != Dynamic)
struct MatrixStore<Type, dims, StaticAllocator> {
  constexpr static Dimensions dimensions = dims;

  using value_type = Type;
  using Alloc_t    = StaticAllocator;
  using Storage    = typename Storage<Type, dimensions, StaticAllocator>::value_type;

  constexpr MatrixStore() noexcept(std::is_nothrow_default_constructible_v<Storage>)                        = default;
  constexpr MatrixStore(const MatrixStore&) noexcept(std::is_nothrow_copy_constructible_v<Storage>)         = default;
  constexpr MatrixStore(MatrixStore&&) noexcept(std::is_nothrow_move_constructible_v<Storage>)              = default;
  constexpr MatrixStore& operator=(const MatrixStore&) noexcept(std::is_nothrow_copy_assignable_v<Storage>) = default;
  constexpr MatrixStore& operator=(MatrixStore&&) noexcept(std::is_nothrow_move_assignable_v<Storage>)      = default;

  constexpr ~MatrixStore() noexcept(std::is_nothrow_destructible_v<Storage>) = default;

  // assignment from dynamic matrices
  constexpr MatrixStore& operator=(const MatrixStore<Type, Dynamic, DynamicAllocator>& other) noexcept {
    assert(other.width == width);
    assert(other.height == height);
    //! @TODO do the assignment
    return *this;
  }

  // assignment from other static matrices

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const Slicer slicer) {
    // return a slice wrapper
    return 0;
  }

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const YIndex index) {
    return std::forward<Self>(self).data.at(index.value);
  }

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const XIndex index) {
    return std::forward<Self>(self).data.at(index.value);
  }

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const XIndex x_index, const YIndex y_index) {
    return std::forward<Self>(self).data.at(to_1D(width, x_index, y_index));
  }

  constexpr void resize(Width, Height) {
    static_assert(false, "Cannot dynamically resize statically allocated storage");
  }

  constexpr static Width  width  = dimensions.width;
  constexpr static Height height = dimensions.height;

  Storage data;
};

template<typename Type>
struct MatrixStore<Type, Dynamic, DynamicAllocator> {
  constexpr static Dimensions dimensions = Dynamic;

  using value_type = Type;
  using Alloc_t    = DynamicAllocator;
  using Storage    = Storage<Type, Dynamic, DynamicAllocator>::value_type;

  // constexpr MatrixStore()

  // assignment from other dynamic matrices

  // assignment from static matrices

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const YIndex index) {
    return std::forward<Self>(self).data.at(index.value);
  }

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const XIndex index) {
    return std::forward<Self>(self).data.at(index.value);
  }

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const XIndex x_index, const YIndex y_index) {
    return std::forward<Self>(self).data.at(to_1D(self.width, x_index, y_index));
  }

  constexpr void resize(Width w, Height h) {
    width  = w;
    height = h;
    data.resize(width * height);
  }

  Width  width;
  Height height;

  Storage data;
};

constexpr size_t StaticLimit = 4096;

template<typename Type>
struct MatrixStore<Type, Dynamic, DeducedAllocator> : MatrixStore<Type, Dynamic, DynamicAllocator> {};
template<typename Type, Dimensions dimensions>
  requires((dimensions.width * dimensions.height) * sizeof(Type) <= StaticLimit)
struct MatrixStore<Type, dimensions, DeducedAllocator> : MatrixStore<Type, dimensions, StaticAllocator> {};
template<typename Type, Dimensions dimensions>
  requires((dimensions.width * dimensions.height) * sizeof(Type) > StaticLimit)
struct MatrixStore<Type, dimensions, DeducedAllocator> : MatrixStore<Type, Dynamic, DynamicAllocator> {};

template<typename Type, Dimensions dimensions = Dynamic, Allocator alloc = DeducedAllocator>
struct Matrix {
  using value_type = Type;
  using Storage    = MatrixStore<value_type, dimensions, alloc>;
  using allocator  = typename Storage::Alloc_t;

  constexpr Matrix() noexcept(std::is_nothrow_default_constructible_v<Storage>)           = default;
  constexpr Matrix(const Matrix&) noexcept(std::is_nothrow_copy_constructible_v<Storage>) = default;
  constexpr Matrix(Matrix&&) noexcept(std::is_nothrow_move_constructible_v<Storage>)      = default;

  constexpr Matrix& operator=(const Matrix&) noexcept(std::is_nothrow_copy_assignable_v<Storage>) = default;
  constexpr Matrix& operator=(Matrix&&) noexcept(std::is_nothrow_move_assignable_v<Storage>)      = default;

  constexpr ~Matrix() noexcept(std::is_nothrow_destructible_v<Storage>) = default;

  constexpr Matrix(Dimensions dims, const Type value) noexcept
    : storage(dims, value) {}
  constexpr Matrix(Dimensions dims) noexcept
    : Matrix(dims, {}) {}
  constexpr Matrix(const Width width, const Height height, const Type value) noexcept
    : Matrix({ width, height }, value) {}
  constexpr Matrix(const Width width, const Height height) noexcept
    : Matrix(width, height, {}) {}

  // assignment from other dynamic matrices

  // assignment from static matrices

  // the single argument index operators could return a slice-like type if the dimensions are Dynamic

  // using YIndex to match with the Vector alias
  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const size_t index) {
    return std::forward<Self>(self).storage[YIndex(index)];
  }

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const YIndex index) {
    return std::forward<Self>(self).storage[index];
  }

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const XIndex index) {
    return std::forward<Self>(self).storage[index];
  }

  template<typename Self>
  constexpr decltype(auto) operator[](this Self && self, const XIndex x_index, const YIndex y_index) {
    return std::forward<Self>(self).storage[x_index, y_index];
  }

  constexpr void resize(Dimensions dims)
    requires(dimensions == Dynamic and std::is_same_v<allocator, DynamicAllocator>)
  {
    storage.resize(dims.width, dims.height);
  }

  constexpr void resize(Width width, Height height)
    requires(dimensions == Dynamic and std::is_same_v<allocator, DynamicAllocator>)
  {
    storage.resize(width, height);
  }

  constexpr void resize(Height height)
    requires(dimensions == Dynamic and std::is_same_v<allocator, DynamicAllocator>)
  {
    storage.resize(height);
  }

  constexpr void resize(Width width)
    requires(dimensions == Dynamic and std::is_same_v<allocator, DynamicAllocator>)
  {
    storage.resize(width);
  }

  [[nodiscard]]
  constexpr Width width() const {
    return storage.width;
  }

  [[nodiscard]]
  constexpr Height height() const {
    return storage.height;
  }

  Storage storage;
};

// matrix_ops.hpp
template<typename OP, typename LHS, typename RHS>
  requires(std::convertible_to<typename RHS::value_type, typename LHS::value_type>)
struct Operation {
  LHS lhs;
  RHS rhs;

  [[nodiscard]]
  constexpr LHS
  operator()() const {
    return OP()(lhs, rhs);
  }

  [[nodiscard]]
  constexpr
  operator LHS() const {
    return (*this)();
  }
};

template<typename LHS, typename RHS>
constexpr decltype(auto) operator+(const LHS & lhs, const RHS & rhs) {
  using MatrixAddition = Operation<std::plus<>, LHS, RHS>;
  return MatrixAddition { lhs, rhs };
}

template<typename LHS, typename RHS>
constexpr decltype(auto) operator-(const LHS & lhs, const RHS & rhs) {
  using MatrixSubtraction = Operation<std::minus<>, LHS, RHS>;
  return MatrixSubtraction { lhs, rhs };
}

template<typename LHS, typename RHS>
constexpr decltype(auto) operator*(const LHS & lhs, const RHS & rhs) {
  using MatrixMultiplication = Operation<std::multiplies<>, LHS, RHS>;
  return MatrixMultiplication { lhs, rhs };
}

template<typename LHS, typename RHS>
constexpr decltype(auto) operator/(const LHS & lhs, const RHS & rhs) {
  using MatrixDivision = Operation<std::divides<>, LHS, RHS>;
  return MatrixDivision { lhs, rhs };
}

struct S {};
static_assert(MatrixLike<Matrix<int, Dynamic, DynamicAllocator>>);
static_assert(MatrixLike<Matrix<unsigned int, Dynamic, DynamicAllocator>>);
static_assert(MatrixLike<Matrix<float, Dynamic, DynamicAllocator>>);
static_assert(MatrixLike<Matrix<S, Dynamic, DynamicAllocator>>);
static_assert(MatrixLike<Matrix<int, { 1uz, 1uz }, StaticAllocator>>);
static_assert(MatrixLike<Matrix<unsigned int, { 1uz, 1uz }, StaticAllocator>>);
static_assert(MatrixLike<Matrix<float, { 1uz, 1uz }, StaticAllocator>>);
static_assert(MatrixLike<Matrix<S, { 1uz, 1uz }, StaticAllocator>>);

// matrix_aliases.hpp
// none of these aliases specify an allocation type?
// they're probably currently dynamic, but maybe they should be static?
template<typename Type, size_t Length>
using Vector = Matrix<Type, Dimensions(Width(1uz), Height(Length))>;

template<Width WIDTH, Height HEIGHT>
using Mati = Matrix<int, Dimensions(WIDTH, HEIGHT)>;
template<Width WIDTH, Height HEIGHT>
using Matui = Matrix<unsigned int, Dimensions(WIDTH, HEIGHT)>;
template<Width WIDTH, Height HEIGHT>
using Matf = Matrix<float, Dimensions(WIDTH, HEIGHT)>;
template<Width WIDTH, Height HEIGHT>
using Matd = Matrix<double, Dimensions(WIDTH, HEIGHT)>;

} // namespace flp
