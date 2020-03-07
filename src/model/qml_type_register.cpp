#include "qml_type_register.h"

#include "qqml.h"

void Register::registerTypes(const char *uri) {
  Q_ASSERT(uri == QLatin1String("video_hub.src.model"));
  qmlRegisterType<ConfigModel>(uri, 1, 0, "ConfigModel");
}