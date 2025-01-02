#include <singly_linked_list.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("single linked list") {
  SinglyLinkedList<int> list;

  CHECK(list.empty());
  CHECK(list.size() == 0);

  list.push_back(42);
  CHECK(not list.empty());
  CHECK(list.size() == 1);
  CHECK(list.back() == 42);

  list.back() = 1138;
  CHECK(list.back() == 1138);

  list.pop_back();
  CHECK(list.empty());
  CHECK(list.size() == 0);

  list.push_back(42);
  list.clear();
  CHECK(list.empty());
  CHECK(list.size() == 0);
}
