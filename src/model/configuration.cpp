#include "configuration.h"

#include <fstream>
#include <iostream>
#include <string>

// #include "qml_type_register.h"

// namespace {
// QMLTypeRegister<ConfigModel> register_;
// }

namespace {
const std::string config_file_name{"config.toml"};
}  // namespace

ConfigModel::ConfigModel() {
  connect(this, &ConfigModel::httpProxyChanged, [this]() {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << httpProxy_.toStdString()
              << std::endl;
  });
}