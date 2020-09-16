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

#include "logger.h"
#include "spdlog/common.h"

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

    [[nodiscard]] auto GetLogLevel() const {
        if (log_level_ == "trace") {
            return spdlog::level::trace;
        }

        if (log_level_ == "debug") {
            return spdlog::level::debug;
        }

        if (log_level_ == "info") {
            return spdlog::level::info;
        }

        if (log_level_ == "warn") {
            return spdlog::level::warn;
        }

        if (log_level_ == "err") {
            return spdlog::level::err;
        }

        return spdlog::level::warn;
    }

   private:
    Database() = default;
    std::string font_path_;
    std::string log_level_;
};