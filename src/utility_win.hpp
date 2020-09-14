/**
 * @file utility_win.hpp
 * @author yuantonghao@gmail.com
 * @brief   utility functions only workd on windows platform.
 * @version 0.1
 * @date 2020-09-14
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <Windows.h>
#include <objbase.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>

#include <string>

inline void open_file(std::string&& file) {
    ShellExecute(nullptr, "open", file.c_str(), nullptr, nullptr, SW_SHOW);
}
