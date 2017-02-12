#include "Reddit.hpp"
#include <cpr/cpr.h>
#include <fstream>
#include <json.hpp>
#include "debug.hpp"

using nlohmann::json;

bool Reddit::login() {
  cpr::Authentication auth{cid_, secret_};
  auto r = cpr::Post(
      cpr::Header{{"accept", "application/json"},
                  {"content-type", "application/x-www-form-urlencoded"},
                  {"User-Agent", "Streisand/0.1"}},
      cpr::Url{"https://www.reddit.com/api/v1/access_token"}, auth,
      cpr::Payload{{"grant_type", "password"},
                   {"username", user_},
                   {"password", pass_}});
  if (r.status_code != 200) {
    return false;
  }
  auto at = json::parse(r.text);
  auto reply = json::parse(r.text);
  auto auth_it = reply.find("access_token");
  if (auth_it == reply.end()) {
    std::cout << "Access token not found" << std::endl;
    return false;
  }
  token_ = *auth_it;
  base_header_["Authorization"] = "Bearer " + token_;
  return true;
}

cpr::Response Reddit::get_request(const std::string& path,
                                  const cpr::Parameters& params) {
  auto r = cpr::Get(base_header_, cpr::Url{baseurl + path}, params);
  return r;
}

json Reddit::list_subreddit(const std::string& sub, size_t limit) {
  auto r = get_request(sub, {{"limit", std::to_string(limit)}});
  json j = json::parse(r.text);
  return j;
}
