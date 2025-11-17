#include <net/hal/getaddrinfo.hh>

int main() {
  const auto conn_params = flp::Net::getaddrinfo("www.google.com", "80");
  const auto& params = conn_params.front();

  const auto s = socket((int)params.family, (int)params.type, (int)params.protocol);
  const auto conn_res = connect(s, server_info->ai_addr, server_info->ai_addrlen);

  close(s);
}
