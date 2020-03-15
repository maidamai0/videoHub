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

#include <functional>
#include <vector>

#include "qobjectdefs.h"
#include "qqml.h"
#include "qqmlextensionplugin.h"

class Register : public QQmlExtensionPlugin {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
 public:
  Register() = default;
  ~Register() override = default;

  void registerTypes(const char *uri) override;

  static void AddRegisterFunctions(std::function<void(const char *uri)> fn);

 private:
  template <typename QMLType>
  void register_qml_type() {
    static_assert(std::is_base_of_v<QObject, QMLType>,
                  "QMLType must be drived from QObject");
    qmlRegisterType<QMLType>("model", 1, 0,
                             QMLType::staticMetaObject.className());
  }

 private:
  static std::vector<std::function<void(const char *uri)>> register_functions_;
};

template <typename T>
void RegisterQmlType(const char *uri) {
  static_assert(std::is_base_of_v<QObject, T>, "T must be drived from QObject");
  qmlRegisterType<T>(uri, 1, 0, T::staticMetaObject.className());
}

template <typename T>
class QMLTypeRegister {
 public:
  QMLTypeRegister() { Register::AddRegisterFunctions(register_function); }
  static void register_function(const char *uri) { RegisterQmlType<T>(uri); }
};