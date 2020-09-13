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
    static auto& GetInstance() {
        static auto instance = Database();
        return instance;
    }

    void Save();
    void Load();

    [[nodiscard]] const auto& GetFontPath() const {
        return font_path_;
    }

   private:
    Database() = default;
    std::string font_path_;
};
