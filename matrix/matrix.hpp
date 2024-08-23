// https://eigen.tuxfamily.org/dox/group__TutorialSlicingIndexing.html
//! @TODO compare against the other interface, too..
// the mixins might be valuable...

#include <array>
#include <iostream>
#include <vector>

// is_instance.hpp
template<typename, template<typename...> typename>
inline constexpr bool is_instance_helper = std::false_type{};

template<template<typename...> typename Query, typename ...Parameters>
inline constexpr bool is_instance_helper<Query<Parameters...>, Query> = std::true_type{};

// using the wrapper and decay handles refs and cv-qual
template<typename Query, template<typename...> typename Target>
inline constexpr bool is_instance_of = is_instance_helper<std::decay_t<Query>, Target>;

template<typename Type, template<typename...> typename Target>
concept instance_of = is_instance_of<Type, Target>;

// tagged_type.hpp
template<typename Type, typename/*Tag*/ = decltype([]{})>
struct TaggedType {
    using value_type = Type;

    Type value{};

    constexpr TaggedType() noexcept = default;

    constexpr TaggedType(std::convertible_to<Type> auto&& val) noexcept
        : value(std::move(val)) 
    {}

    constexpr TaggedType(const TaggedType&) noexcept = default;
    constexpr TaggedType(TaggedType&&) noexcept = default;

    constexpr TaggedType& operator=(const TaggedType&) noexcept = default;
    constexpr TaggedType& operator=(TaggedType&&) noexcept = default;

    constexpr ~TaggedType() = default;

    constexpr operator Type() const noexcept {
        return value;
    }

    constexpr TaggedType& operator=(Type val) noexcept {
        value = std::move(val);
        return *this;
    }
};

using Width = TaggedType<size_t>;
using Height = TaggedType<size_t>;
using XIndex = TaggedType<size_t>;
using YIndex = TaggedType<size_t>;
static_assert(not std::is_same_v<Width, Height>);
static_assert(not std::is_same_v<XIndex, YIndex>);

// dimensions.hpp
struct Dimensions {
    constexpr Dimensions() noexcept = default;
    constexpr Dimensions(Width w, Height h) noexcept
        : width(w)
        , height(h)
    {}

    constexpr Dimensions(const Dimensions&) noexcept = default;
    constexpr Dimensions(Dimensions&&) noexcept = default;

    constexpr Dimensions& operator=(const Dimensions&) noexcept = default;
    constexpr Dimensions& operator=(Dimensions&&) noexcept = default;

    constexpr ~Dimensions() noexcept = default;

    constexpr friend auto operator<=>(const Dimensions&, const Dimensions&) noexcept = default;

    Width width;
    Height height;
};

struct Dynamic_t {
    template<typename Type>
    constexpr static inline Type MAX_VALUE = std::numeric_limits<Width::value_type>::max();
    constexpr operator Width() const noexcept {
        return MAX_VALUE<Width>;
    }
    constexpr operator Height() const noexcept {
        return MAX_VALUE<Height>;
    }
    constexpr operator Dimensions() const noexcept {
        return {MAX_VALUE<Width>, MAX_VALUE<Height>};
    }
};

constexpr Dynamic_t Dynamic{};

// allocator.hpp
template<typename=decltype([]{})>
struct Allocator_t {};

template<typename Type>
inline constexpr bool is_allocator = is_instance_of<Type, Allocator_t>;

template<typename Type>
concept Allocator = instance_of<Type, Allocator_t>;

using DynamicAllocator = Allocator_t<>;
using StaticAllocator = Allocator_t<>;
using DeducedAllocator = Allocator_t<>;

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
    requires (((dimensions.width * dimensions.height) * sizeof(Type)) <= (1024 * 1024))
struct Storage<Type, dimensions, DeducedAllocator> {
    template<typename T = Type>
    using value_type = std::array<T, dimensions.width * dimensions.height>;
};

template<typename Type, Dimensions dimensions>
    requires (((dimensions.width * dimensions.height) * sizeof(Type)) > (1024 * 1024))
struct Storage<Type, dimensions, DeducedAllocator> {
    template<typename T = Type>
    using value_type = std::vector<T>;
};

template<typename Type>
concept BasicMatrix = requires(Type matrix, size_t index, XIndex xindex, YIndex yindex) {
    // the single parameter versions especially can also return a slice
    {matrix[index]} -> std::convertible_to<typename Type::value_type>;
    {matrix[index, index]} -> std::convertible_to<typename Type::value_type>;
    {matrix[xindex, yindex]} -> std::convertible_to<typename Type::value_type>;
    {matrix[xindex]} -> std::convertible_to<typename Type::value_type>;
    {matrix[yindex]} -> std::convertible_to<typename Type::value_type>;

    {matrix.width()} -> std::same_as<Width>;
    {matrix.height()} -> std::same_as<Height>;
};

template<typename Type>
concept MatrixLike = BasicMatrix<Type> and requires(Type matrix) {
    {matrix + matrix} /*-> BasicMatrix*/;
    {matrix - matrix} /*-> BasicMatrix*/;
    {matrix * matrix} /*-> BasicMatrix*/;
    {matrix / matrix} /*-> BasicMatrix*/;
};

