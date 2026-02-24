#pragma once
#include <deque>
#include <string>

namespace skeleton::core {

class Logger {
public:
  enum class Level { Log, Info, Warning, Error };

  struct Entry {
    Level level;
    std::string time;
    std::string msg;
  };

  static void log(const std::string &msg);
  static void info(const std::string &msg);
  static void warning(const std::string &msg);
  static void error(const std::string &msg);

  static const std::deque<Entry> &entries() { return s_entries; }
  static void clear() { s_entries.clear(); }

private:
  static void print(Level level, const std::string &label,
                    const std::string &msg);

  static constexpr size_t kMaxEntries = 200;
  static std::deque<Entry> s_entries;
};

} // namespace skeleton::core
