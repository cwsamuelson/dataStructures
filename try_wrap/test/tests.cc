#include <try_wrap.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

void nodata_nothrow() noexcept {
}

void nodata() {
}

int nothrow() noexcept {
    return 42;
}

int data() {
    return 1138;
}

int& get_static() {
    static int i = 42;
    return i;
}

TEST_CASE("try_wrap") {
    /*auto x = */TryWrap{nodata_nothrow}();
    auto y = TryWrap{nothrow}();
    auto z = TryWrap{nodata}();
    auto [v, w] = TryWrap{data}();
    auto&& [a, b] = TryWrap{get_static}();

    std::cout << *a << '\n';
    ++*a;
    std::cout << *a << '\n';

    auto&& [c, d] = TryWrap{get_static}();
    std::cout << *c << '\n';
    ++*c;
    std::cout << *c << '\n';
    std::cout << *a << '\n';
}
