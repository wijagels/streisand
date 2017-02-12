#pragma once
#include <cpr/cpr.h>
#include <json.hpp>
#include <string>

class Reddit {
 public:
  Reddit(const nlohmann::json &j) : json_{j} {
    cid_ = j["client_id"];
    secret_ = j["secret"];
    user_ = j["user"];
    pass_ = j["password"];
  }

  cpr::Response get_request(const std::string &,
                            const cpr::Parameters &params = cpr::Parameters{});
  nlohmann::json list_subreddit(const std::string &, size_t limit = 100);
  bool login();

  bool logged_in;

 private:
  cpr::Session session_;
  const std::string baseurl = "https://oauth.reddit.com/";
  cpr::Header base_header_{{"accept", "application/json"},
                           {"User-Agent", "Streisand/0.1"}};
  const nlohmann::json json_;
  std::string cid_;
  std::string secret_;
  std::string user_;
  std::string pass_;
  std::string token_;
};
