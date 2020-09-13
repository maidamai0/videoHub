#pragma once

/**
 * @file logger.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief wrapper of spdlog
 * @version 0.1
 * @date 2020-09-13
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>

#include "spdlog/common.h"
#include "spdlog/spdlog.h"

#define LOG_T(...) Logger::GetInstance().Log(__FILE__, __LINE__, spdlog::level::trace, __VA_ARGS__);
#define LOG_D(...) Logger::GetInstance().Log(__FILE__, __LINE__, spdlog::level::debug, __VA_ARGS__);
#define LOG_I(...) Logger::GetInstance().Log(__FILE__, __LINE__, spdlog::level::info, __VA_ARGS__);
#define LOG_W(...) Logger::GetInstance().Log(__FILE__, __LINE__, spdlog::level::warn, __VA_ARGS__);
#define LOG_E(...) Logger::GetInstance().Log(__FILE__, __LINE__, spdlog::level::err, __VA_ARGS__);

class Logger {
   public:
    class TraceGuard {
       public:
        explicit TraceGuard(std::string&& name);
        ~TraceGuard();

       private:
        std::string name_;
    };

    void SetLevel(spdlog::level::level_enum l) {
        logger_->set_level(l);
    }

    static auto& GetInstance() {
        static Logger instance;
        return instance;
    }

    /**
     * @brief log with source file and line
     *
     * @tparam Args     log
     * @param file      file name, __FILE__
     * @param line      line numner, __LINE__
     * @param lvl       log level
     * @param fmt       format
     * @param args      arguments used in @ref fmt
     */
    template <typename... Args>
    void Log(std::string&& file, int line, spdlog::level::level_enum lvl, std::string_view fmt,
             const Args&... args) {
        logger_->log(spdlog::source_loc{file.c_str(), line, ""}, lvl, fmt, args...);
    }

    /**
     * @brief   log without source location
     *
     * @tparam Args     log
     * @param lvl       log level
     * @param fmt       format
     * @param args      arguments used in @ref fmt
     */
    template <typename... Args>
    void Log(spdlog::level::level_enum lvl, std::string_view fmt, const Args&... args) {
        logger_->log(lvl, fmt, args...);
    }

   private:
    Logger();

    std::shared_ptr<spdlog::logger> logger_;
};