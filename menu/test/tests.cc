#include <menu.hh>

#include <catch2/catch_all.hpp>

#include <vector>

using namespace flp;

TEST_CASE("`Menu`::Construction") {
  const std::vector<Menu> v;
  Menu a("");

  CHECK(a.sub_menus.empty());

  Menu b("", v);
  Menu c("", {{""}});
  Menu d("", {{""}, {"", {{""}}}});

  CHECK(b.sub_menus.empty());
  CHECK(c.sub_menus.size() == 1);
  CHECK(d.sub_menus.size() == 2);

  const std::map<size_t, Menu> m {
    {0, {""}},
    {1, {""}},
    {2, {""}},
  };

  Menu e("", m);
  Menu f("", {{0, {""}}});
  Menu g("", {
    {0, {""}},
    {1, {"", {
      {""}
    }}}
  });

  CHECK(e.sub_menus.size() == 3);
  CHECK(f.sub_menus.size() == 1);
  CHECK(g.sub_menus.size() == 2);
}
