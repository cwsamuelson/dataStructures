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
        CHECK(!j.is_number());
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
        CHECK(!j.is_number());
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
        CHECK(!j.is_number());
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
        CHECK(!j.is_number());
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
        CHECK(!j.is_number());
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
        CHECK(!j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
      }
    }

    SECTION("'signed integer' type") {
      SECTION("signed short") {
        SECTION("from var") {
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
          CHECK(j.is_number());
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
          CHECK(j.is_number());
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
          CHECK(j.is_number());
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
          CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
      CHECK(!j.is_number());
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
      CHECK(!j.is_number());
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
      CHECK(!j.is_number());
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
        CHECK(!j.is_number());
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
        CHECK(!j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
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
        CHECK(j.is_number());
      }
    }
  }

  SECTION("Get what's available, cast as feasible"){
    SECTION("Numbers"){
      gsw::json j = 5;

      CHECK(j.get<int>() == 5);
      CHECK(j.get<short>() == 5);
      CHECK(j.get<long>() == 5);
      CHECK(j.get<long long>() == 5);
      CHECK(j.get<unsigned int>() == 5);
      CHECK(j.get<unsigned short>() == 5);
      CHECK(j.get<unsigned long>() == 5);
      CHECK(j.get<unsigned long long>() == 5);
    }
  }
}

