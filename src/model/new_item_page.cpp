#include "new_item_page.h"

#include <iostream>

// #include "qml_type_register.h"

// namespace {
// QMLTypeRegister<NewItemModel> register_;
// }

NewItemModel* NewItemModel::GetInstance() {
  static NewItemModel instance;
  return &instance;
}

NewItemModel::NewItemModel() {
  connect(this, &NewItemModel::addressChanged, [this]() {
    std::cout << __FILE__ << __LINE__ << ":" << address_.toStdString()
              << std::endl;
  });
}
