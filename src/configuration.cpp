#include "configuration.h"

#include <fstream>
#include <iostream>
#include <string>

#include "toml11/toml.hpp"
#include "toml11/toml/parser.hpp"

namespace {
const std::string kConfigFileName{"settings.toml"};
}  // namespace

Config::Config() {
    auto settings = toml::parse(kConfigFileName);

    auto general = settings["general"];
    // SetLogLevel(settings["general"]["log_level"].as_integer());

    auto network = settings["network"];
    http_proxy_ = network["http_proxy"].as_string();
    http_proxy_ = network["https_proxy"].as_string();

    Print();
}

void Config::Print() {}