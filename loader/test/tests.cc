#include <loader.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

#include <nlohmann/json.hpp>

#include <fstream>

using namespace flp;
using nlohmann::json;

TEST_CASE("`Loader`") {
  bool loaded = false;
  Loader<json> loader(
    [&loaded](const std::filesystem::path& path) {
      std::ifstream file(path);
      loaded = true;
      return json::parse(file);
    }
  );

  const auto handle = loader.load("test.json");
  CHECK(not loaded);
  const auto data = *handle;
  CHECK(loaded);

  CHECK(data.is_object());
  CHECK(not data.empty());
  REQUIRE(data.contains("magic"));
  CHECK(data.at("magic") == "foo");

  // rc::prop("different major", [](const size_t var) {
  //   RC_ASSERT(true);
  // });
}
