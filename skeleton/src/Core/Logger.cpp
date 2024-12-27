#include <skeleton/Core/Logger.hpp>
#include <cstdarg>
#include <ctime>
#include <iomanip>
#include <iostream>
skeleton::Logger* skeleton::Logger::instance = nullptr;
namespace skeleton {
Logger::Logger() = default;

Logger::~Logger() = default;

Logger *Logger::get_instance() {
  if (!instance) {
    instance = new Logger();
  }
  return instance;
}

void Logger::log(const std::string &entry) {
  skeleton::Logger::print("Log", entry);
}
void Logger::info(const std::string &entry) {
  skeleton::Logger::print("Info", entry);
}
void Logger::error(const std::string &entry) {
  skeleton::Logger::print("Error", entry);
}
void Logger::warning(const std::string &entry) {
  skeleton::Logger::print("Warning", entry);
}

void Logger::logf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  custom_printf("Log", format, args);
  va_end(args);
}

void Logger::print(const std::string &type, const std::string &entry) {
  std::time_t now = std::time(0);
  std::tm *ltm = std::localtime(&now);

  std::cout << "[" << std::put_time(ltm, "%H:%M:%S") << "] [" << type
            << "]: " << entry << std::endl;
}

void Logger::custom_printf(const std::string &type, const char *format, ...) {
  std::time_t now = std::time(nullptr);
  std::tm *ltm = std::localtime(&now);

  va_list args;
  va_start(args, format);
  std::cout << "[" << std::put_time(ltm, "%H:%M:%S") << "] [" << type << "]: ";
  vprintf(format, args);
  va_end(args);
}
} // namespace skeleton
