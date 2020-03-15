#pragma once

/**
 * @file global_def.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief common used defines
 * @version 0.1
 * @date 2020-03-07
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "qobjectdefs.h"

#define QPROP(type, Rname, Wname)                                          \
  Q_PROPERTY(type Rname READ Rname WRITE Set##Wname NOTIFY Rname##Changed) \
                                                                           \
 private:                                                                  \
  type Rname##_;                                                           \
                                                                           \
 public:                                                                   \
  type Rname() const { return Rname##_; }                                  \
  void Set##Wname(const type& v) {                                         \
    if (Rname##_ == v) {                                                   \
      return;                                                              \
    } else {                                                               \
      Rname##_ = v;                                                        \
      emit Rname##Changed();                                               \
    };                                                                     \
  }                                                                        \
                                                                           \
 public:                                                                   \
  Q_SIGNAL void Rname##Changed();

#ifdef _WIN32
#ifdef VH_EXPORTDLL
#define VH_EXPORT __declspec(dllexport)
#else
#define VH_EXPORT __declspec(dllimport)
#endif
#else
#define VH_EXPORT
#endif

// #define VH_EXPORT