struct Slicer {};
// static_assert(MatrixLike<Slicer>);

// matrix.hpp
template<typename Type, Dimensions Dimensions = Dynamic, Allocator = DynamicAllocator>
struct MatrixStore;

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

template<typename Type, Dimensions dimensions>
    requires (dimensions != Dynamic)
struct MatrixStore<Type, dimensions, StaticAllocator> {
    using Storage = Storage<Type, dimensions, StaticAllocator>::value_type;

    constexpr MatrixStore() noexcept(std::is_nothrow_default_constructible_v<Storage>) = default;
    constexpr MatrixStore(const MatrixStore&) noexcept(std::is_nothrow_copy_constructible_v<Storage>) = default;
    constexpr MatrixStore(MatrixStore&&) noexcept(std::is_nothrow_move_constructible_v<Storage>) = default;
    constexpr MatrixStore& operator=(const MatrixStore&) noexcept(std::is_nothrow_copy_assignable_v<Storage>) = default;
    constexpr MatrixStore& operator=(MatrixStore&&) noexcept(std::is_nothrow_move_assignable_v<Storage>) = default;
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
    constexpr decltype(auto) operator[](this Self&& self, const Slicer slicer) {
        // return a slice wrapper
        return 0;
    }

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const YIndex index) {
        return std::forward<Self>(self).data.at(index);
    }

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const XIndex index) {
        return std::forward<Self>(self).data.at(index);
    }

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const XIndex x_index, const YIndex y_index) {
        return std::forward<Self>(self).data.at(to_1D(width, x_index, y_index));
    }

    constexpr void resize(Width, Height) {
        static_assert(false, "Cannot dynamically resize statically allocated storage");
    }

    constexpr static Width width = dimensions.width;
    constexpr static Height height = dimensions.height;

    Storage data;
};

template<typename Type>
struct MatrixStore<Type, Dynamic, DynamicAllocator> {
    using Storage = Storage<Type, Dynamic, DynamicAllocator>::value_type;

    //constexpr MatrixStore()

    // assignment from other dynamic matrices
    
    // assignment from static matrices

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const YIndex index) {
        return std::forward<Self>(self).data.at(index);
    }

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const XIndex index) {
        return std::forward<Self>(self).data.at(index);
    }

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const XIndex x_index, const YIndex y_index) {
        return std::forward<Self>(self).data.at(to_1D(self.width, x_index, y_index));
    }

    constexpr void resize(Width w, Height h) {
        width = w;
        height = h;
        data.resize(width * height);
    }

    Width width;
    Height height;

    Storage data;
};

template<typename Type, Dimensions dimensions = Dynamic, Allocator allocator = DynamicAllocator>
struct Matrix {
    using value_type = Type;
    using Storage = MatrixStore<value_type, dimensions, allocator>;

    constexpr Matrix() noexcept(std::is_nothrow_default_constructible_v<Storage>) = default;
    constexpr Matrix(const Matrix&) noexcept(std::is_nothrow_copy_constructible_v<Storage>) = default;
    constexpr Matrix(Matrix&&) noexcept(std::is_nothrow_move_constructible_v<Storage>) = default;
    constexpr Matrix& operator=(const Matrix&) noexcept(std::is_nothrow_copy_assignable_v<Storage>) = default;
    constexpr Matrix& operator=(Matrix&&) noexcept(std::is_nothrow_move_assignable_v<Storage>) = default;
    constexpr ~Matrix() noexcept(std::is_nothrow_destructible_v<Storage>) = default;

    constexpr Matrix(Dimensions dims, const Type value) noexcept
        : storage(dims, value)
    {}
    constexpr Matrix(Dimensions dims) noexcept
        : Matrix(dims, {})
    {}
    constexpr Matrix(const Width width, const Height height, const Type value) noexcept
        : Matrix({width, height}, value)
    {}
    constexpr Matrix(const Width width, const Height height) noexcept
        : Matrix(width, height, {})
    {}

    // assignment from other dynamic matrices
    
    // assignment from static matrices

    // the single argument index operators could return a slice-like type if the dimensions are Dynamic

    // using YIndex to match with the Vector alias
    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const size_t index) {
        return std::forward<Self>(self).storage[YIndex(index)];
    }

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const YIndex index) {
        return std::forward<Self>(self).storage[index];
    }

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const XIndex index) {
        return std::forward<Self>(self).storage[index];
    }

    template<typename Self>
    constexpr decltype(auto) operator[](this Self&& self, const XIndex x_index, const YIndex y_index) {
        return std::forward<Self>(self).storage[x_index, y_index];
    }

    constexpr void resize(Dimensions dims)
        requires (dimensions == Dynamic and std::is_same_v<allocator, DynamicAllocator>)
    {
        storage.resize(dims.width, dims.height);
    }

    constexpr void resize(Width width, Height height)
        requires (dimensions == Dynamic and std::is_same_v<allocator, DynamicAllocator>)
    {
        storage.resize(width, height);
    }

    constexpr void resize(Height height)
        requires (dimensions == Dynamic and std::is_same_v<allocator, DynamicAllocator>)
    {
        storage.resize(height);
    }

    constexpr void resize(Width width)
        requires (dimensions == Dynamic and std::is_same_v<allocator, DynamicAllocator>)
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

