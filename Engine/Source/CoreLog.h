#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>
#include <unordered_map>

// Define log categories
enum class LogCategory {
    LogTemp,
    LogCore,
    LogGame
};

// Convert log category to string
inline const char* LogCategoryToString(LogCategory category) {
    switch (category) {
    case LogCategory::LogTemp: return "LogTemp";
    case LogCategory::LogCore: return "LogCore";
    case LogCategory::LogGame: return "LogGame";
    default: return "Unknown";
    }
}

// Logger wrapper class
class Logger {
public:
    static void Init() {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/engine_log.txt", true);

        console_sink->set_pattern("[%H:%M:%S] [%n] [%l] %v");
        file_sink->set_pattern("[%H:%M:%S] [%n] [%l] %v");
        
        // Initialize loggers with both console and file sinks
        for (int i = static_cast<int>(LogCategory::LogTemp); i <= static_cast<int>(LogCategory::LogGame); ++i) {
            auto category = static_cast<LogCategory>(i);
            auto name = LogCategoryToString(category);
            auto logger = std::make_shared<spdlog::logger>(name, spdlog::sinks_init_list{ console_sink, file_sink });
            logger->set_level(spdlog::level::trace);
            spdlog::register_logger(logger);
            s_Loggers[category] = logger;
        }
    }

    inline static std::shared_ptr<spdlog::logger>& GetLogger(LogCategory category) { return s_Loggers.at(category); }

private:
    static std::unordered_map<LogCategory, std::shared_ptr<spdlog::logger>> s_Loggers;
};

// Define logging macro
#define REALITY_LOG(Category, Level, ...) \
Logger::GetLogger(Category)->Level(__VA_ARGS__)