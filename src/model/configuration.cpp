#include "configuration.h"

#include <fstream>
#include <iostream>
#include <string>

#include "toml11/toml.hpp"
#include "toml11/toml/parser.hpp"

namespace {
const std::string config_file_name{"settings.toml"};
}  // namespace

Config::Config() {
    auto settings = toml::parse(config_file_name);

    auto general = settings["general"];
    SetLogLevel(settings["general"]["log_level"].as_integer());

    auto network = settings["network"];
    http_proxy_ = network["http_proxy"].as_string();
    http_proxy_ = network["https_proxy"].as_string();

    Print();
}

void Config::Print() {}