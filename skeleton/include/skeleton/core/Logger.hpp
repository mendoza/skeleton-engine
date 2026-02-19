#pragma once
#include <string>

namespace skeleton::core {

class Logger {
public:
    static void log(const std::string &msg);
    static void info(const std::string &msg);
    static void warning(const std::string &msg);
    static void error(const std::string &msg);

private:
    static void print(const std::string &level, const std::string &msg);
};

} // namespace skeleton::core