template<typename OP, MatrixLike LHS, MatrixLike RHS>
    requires (std::convertible_to<typename RHS::value_type, typename LHS::value_type>)
struct Operation {
    LHS lhs;
    RHS rhs;

    [[nodiscard]]
    constexpr LHS operator()() const {
        return OP()(lhs, rhs);
    }

    [[nodiscard]]
    constexpr operator LHS() const {
        return (*this)();
    }
};

/*template<typename LType, Dimensions Ldimensions, Allocator Lallocator, typename RType, Dimensions Rdimensions, Allocator Rallocator>
constexpr decltype(auto) operator+(const Matrix<LType, Ldimensions, Lallocator>& lhs, const Matrix<RType, Rdimensions, Rallocator>& rhs) {
    using MatrixAddition = Operation<std::plus<>, LType, Ldimensions, Lallocator, RType, Rdimensions, Rallocator>;
    return MatrixAddition{lhs, rhs};
}

template<typename LType, Dimensions Ldimensions, Allocator Lallocator, typename RType, Dimensions Rdimensions, Allocator Rallocator>
constexpr decltype(auto) operator-(const Matrix<LType, Ldimensions, Lallocator>& lhs, const Matrix<RType, Rdimensions, Rallocator>& rhs) {
    using MatrixSubtraction = Operation<std::minus<>, LType, Ldimensions, Lallocator, RType, Rdimensions, Rallocator>;
    return MatrixSubtraction{lhs, rhs};
}

template<typename LType, Dimensions Ldimensions, Allocator Lallocator, typename RType, Dimensions Rdimensions, Allocator Rallocator>
constexpr decltype(auto) operator*(const Matrix<LType, Ldimensions, Lallocator>& lhs, const Matrix<RType, Rdimensions, Rallocator>& rhs) {
    using MatrixMultiplication = Operation<std::multiplies<>, LType, Ldimensions, Lallocator, RType, Rdimensions, Rallocator>;
    return MatrixMultiplication{lhs, rhs};
}

template<typename LType, Dimensions Ldimensions, Allocator Lallocator, typename RType, Dimensions Rdimensions, Allocator Rallocator>
constexpr decltype(auto) operator/(const Matrix<LType, Ldimensions, Lallocator>& lhs, const Matrix<RType, Rdimensions, Rallocator>& rhs) {
    using MatrixDivision = Operation<std::divides<>, LType, Ldimensions, Lallocator, RType, Rdimensions, Rallocator>;
    return MatrixDivision{lhs, rhs};
}*/

template<MatrixLike LHS, MatrixLike RHS>
constexpr decltype(auto) operator+(const LHS& lhs, const RHS& rhs) {
    using MatrixAddition = Operation<std::plus<>, LHS, RHS>;
    return MatrixAddition{lhs, rhs};
}

template<MatrixLike LHS, MatrixLike RHS>
constexpr decltype(auto) operator-(const LHS& lhs, const RHS& rhs) {
    using MatrixSubtraction = Operation<std::minus<>, LHS, RHS>;
    return MatrixSubtraction{lhs, rhs};
}

template<MatrixLike LHS, MatrixLike RHS>
constexpr decltype(auto) operator*(const LHS& lhs, const RHS& rhs) {
    using MatrixMultiplication = Operation<std::multiplies<>, LHS, RHS>;
    return MatrixMultiplication{lhs, rhs};
}

template<MatrixLike LHS, MatrixLike RHS>
constexpr decltype(auto) operator/(const LHS& lhs, const RHS& rhs) {
    using MatrixDivision = Operation<std::divides<>, LHS, RHS>;
    return MatrixDivision{lhs, rhs};
}

struct S{};
static_assert(MatrixLike<Matrix<int, Dynamic, DynamicAllocator>>);
static_assert(MatrixLike<Matrix<unsigned int, Dynamic, DynamicAllocator>>);
static_assert(MatrixLike<Matrix<float, Dynamic, DynamicAllocator>>);
static_assert(MatrixLike<Matrix<S, Dynamic, DynamicAllocator>>);
static_assert(MatrixLike<Matrix<int, {1, 1}, StaticAllocator>>);
static_assert(MatrixLike<Matrix<unsigned int, {1, 1}, StaticAllocator>>);
static_assert(MatrixLike<Matrix<float, {1, 1}, StaticAllocator>>);
static_assert(MatrixLike<Matrix<S, {1, 1}, StaticAllocator>>);

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

int main() {
    Matrix<size_t> int_mat;
    Matrix<float> float_mat;
    Matrix<int, {5, 5}, StaticAllocator> s_mat;
    //s_mat.resize(1,1);
    s_mat[0];
    //s_mat[100];

    int_mat.resize(1, 2);

    int_mat[0] = 5;
    int_mat[1] = 5;

    return int_mat[0] * int_mat[1];
}
