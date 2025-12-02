#include <message-bus.hh>

#include <error_help.hh>

#include <ranges>

namespace flp {

void MessageBus::send_message(const std::string& message_id) {
  VERIFY(message_names.contains(message_id), "Trying to send unknown message name({})", message_id);

  auto&& [lower, upper] = responders.equal_range(message_id);
  for (auto iter = lower; lower != upper; ++lower) {
    const auto& [key, responder] = *iter;
    responder(key);
  }
}

void MessageBus::register_message(const std::string& message_id) {
  message_names.insert(message_id);
}

void MessageBus::register_messages(const std::vector<std::string>& message_ids) {
  message_names.insert(message_ids.begin(), message_ids.end());
}

void MessageBus::subscribe(const std::string& message_id, const std::function<void(std::string)>& functor) {
  VERIFY(message_names.contains(message_id), "Trying to subscribe to unknown message name({})", message_id);

  responders.emplace(message_id, functor);
}

}
