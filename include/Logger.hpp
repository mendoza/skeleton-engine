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
	void log(std::string);
	void logf(const char *format, ...);
	void error(std::string);
	void warning(std::string);
	~Logger();

  private:
	Logger();
	void print(std::string, std::string);
	void custom_printf(std::string, const char *format, ...);
};
} // namespace skeleton

#endif