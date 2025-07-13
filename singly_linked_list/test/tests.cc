#include <singly_linked_list.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("single linked list") {
  SinglyLinkedList<int> list;

  CHECK(list.empty());
  CHECK(list.size() == 0);

  list.clear();

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
  CHECK(list.back() == 42);
  list.back() = 1138;
  CHECK(list.back() == 1138);

  list.clear();

  CHECK(list.empty());
  CHECK(list.size() == 0);
}

SCENARIO("Empty container exhibits typical empty container characteristics.") {
  GIVEN("A default initialized list") {
    SinglyLinkedList<int> list;

    THEN("The list is empty") {
      CHECK(list.empty());
    }
    THEN("The list has size 0") {
      CHECK(list.size() == 0);
    }

    WHEN("The container is cleared") {
      list.clear();

      THEN("The list is empty") {
        CHECK(list.empty());
      }
      THEN("The list has size 0") {
        CHECK(list.size() == 0);
      }
    }

    WHEN("Values are added to the container") {
      list.push_back(0);

      THEN("The list is not empty") {
        CHECK(not list.empty());
      }
      THEN("The list size is non-zero") {
        CHECK(list.size() != 0);
      }

      AND_WHEN("The container is cleared") {
        list.clear();

        THEN("The list is empty") {
          CHECK(list.empty());
        }
        THEN("The list has size 0") {
          CHECK(list.size() == 0);
        }
      }
    }
  }

  // The same as above, but with a list with values
  // values from ctor
}
