enum class LogLevel
{
    Debug,
    Info,
    Warn,
    Error
};
#define LOG_DEBUG(...) Logger::log(LogLevel::Debug, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) Logger::log(LogLevel::Info, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) Logger::log(LogLevel::Warn, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) Logger::log(LogLevel::Error, __FILE__, __LINE__, __VA_ARGS__)
