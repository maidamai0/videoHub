#include "configuration.h"

#include <fstream>
#include <iostream>
#include <string>

namespace {
const std::string kConfigFileName{"video_hub_settings.json"};
}  // namespace

Config::Config() {

    Print();
}

void Config::Print() {}