#include <ctime>
#include <iomanip>
#include <iostream>
#include <skeleton/core/Logger.hpp>

namespace skeleton::core {

std::deque<Logger::Entry> Logger::s_entries;

void Logger::print(Level level, const std::string &label,
                   const std::string &msg) {
  std::time_t now = std::time(nullptr);
  std::tm *t = std::localtime(&now);

  char timebuf[16];
  std::strftime(timebuf, sizeof(timebuf), "%H:%M:%S", t);

  std::cout << "[" << timebuf << "] [" << label << "]: " << msg << "\n";

  s_entries.push_back({level, timebuf, msg});
  if (s_entries.size() > kMaxEntries)
    s_entries.pop_front();
}

void Logger::log(const std::string &msg) { print(Level::Log, "Log", msg); }
void Logger::info(const std::string &msg) { print(Level::Info, "Info", msg); }
void Logger::warning(const std::string &msg) {
  print(Level::Warning, "Warning", msg);
}
void Logger::error(const std::string &msg) {
  print(Level::Error, "Error", msg);
}

} // namespace skeleton::core
