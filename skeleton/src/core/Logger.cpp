#include <ctime>
#include <iomanip>
#include <iostream>
#include <skeleton/core/Logger.hpp>

namespace skeleton::core {

void Logger::print(const std::string &level, const std::string &msg) {
    std::time_t now = std::time(nullptr);
    std::tm *t = std::localtime(&now);
    std::cout << "[" << std::put_time(t, "%H:%M:%S") << "] [" << level << "]: " << msg << "\n";
}

void Logger::log(const std::string &msg)     { print("Log",     msg); }
void Logger::info(const std::string &msg)    { print("Info",    msg); }
void Logger::warning(const std::string &msg) { print("Warning", msg); }
void Logger::error(const std::string &msg)   { print("Error",   msg); }

} // namespace skeleton::core
