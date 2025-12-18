#include <version/semver.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

using namespace flp;

TEST_CASE("`Version`::`Generic`") {
}

TEST_CASE("`Version`::`SemVer`::Construction") {
  SECTION("major") {
    flp::Version::Semantic version(1);
    const auto rev0 = version;

    CHECK(version.major() == 1);
    CHECK(version.minor() == 0);
    CHECK(version.patch() == 0);

    version.major(4);
    version.minor(5);
    version.patch(6);

    CHECK(version.major() == 4);
    CHECK(version.minor() == 5);
    CHECK(version.patch() == 6);

    const auto rev1 = version;

    CHECK(rev0 != rev1);
    CHECK(rev1 == version);
  }

  SECTION("major-pre_release") {
  }

  SECTION("major-build") {
  }

  SECTION("major-pre_release-build") {
  }

  SECTION("major-minor") {
    flp::Version::Semantic version(1, 2);
    const auto rev0 = version;

    CHECK(version.major() == 1);
    CHECK(version.minor() == 2);
    CHECK(version.patch() == 0);

    version.major(4);
    version.minor(5);
    version.patch(6);

    CHECK(version.major() == 4);
    CHECK(version.minor() == 5);
    CHECK(version.patch() == 6);

    const auto rev1 = version;

    CHECK(rev0 != rev1);
    CHECK(rev1 == version);
  }

  SECTION("major-minor-pre_release") {
  }

  SECTION("major-minor-build") {
  }

  SECTION("major-minor-pre_release-build") {
  }

  SECTION("major-minor-patch") {
    flp::Version::Semantic version(1, 2, 3);
    const auto rev0 = version;

    CHECK(version.major() == 1);
    CHECK(version.minor() == 2);
    CHECK(version.patch() == 3);

    version.major(4);
    version.minor(5);
    version.patch(6);

    CHECK(version.major() == 4);
    CHECK(version.minor() == 5);
    CHECK(version.patch() == 6);

    const auto rev1 = version;

    CHECK(rev0 != rev1);
    CHECK(rev1 == version);
  }

  SECTION("major-minor-patch-pre_release") {
  }

  SECTION("major-minor-patch-build") {
  }

  SECTION("major-minor-patch-pre_release-build") {
  }
}

TEST_CASE("`Version`::`SemVer`::Comparison") {
  rc::prop("different major", [](const size_t minor, const size_t patch) {
    const auto major1 = *rc::gen::arbitrary<size_t>();
    const auto diff = *rc::gen::nonZero<uint8_t>();
    const auto major2 = major1 + diff;

    flp::Version::Semantic rev1(major1, minor, patch);
    flp::Version::Semantic rev2(major2, minor, patch);

    RC_ASSERT(rev1 <  rev2);
    RC_ASSERT(rev1 <= rev2);
    RC_ASSERT(rev2 >  rev1);
    RC_ASSERT(rev2 >= rev1);
  });

  rc::prop("different minor", [](const size_t major, const size_t patch) {
    const auto minor1 = *rc::gen::arbitrary<size_t>();
    const auto diff = *rc::gen::nonZero<uint8_t>();
    const auto minor2 = minor1 + diff;

    flp::Version::Semantic rev1(major, minor1, patch);
    flp::Version::Semantic rev2(major, minor2, patch);

    RC_ASSERT(rev1 <  rev2);
    RC_ASSERT(rev1 <= rev2);
    RC_ASSERT(rev2 >  rev1);
    RC_ASSERT(rev2 >= rev1);
  });

  rc::prop("different patch", [](const size_t major, const size_t minor) {
    const auto patch1 = *rc::gen::arbitrary<size_t>();
    const auto diff = *rc::gen::nonZero<uint8_t>();
    const auto patch2 = patch1 + diff;

    flp::Version::Semantic rev1(major, minor, patch1);
    flp::Version::Semantic rev2(major, minor, patch2);

    RC_ASSERT(rev1 <  rev2);
    RC_ASSERT(rev1 <= rev2);
    RC_ASSERT(rev2 >  rev1);
    RC_ASSERT(rev2 >= rev1);
  });

  rc::prop("Pre-Release implies older", [](const size_t major, const size_t minor, const size_t patch) {
    flp::Version::Semantic rev1(major, minor, patch);
    flp::Version::Semantic rev2(major, minor, patch, flp::Version::Semantic::PreRelease{});

    RC_ASSERT(rev2 <  rev1);
    RC_ASSERT(rev2 <= rev1);
  });

  rc::prop("Build implies older", [](const size_t major, const size_t minor, const size_t patch) {
    flp::Version::Semantic rev1(major, minor, patch);
    flp::Version::Semantic rev2(major, minor, patch, flp::Version::Semantic::Build{});

    RC_ASSERT(rev2 <  rev1);
    RC_ASSERT(rev2 <= rev1);
  });
}
