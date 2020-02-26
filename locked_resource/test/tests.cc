#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include <locked_resource.hh>

#include <thread>

TEST_CASE("Locked Resource", "[]"){
  gsw::locked_resource<int> lr;

  std::thread one([res = lr.get()](){ *res = 42; });
  std::thread two([res = lr.get()](){ *res = 24; });

  one.join();
  two.join();

  CHECK(*lr.get() == 24);
}
