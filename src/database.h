#pragma once

/**
 * @file database.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-09-12
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <string>

class Database {
   public:
    static void Save();
    static void Load();

   private:
    Database() = default;
    std::string http_proxy_;
    std::string https_proxy_;
};
