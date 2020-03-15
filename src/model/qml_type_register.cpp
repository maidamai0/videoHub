#include "qml_type_register.h"

#include <qmetaobject.h>

#include <QString>
#include <type_traits>

#include "model/configuration.h"
#include "model/new_item_page.h"
#include "qqml.h"

std::vector<std::function<void(const char *uri)>> Register::register_functions_;

void Register::registerTypes(const char *uri) {
  Q_ASSERT(uri == QLatin1String("model"));
  register_qml_type<NewItemModel>();
  register_qml_type<ConfigModel>();

  // for (const auto &fn : register_functions_) {
  //   fn(uri);
  // }
}

void Register::AddRegisterFunctions(std::function<void(const char *uri)> fn) {
  register_functions_.emplace_back(fn);
}
