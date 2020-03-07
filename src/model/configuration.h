#pragma once

/**
 * @file configuration.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   configuration model of video_hub, proxy of confugration file and ui
 * @version 0.1
 * @date 2020-03-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <QObject>

#include "../common/global_def.h"

class ConfigModel : public QObject {
  Q_OBJECT
  QPROP(QString, httpProxy, HttpProxy);

 public:
  ConfigModel();
};
