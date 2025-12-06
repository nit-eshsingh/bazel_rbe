#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger {
private:
    std::ofstream logFile;
    LogLevel minLevel;
    std::string getCurrentTime();
    std::string levelToString(LogLevel level);

public:
    Logger(const std::string& filename, LogLevel minLevel = LogLevel::INFO);
    ~Logger();
    
    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);
    void log(LogLevel level, const std::string& message);
};

#endif // LOGGER_H
