#ifndef SKELETON_LOGGER_HPP
#define SKELETON_LOGGER_HPP

#include <cstdarg>
#include <ctime>
#include <iostream>
#include <string>
namespace skeleton {
class Logger {
  public:
	static Logger *instance;
	static Logger *get_instance();
	static void log(const std::string &);
	static void info(const std::string &);
	static void logf(const char *format, ...);
	static void error(const std::string &);
	static void warning(const std::string &);
	~Logger();

  private:
	Logger();
	static void print(const std::string &, const std::string &);
	static void custom_printf(const std::string &, const char *format, ...);
};
} // namespace skeleton

#endif
