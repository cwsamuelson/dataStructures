#pragma once

#include <any>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace flp {

struct MessageBus {
  void send_message(const std::string& message_id);

  void register_message(const std::string& message_id);
  void register_messages(const std::vector<std::string>& message_ids);

  void subscribe(const std::string& message_id, const std::function<void(std::string)>& functor);

  std::multimap<std::string, std::function<void(std::string)>, std::less<>> responders;
  std::set<std::string, std::less<>> message_names;
};

} // namespace flp
