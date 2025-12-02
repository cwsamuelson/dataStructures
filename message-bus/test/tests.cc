#include <message-bus.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

using namespace flp;

TEST_CASE("`MessageBus`") {
  rc::prop("No registered message", [](const std::string& ID) {
    MessageBus message_bus;

    RC_ASSERT_THROWS(message_bus.send_message(ID));
  });

  rc::prop("Trying to send un-registered messages", [](const std::string& ID) {
    MessageBus message_bus;

    message_bus.register_message(ID);

    const auto other_ID = *rc::gen::distinctFrom(rc::gen::arbitrary<std::string>(), ID);
    RC_ASSERT_THROWS(message_bus.send_message(other_ID));
    RC_ASSERT_THROWS(message_bus.subscribe(other_ID, [](const auto&){}));

    size_t message_counter{};
    message_bus.subscribe(ID, [&message_counter, &ID](const std::string& id) {
      RC_ASSERT(id == ID);
      ++message_counter;
    });

    RC_ASSERT(message_counter == 0);

    message_bus.send_message(ID);
    RC_ASSERT(message_counter == 1);
  });

  rc::prop("Bunch of registered messages", [](const std::vector<std::string>& message_ids) {
    MessageBus message_bus;

    message_bus.register_messages(message_ids);

    size_t messageA_counter{};
    message_bus.send_message(*rc::gen::elementOf(message_ids));

    RC_ASSERT(messageA_counter == 0);

    const auto& single_id = *rc::gen::elementOf(message_ids);
    message_bus.subscribe(single_id, [&messageA_counter](const std::string& m_id) {
      ++messageA_counter;
    });

    message_bus.send_message(single_id);

    RC_ASSERT(messageA_counter == 1);

    messageA_counter = 0;

    size_t messageB_counter{};

    for (const auto& id : message_ids) {
      message_bus.subscribe(id, [&messageB_counter, &id](const std::string& m_id) {
        RC_ASSERT(m_id == id);
        ++messageB_counter;
      });
    }

    RC_ASSERT(messageA_counter == 0);
    RC_ASSERT(messageB_counter == 0);

    for (const auto& id : message_ids) {
      message_bus.send_message(id);
    }

    RC_ASSERT(messageA_counter == 2);
    RC_ASSERT(messageB_counter == message_ids.size());
  });
}
