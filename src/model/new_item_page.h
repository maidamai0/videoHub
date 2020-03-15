#pragma once

/**
 * @file new_item_page.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-03-08
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "common/global_def.h"
#include "icons.h"
#include "qobject.h"
#include "qobjectdefs.h"

class VH_EXPORT NewItemModel : public QObject {
  Q_OBJECT

  QPROP(QString, address, Address)

 public:
  static NewItemModel* GetInstance();

  //  private:
  NewItemModel();
};
