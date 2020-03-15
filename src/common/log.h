#pragma once

/**
 * @file log.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief qt message handler
 * @version 0.1
 * @date 2020-03-12
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <QString>
#include <QTime>
#include <QtGlobal>
#include <iostream>
#include <ostream>

#include "qdatetime.h"
// #include <fstream>
// #include <iostream>
// #include <mutex>

void logger(QtMsgType type, const QMessageLogContext &ctx, const QString &msg) {
  QString level;
  switch (type) {
    case QtMsgType::QtDebugMsg: {
      level = "[Debug]";
      break;
    }
    case QtMsgType::QtWarningMsg: {
      level = "[Warn]";
      break;
    }
    case QtMsgType::QtCriticalMsg: {
      level = "[Critical]";
      break;
    }
    case QtMsgType::QtFatalMsg: {
      level = "[Fatal]";
      break;
    }
    case QtMsgType::QtInfoMsg: {
      level = "[Info]";
      break;
    }
  }

  std::cout << ctx.file << "@" << ctx.line << ":" << level.toStdString() << " ["
            << QTime::currentTime().toString().toStdString() << "] "
            << msg.toStdString() << std::endl;
  //   static std::mutex mt;
  //   std::lock_guard<std::mutex> lock(mt);
  //   static std::ofstream log_file("log.log");
  //   if (log_file) {
  //     log_file << qPrintable(qFormatLogMessage(type, context, message))
  //              << std::endl;
  //   }
}