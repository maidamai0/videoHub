#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <iostream>

#include "app.h"
#include "common/log.h"
#include "model/configuration.h"
#include "model/new_item_page.h"
#include "qqmlapplicationengine.h"

auto main(int argc, char *argv[]) -> int {
  qInstallMessageHandler(logger);
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  app.setWindowIcon(QIcon(R"(:/VideoHub.png)"));

  QQmlApplicationEngine engine;
  engine.addPluginPath(app.applicationDirPath());

  const QUrl url(QStringLiteral("qrc:/MainWindow.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  auto model = new NewItemModel();
  engine.rootContext()->setContextProperty("new_item_model", model);
  auto config_model = new ConfigModel();
  engine.rootContext()->setContextProperty("config_model", config_model);

  return app.exec();
}
