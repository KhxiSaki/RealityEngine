#include "CoreLog.h"

/**
 *
 * Usage Example
 * Here’s how you can initialize and use the logging system in your main function or any other part of your code:
 * #include "CoreLog.h"
 *
 *int main() {
 *   Logger::Init();
 *
 * REALITY_LOG(LogCategory::LogTemp, info, "This is an info message!");
 * REALITY_LOG(LogCategory::LogTemp, warn, "This is a warning message!");
 * REALITY_LOG(LogCategory::LogTemp, error, "This is an error message!");
 * REALITY_LOG(LogCategory::LogTemp, critical, "This is a fatal error message!");
 *
 * REALITY_LOG(LogCategory::LogTemp, trace, "This is a verbose message!");
 * REALITY_LOG(LogCategory::LogTemp, debug, "This is a very verbose message!");
 *
 *   return 0;
 * }
 */

// Initialize static member
std::unordered_map<LogCategory, std::shared_ptr<spdlog::logger>> Logger::s_Loggers;