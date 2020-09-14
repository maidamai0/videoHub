#include "logger.h"

#include <memory>

#include "database.h"
#include "spdlog/common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

constexpr auto kLogFileName = "video_hub.log";

// see https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
constexpr auto kLogPattern = R"([%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] [%g:%# %!] %v)";
constexpr auto kTraceLogPattern = R"([%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] %v)";

Logger::Logger() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(kLogFileName, true);
    logger_ = std::make_shared<spdlog::logger>("logger",
                                               spdlog::sinks_init_list{console_sink, file_sink});

    spdlog::register_logger(logger_);
    spdlog::set_pattern(kLogPattern);
    logger_->flush_on(spdlog::level::debug);

#ifdef NDEBUG
    logger->set_level(Database::GetInstance().GetLogLevel());
#else
    logger_->set_level(spdlog::level::trace);
#endif
}

Logger::TraceGuard::TraceGuard(std::string&& name) : name_(name) {
    spdlog::set_pattern(kTraceLogPattern);
    Logger::GetInstance().Log(spdlog::level::trace, "Enter {}", name_);
    spdlog::set_pattern(kLogPattern);
}

Logger::TraceGuard::~TraceGuard() {
    spdlog::set_pattern(kTraceLogPattern);
    Logger::GetInstance().Log(spdlog::level::trace, "Leave {}", name_);
    spdlog::set_pattern(kLogPattern);
}