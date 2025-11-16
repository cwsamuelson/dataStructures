#pragma once

namespace flp::Net {

// https://man7.org/linux/man-pages/man5/protocols.5.html
// https://man7.org/linux/man-pages/man3/getprotoent.3.html

// The protocol interface is how you're 'supposed' to get the level ID number when using the [gs]etsockopt interface.

auto get_protocols() {
  std::map<std::string, size_t> protocol_ids;
  std::multimap<size_t, std::string> protocol_names;

  // Open the protocol database
  setprotoent(1);

  // Read entries until EOF
  for (protoent* protocol = getprotoent(); protocol != nullptr; protocol = getprotoent()) {
    for (char** alias = protocol->p_aliases; *alias != nullptr; alias++) {
      protocol_ids[*alias] = protocol->p_proto;
      protocol_names.emplace(protocol->p_proto, *alias);
    }
  }

  // Close the protocol database
  endprotoent();

  return std::make_tuple(protocol_ids, protocol_names);
}

auto get_protocol_ids() {
  const auto&& [ids, names] = get_protocols();
  return ids;
}

auto get_protocol_names() {
  const auto&& [ids, names] = get_protocols();
  return names;
}

}
