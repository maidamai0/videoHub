#pragma once

/**
 * @file app.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-03-08
 *
 * @copyright Copyright (c) 2020
 *
 */

/**
 * @brief application
 *
 */
#include "common/ref_ptr.h"
#include "qqml.h"
#include "qqmlapplicationengine.h"

class APP final {
 public:
  static APP& GetInstance();

  void SetQmlEngine(QQmlApplicationEngine* engine) {
    qml_engine_ = RefPtr<QQmlApplicationEngine>(engine);
  }
  RefPtr<QQmlApplicationEngine> GetRootContext() const { return qml_engine_; }

 private:
  APP();

 private:
  RefPtr<QQmlApplicationEngine> qml_engine_;
};