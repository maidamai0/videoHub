#include "app.h"

#include <QQmlContext>
#include <iostream>

// #include "model/configuration.h"
// #include "model/new_item_page.h"

APP& APP::GetInstance() {
  static APP instance;
  return instance;
}

APP::APP() {
  // qml_engine_->rootContext()->setContextProperty("NewItemModel",
  //                                                NewItemModel::GetInstance());
  // std::cout << "NewItemModel.address is "
  //           << NewItemModel::GetInstance()->address().toStdString()
  //           << std::endl;
}
