#include "configuration.h"

#include <QDebug>
#include <fstream>
#include <iostream>
#include <string>

#include "toml11/toml.hpp"
#include "toml11/toml/parser.hpp"

namespace {
const std::string config_file_name{"settings.toml"};
}  // namespace

ConfigModel::ConfigModel() {
  auto settings = toml::parse(config_file_name);

  auto general = settings["general"];
  SetLogLevel(settings["general"]["log_level"].as_integer());

  auto network = settings["network"];
  SetHttpProxy(QString::fromStdString(network["http_proxy"].as_string()));
  SetHttpsProxy(QString::fromStdString(network["https_proxy"].as_string()));

  Print();

  connect(this, &ConfigModel::httpProxyChanged, [this]() {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << httpProxy_.toStdString()
              << std::endl;
  });
}

void ConfigModel::Print() {
  qDebug() << "settings:";

  qDebug() << "general:";
  qDebug() << "log level: " << logLevel_;

  qDebug() << "network:";
  qDebug() << "http proxy: " << httpProxy_;
  qDebug() << "https proxy: " << httpsProxy_;
}