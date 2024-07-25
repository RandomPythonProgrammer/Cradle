#pragma once
#include <ostream>
#include <string>

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
};

const std::string text[] = {
    "\033[0;30mDEBUG\033[39;49m",
    "\033[0;36mINFO\033[39;49m",
    "\033[0;33mWARN\033[39;49m",
    "\033[0;91mERROR\033[39;49m",
    "\033[0;31mFATAL\033[39;49m",
};

class Logger {
   private:
    LogLevel level;
    std::string name;
    std::ostream* stream;

   public:
    Logger(LogLevel level, std::string name, std::ostream* stream);
    Logger& log(LogLevel level, std::string message);
    Logger& debug(std::string message);
    Logger& info(std::string message);
    Logger& warn(std::string message);
    Logger& error(std::string message);
    Logger& fatal(std::string message);
    Logger& setLevel(LogLevel level);
};
