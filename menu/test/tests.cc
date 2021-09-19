#include<sstream>

#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<menu.hh>

TEST_CASE("Menu allows option selection and provides callbacks on selection.", "[menu]") {
  std::stringstream ss;
  auto pm0 = std::make_shared<gsw::menu<int>>("pm0");
  auto pm1 = std::make_shared<gsw::menu<int>>("pm1");
  std::shared_ptr<gsw::menu<int>> current(pm0);

  CHECK(pm0->prompt() == "pm0");
  CHECK(pm1->prompt() == "pm1");
  CHECK(current->prompt() == "pm0");

  /*! @todo Add tests when false is returned */
  pm0->addOption(0, "electric", pm1, [&](int)
    {
      ss << "beep" << '\n';
      return true;
    });
  pm0->addOption(1, "boogaloo", pm1, [&](int)
    {
      ss << "boop" << '\n';
      return true;
    });

  pm1->addOption(0, "foo", pm0, [&](int)
    {
      ss << "buup" << '\n';
      return true;
    });
  pm1->addOption(1, "baz", pm0, [&](int)
    {
      ss << "biip" << '\n';
      return true;
    });
  pm1->addOption(1, "bar", pm0, [&](int)
    {
      ss << "byyp" << '\n';
      return true;
    });

  //ctor compile check
  gsw::menu<int> one;
  gsw::menu<int> two(one);
  gsw::menu<int> three(gsw::menu<int>());
  one.print_options(ss);
  one.print_options(ss);
  ss << one;

  SECTION("Prints menus when requested.") {
    for(unsigned int i = 0; i < 2; ++i) {
      current->print_options(ss);
      current = current->select(i);
    }
    int i;
    std::string str;

    ss >> i;
    ss >> str;

    CHECK(i == 0);
    CHECK(str == "electric");

    ss >> i;
    ss >> str;

    CHECK(i == 1);
    CHECK(str == "boogaloo");

    ss >> str;

    CHECK(str == "beep");

    ss >> i;
    ss >> str;

    CHECK(i == 0);
    CHECK(str == "foo");

    ss >> i;
    ss >> str;

    CHECK(i == 1);
    CHECK(str == "bar");

    ss >> str;

    CHECK(str == "byyp");
  }

  SECTION("Forwards out of range exception when accessing an invalid menu option.") {
    CHECK_THROWS_AS(pm0->select(3), std::out_of_range);
  }
}
