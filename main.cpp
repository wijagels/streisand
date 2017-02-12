#include <cpr/cpr.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include "Reddit.hpp"
#include "debug.hpp"

using nlohmann::json;

int main() {
  std::ifstream conf_file{"config.json"};
  if (!conf_file.is_open()) {
    loge("Unable to open configuration file at %s", "config.json");
    exit(1);
  }
  json j;
  conf_file >> j;
  auto red_conf = j["reddit"];
  Reddit reddit{red_conf};
  while (!reddit.login()) {
    usleep(1e7);
  }
  json sub = reddit.list_subreddit("/r/videos", 100);
  for (auto vid : sub["data"]["children"]) {
    auto url = vid["data"]["url"].get<std::string>();
    std::cout << url << std::endl;
  }
}
