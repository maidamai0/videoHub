#pragma once

/**
 * @file qml_type_register.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief register model to qml engine
 * @version 0.1
 * @date 2020-03-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "configuration.h"
#include "qobjectdefs.h"
#include "qqmlextensionplugin.h"

class Register : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
 public:
  Register() = default;
  ~Register() override = default;

  void registerTypes(const char* uri) override;
};
