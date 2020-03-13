#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include <logger.hh>
#include <logging_context.hh>

TEST_CASE("logger", "[]"){
  gsw::logger logger;
  logger << "test string";

  SECTION("contexts prepend text to a log message"){
    SECTION("Multiple contexts"){
      SECTION("A"){
        gsw::LoggingContext ctx(logger, "A");

        logger << "A message";
        SECTION("B"){
          gsw::LoggingContext ctx(logger, "B");

          logger << "B message";
        }

        logger << "A2 message";

        SECTION("C"){
          gsw::LoggingContext ctx(logger, "C");

          logger << "C message";
        }

        logger << "A3 message";
      }
      SECTION("D"){
        gsw::LoggingContext ctx(logger, "D");

        logger << "D message";

        {
          gsw::LoggingContext ctx(logger, "E");

          logger << "E message";
        }

        logger << "D2 message";
      }
    }
  }
}
