#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<logic.hh>
#include<catch_stringify_helper.hh>

using namespace std;
using namespace gsw;

TEST_CASE("Logic operators behave as expected", "[logic]") {
  auto foo = "foo"_lvar;
  auto bar = "bar"_lvar;
  auto baz = "baz"_lvar;
  auto qux = "qux"_lvar;

  SECTION("Basic operation") {
    REQUIRE((foo)({ "foo" })); // trivially true
    REQUIRE(!(foo)({}));      // trivially false

    CHECK((foo).solve({ "foo" }) == set<set<string>>{{ "foo" }});

    CHECK((foo).solve({ "foo" }) == set<set<string>>{{ "foo" }});

    CHECK((foo).solve({ "bar" }) == set<set<string>>{{ "bar", "foo" },
                                                     { "foo" }});


    CHECK((foo).solve2({ "foo" }) == set<set<string>>{{ "foo" }});

    CHECK((foo).solve2({ "foo" }) == set<set<string>>{{ "foo" }});

    CHECK((foo).solve2({ "bar" }) == set<set<string>>{{ "bar", "foo" },
                                                      { "foo" }});
  }

  SECTION("Negation") {
    SECTION("Basic negation") {
      REQUIRE((!foo)({}));
      REQUIRE(!(!foo)({ "foo" }));

      // The only existing solution is foo being false
      // which is represented by empty set
      CHECK((!foo).solve({ "foo" }) == set<set<string>>{{}});

      CHECK((!foo).solve2({ "foo" }) == set<set<string>>{{}});
    }

    SECTION("Double negation") {
      REQUIRE((!!foo)({ "foo" }));

      CHECK((!!foo).solve({ "foo" }) == set<set<string>>{{ "foo" }});

      CHECK((!!foo).solve2({ "foo" }) == set<set<string>>{{ "foo" }});
    }
  }

  SECTION("Conjunction (and)") {
    REQUIRE((foo && bar)({ "foo", "bar" }));
    REQUIRE(!(foo && bar)({ "bar" }));
    REQUIRE(!(foo && bar)({ "foo" }));
    REQUIRE(!(foo && bar)({}));
    REQUIRE((!foo && !bar)({}));

    CHECK((foo && bar).solve({ "foo", "bar" }) == set<set<string>>{{ "foo", "bar" }});

    CHECK((foo && !foo).solve({ "foo" }).empty());

    CHECK((foo && bar).solve2({ "foo", "bar" }) == set<set<string>>{{ "foo", "bar" }});

    CHECK((foo && !foo).solve2({ "foo" }).empty());
  }

  SECTION("Disjunction (or)") {
    REQUIRE((foo || bar)({ "foo", "bar" }));
    REQUIRE((foo || bar)({ "bar" }));
    REQUIRE((foo || bar)({ "foo" }));
    REQUIRE(!(foo || bar)({}));

    CHECK((foo || bar).solve({ "foo", "bar" }) == set<set<string>>({{ "foo", "bar" },
                                                                    { "foo" },
                                                                    { "bar" }}));

    CHECK((foo || !foo).solve({ "foo" }) == set<set<string>>{{ "foo" },
                                                             {}});

    CHECK((foo || bar).solve2({ "foo", "bar" }) == set<set<string>>({{ "foo", "bar" },
                                                                     { "foo" },
                                                                     { "bar" }}));

    CHECK((foo || !foo).solve2({ "foo" }) == set<set<string>>{{ "foo" },
                                                              {}});
  }

  SECTION("Exclusive disjunction (xor)") {
    REQUIRE(!(foo ^ bar)({ "foo", "bar" }));
    REQUIRE((foo ^ bar)({ "bar" }));
    REQUIRE((foo ^ bar)({ "foo" }));
    REQUIRE(!(foo ^ bar)({}));

    CHECK((foo ^ bar).solve({ "foo", "bar" }) == set<set<string>>{{ "foo" },
                                                                  { "bar" }});

    CHECK((foo ^ !foo).solve({ "foo" }).empty());

    CHECK((foo ^ (foo || bar)).solve({ "foo", "bar" }) == set<set<string>>{{ "bar" }});


    CHECK((foo ^ bar).solve2({ "foo", "bar" }) == set<set<string>>{{ "foo" },
                                                                   { "bar" }});

    CHECK((foo ^ !foo).solve2({ "foo" }).empty());

    CHECK((foo ^ (foo || bar)).solve2({ "foo", "bar" }) == set<set<string>>{{ "bar" }});
  }

  SECTION("Implication") {
    REQUIRE((foo.implies(bar))({ "foo", "bar" }));
    REQUIRE((foo.implies(bar))({ "bar" }));
    REQUIRE(!(foo.implies(bar))({ "foo" }));
    REQUIRE((foo.implies(bar))({}));

    // foo and bar both false is a valid answer, so empty set is included
    CHECK((foo.implies(bar)).solve({ "foo", "bar" }) == set<set<string>>{{ "foo", "bar" },
                                                                         { "bar" },
                                                                         {}});

    CHECK((foo.implies(foo)).solve({ "foo" }) == set<set<string>>{{ "foo" },
                                                                  {}});

    CHECK((foo.implies(!foo)).solve({ "foo" }) == set<set<string>>{{ "foo" },
                                                                   {}});

    CHECK(((!foo).implies(foo)).solve({ "foo" }) == set<set<string>>{{ "foo" },
                                                                     {}});


    CHECK((foo.implies(bar)).solve2({ "foo", "bar" }) == set<set<string>>{{ "foo", "bar" },
                                                                          { "bar" },
                                                                          {}});

    CHECK((foo.implies(foo)).solve2({ "foo" }) == set<set<string>>{{ "foo" },
                                                                   {}});

    CHECK((foo.implies(!foo)).solve2({ "foo" }) == set<set<string>>{{ "foo" },
                                                                    {}});

    CHECK(((!foo).implies(foo)).solve2({ "foo" }) == set<set<string>>{{ "foo" },
                                                                      {}});
  }

  SECTION("Tautology (equivalence, iff)") {
    REQUIRE((foo.iff(bar))({ "foo", "bar" }));
    REQUIRE(!(foo.iff(bar))({ "bar" }));
    REQUIRE(!(foo.iff(bar))({ "foo" }));
    REQUIRE((foo.iff(bar))({}));

    // foo and bar both false is a valid answer, so empty set is included
    CHECK((foo.iff(bar)).solve({ "foo", "bar" }) == set<set<string>>{{ "foo", "bar" },
                                                                     {}});

    CHECK((foo.iff(bar)).solve2({ "foo", "bar" }) == set<set<string>>{{ "foo", "bar" },
                                                                      {}});
  }

  SECTION("Can form logic sentences") {
    auto prop = ("A"_lvar && !"B"_lvar).implies("C"_lvar) && (!"A"_lvar).iff("B"_lvar && "C"_lvar);

    int i = 0;
    for(const auto& solution : prop.solve({ "A", "B", "C" })) {
      CHECK(prop(solution));
      ++i;
    }
    CHECK(i == 3);

    i = 0;
    for(const auto& solution : prop.solve2({ "A", "B", "C" })) {
      CHECK(prop(solution));
      ++i;
    }
    CHECK(i == 3);
  }

  SECTION("Can solve compound propositions") {
    CHECK(((foo || bar) && (baz || qux)).solve({ "foo", "bar", "baz", "qux" }) == set<set<string>>{{ "bar", "qux" },
                                                                                                   { "foo", "qux" },
                                                                                                   { "foo", "bar", "qux" },
                                                                                                   { "bar", "baz" },
                                                                                                   { "bar", "baz", "qux" },
                                                                                                   { "foo", "baz" },
                                                                                                   { "foo", "baz", "qux" },
                                                                                                   { "foo", "bar", "baz" },
                                                                                                   { "foo", "bar", "baz", "qux" }});

    CHECK(((foo && bar) || (baz && qux)).solve({ "foo", "bar", "baz", "qux" }) == set<set<string>>{{ "foo", "bar" },
                                                                                                   { "baz", "qux" },
                                                                                                   { "foo", "bar", "baz" },
                                                                                                   { "foo", "bar", "qux" },
                                                                                                   { "baz", "qux", "foo" },
                                                                                                   { "baz", "qux", "bar" },
                                                                                                   { "foo", "bar", "baz", "qux" }});


    CHECK(((foo || bar) && (baz || qux)).solve2({ "foo", "bar", "baz", "qux" }) == set<set<string>>{{ "bar", "qux" },
                                                                                                    { "foo", "qux" },
                                                                                                    { "foo", "bar", "qux" },
                                                                                                    { "bar", "baz" },
                                                                                                    { "bar", "baz", "qux" },
                                                                                                    { "foo", "baz" },
                                                                                                    { "foo", "baz", "qux" },
                                                                                                    { "foo", "bar", "baz" },
                                                                                                    { "foo", "bar", "baz", "qux" }});

    CHECK(((foo && bar) || (baz && qux)).solve2({ "foo", "bar", "baz", "qux" }) == set<set<string>>{{ "foo", "bar" },
                                                                                                    { "baz", "qux" },
                                                                                                    { "foo", "bar", "baz" },
                                                                                                    { "foo", "bar", "qux" },
                                                                                                    { "baz", "qux", "foo" },
                                                                                                    { "baz", "qux", "bar" },
                                                                                                    { "foo", "bar", "baz", "qux" }});
  }
}
