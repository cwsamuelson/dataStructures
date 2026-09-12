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

  list.push_front(42);
  CHECK(not list.empty());
  CHECK(list.size() == 1);
  CHECK(list.front() == 42);

  list.front() = 1138;
  CHECK(list.front() == 1138);

  list.pop_front();
  CHECK(list.empty());
  CHECK(list.size() == 0);

  list.push_front(42);
  CHECK(list.front() == 42);
  list.front() = 1138;
  CHECK(list.front() == 1138);

  list.clear();

  CHECK(list.empty());
  CHECK(list.size() == 0);

  list.push_front(1138);
  list.push_front(42);

  CHECK(not list.empty());
  CHECK(list.size() == 2);
  CHECK(list.front() == 42);

  list.pop_front();

  CHECK(not list.empty());
  CHECK(list.size() == 1);
  CHECK(list.front() == 1138);

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
      list.push_front(0);

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
    init_data.push_front(0);
    init_data.push_front(1);
    init_data.push_front(2);
    init_data.push_front(3);
    init_data.push_front(4);

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
      list.push_front(6);

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

SCENARIO("`SinglyLinkedList`::Iterable") {
  GIVEN("A populated list") {
    SinglyLinkedList<int> list;

    list.push_front(0);
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    WHEN("The list is iterated") {
      auto iterate = [&list] {
        for (size_t counter{}; const auto& element : list) {
          CHECK(element == counter++);
        }
      };

      THEN("The list values are observable") {
        iterate();
      }
    }

    WHEN("The list is modified during iteration") {
      for (auto& element : list) {
        ++element;
      }

      THEN("The modified values are reflected in the list") {
        for (size_t counter{1}; const auto& element : list) {
          CHECK(element == counter++);
        }
      }
    }
  }
}
