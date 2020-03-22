#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include <json.hh>

TEST_CASE("Json objects do json like things!", "[json]") {
  SECTION("Construct from any") {
    SECTION("'uninit' type") {
      gsw::json j;

      CHECK(!j.is_object());
      CHECK(!j.is_array());
      CHECK(!j.is_string());
      CHECK(!j.is_integer());
      CHECK(!j.is_floating());
      CHECK(!j.is_bool());
      CHECK(!j.is_signed());
      CHECK(!j.is_unsigned());
    }

    SECTION("'object' type") {
      SECTION("By std::map") {
        gsw::json j(std::map<std::string, int>{{ "A", 1 },
                                               { "B", 2 },
                                               { "C", 3 }});

        CHECK(j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(!j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("By initializer list") {
        gsw::json j;
        /*gsw::json j{{ "A", 1 },
                    { "B", 2 },
                    { "C", 3 }};*/

        CHECK(j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(!j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(!j.is_unsigned());
      }
    }

    SECTION("'array' type") {
      SECTION("std::vector") {
        gsw::json j(std::vector<int>{ 1, 2, 3, 4, 5 });

        CHECK(!j.is_object());
        CHECK(j.is_array());
        CHECK(!j.is_string());
        CHECK(!j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("from initializer list") {
        gsw::json j{ 1, 2, 3, 4, 5 };

        CHECK(!j.is_object());
        CHECK(j.is_array());
        CHECK(!j.is_string());
        CHECK(!j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(!j.is_unsigned());
      }
    }

    SECTION("'string' type") {
      SECTION("cstring") {
        gsw::json j("");

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(j.is_string());
        CHECK(!j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("std::string") {
        gsw::json j(std::string(""));

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(j.is_string());
        CHECK(!j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(!j.is_unsigned());
      }
    }

    SECTION("'unsigned integer' type") {
      SECTION("unsigned short") {
        unsigned short i = 5;
        gsw::json j(i);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(j.is_unsigned());
      }

      SECTION("unsigned int") {
        unsigned int i = 5;
        gsw::json j(i);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(j.is_unsigned());
      }

      SECTION("unsigned long") {
        unsigned long i = 5;
        gsw::json j(i);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(j.is_unsigned());
      }

      SECTION("unsigned long long") {
        unsigned long long i = 5;
        gsw::json j(i);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(j.is_unsigned());
      }
    }

    SECTION("'signed integer' type") {
      SECTION("signed short") {
        signed short i = 5;
        gsw::json j(i);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("signed int") {
        signed int i = 5;
        gsw::json j(i);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("signed long") {
        signed long i = 5;
        gsw::json j(i);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("signed long long") {
        signed long long i = 5;
        gsw::json j(i);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }
    }

    SECTION("'floating point' type") {
      SECTION("float") {
        gsw::json j(0.0f);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(!j.is_integer());
        CHECK(j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("double") {
        gsw::json j(0.0);

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(!j.is_integer());
        CHECK(j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }
    }

    SECTION("'boolean' type") {
      gsw::json j(true);

      CHECK(!j.is_object());
      CHECK(!j.is_array());
      CHECK(!j.is_string());
      CHECK(!j.is_integer());
      CHECK(!j.is_floating());
      CHECK(j.is_bool());
      CHECK(!j.is_signed());
      CHECK(!j.is_unsigned());
    }
  }

  SECTION("Assign from any") {
    gsw::json j;

    SECTION("from object/map") {
      j = std::map<std::string, int>{{ "A", 1 },
                                     { "B", 2 },
                                     { "C", 3 }};

      CHECK(j.is_object());
      CHECK(!j.is_array());
      CHECK(!j.is_string());
      CHECK(!j.is_integer());
      CHECK(!j.is_floating());
      CHECK(!j.is_bool());
      CHECK(!j.is_signed());
      CHECK(!j.is_unsigned());
    }

    SECTION("from array/vector") {
      j = std::vector{ 1, 2, 3, 4, 5 };

      CHECK(!j.is_object());
      CHECK(j.is_array());
      CHECK(!j.is_string());
      CHECK(!j.is_integer());
      CHECK(!j.is_floating());
      CHECK(!j.is_bool());
      CHECK(!j.is_signed());
      CHECK(!j.is_unsigned());
    }

    SECTION("from string") {
      SECTION("cstring") {
        j = "test";

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(j.is_string());
        CHECK(!j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("std::string") {
        j = std::string("test");

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(j.is_string());
        CHECK(!j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(!j.is_unsigned());
      }
    }

    SECTION("from 'floating point' type") {
      SECTION("float") {
        j = 0.0f;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(!j.is_integer());
        CHECK(j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("double") {
        j = 0.0;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(!j.is_integer());
        CHECK(j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }
    }

    SECTION("'unsigned integer' type") {
      SECTION("unsigned short") {
        unsigned short i = 5;
        j = i;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(j.is_unsigned());
      }

      SECTION("unsigned int") {
        unsigned int i = 5;
        j = i;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(j.is_unsigned());
      }

      SECTION("unsigned long") {
        unsigned long i = 5;
        j = i;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(j.is_unsigned());
      }

      SECTION("unsigned long long") {
        unsigned long long i = 5;
        j = i;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(!j.is_signed());
        CHECK(j.is_unsigned());
      }
    }

    SECTION("'signed integer' type") {
      SECTION("signed short") {
        signed short i = 5;
        j = i;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("signed int") {
        signed int i = 5;
        j = i;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("signed long") {
        signed long i = 5;
        j = i;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }

      SECTION("signed long long") {
        signed long long i = 5;
        j = i;

        CHECK(!j.is_object());
        CHECK(!j.is_array());
        CHECK(!j.is_string());
        CHECK(j.is_integer());
        CHECK(!j.is_floating());
        CHECK(!j.is_bool());
        CHECK(j.is_signed());
        CHECK(!j.is_unsigned());
      }
    }
  }
}

