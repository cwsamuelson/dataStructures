#include <singly_linked_list.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`SinglyLinkedList`::Basic characteristics") {
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

  list.push_back(1138);
  list.push_back(42);

  CHECK(not list.empty());
  CHECK(list.size() == 2);
  CHECK(list.back() == 42);

  list.pop_back();

  CHECK(not list.empty());
  CHECK(list.size() == 1);
  CHECK(list.back() == 1138);

  list.clear();
  CHECK(list.empty());
  CHECK(list.size() == 0);
}

SCENARIO("`SinglyLinkedList`::Empty characteristics") {
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

  GIVEN("A list initialized with some data") {
    SinglyLinkedList<int> init_data;
    init_data.push_back(0);
    init_data.push_back(1);
    init_data.push_back(2);
    init_data.push_back(3);
    init_data.push_back(4);

    SinglyLinkedList<int> list(init_data);

    THEN("The list is not empty") {
      CHECK(not list.empty());
    }
    THEN("The list has a size 5") {
      CHECK(list.size() == 5);
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
      list.push_back(6);

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
}

SCENARIO("`SinglyLinkedList`::") {
}
