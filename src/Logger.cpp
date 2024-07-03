#include "Logger.h"
#include <format>
#include <chrono>
#include <thread>

Logger::Logger(LogLevel level, std::string name, std::ostream* stream) {
    this->level = level;
    this->name = name;
    this->stream = stream;
}


Logger& Logger::log(LogLevel level, std::string message) {
    if (this->level <= level) {
        std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
        std::string timeString = std::format("{0:%c}", time);
        *stream << "[" << timeString << "] [" << std::this_thread::get_id() << "] ["  << name << "] " << text[(int) level] << " " << message << std::endl;
    }
    return *this;
}

Logger& Logger::debug(std::string message) {
    log(LogLevel::DEBUG, message);
    return *this;
}

Logger& Logger::info(std::string message) {
    log(LogLevel::INFO, message);
    return *this;
}

Logger& Logger::warn(std::string message) {
    log(LogLevel::WARN, message);
    return *this;
}

Logger& Logger::error(std::string message) {
    log(LogLevel::ERROR, message);
    return *this;
}

Logger& Logger::fatal(std::string message) {
    log(LogLevel::FATAL, message);
    return *this;
}

Logger& Logger::setLevel(LogLevel level) {
    this->level = level;
    return *this;
}