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

#ifdef _WIN32
#ifdef VH_EXPORT
#define VH_API __declspec(dllexport)
#else
#define VH_API __declspec(dllimport)
#endif
#else
#define VH_API
#endif