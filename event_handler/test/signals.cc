#include <signal.hh>

#include <catch2/catch.hpp>

using namespace gsw;

TEST_CASE("Signal tests", ""){
  bool pre_fired = false;
  bool post_fired = false;
  bool action_taken = false;
  int pre_value = 0;
  int post_value = 0;
  int action_value = 0;

  signal<void(int)> method(
          [&action_taken, &action_value](auto value){
            action_value = value;
            action_taken = true;
          });
  method.post().subscribe(
          [&post_fired, &post_value](auto value){
            post_value = value;
            post_fired = true;
          });
  method.pre().subscribe(
          [&pre_fired, &pre_value](auto value){
            pre_value = value;
            pre_fired = true;
          });

  method(42);

  CHECK(pre_fired);
  CHECK(post_fired);
  CHECK(action_taken);
  CHECK(pre_value == 42);
  CHECK(post_value == 42);
  CHECK(action_value == 42);
}
