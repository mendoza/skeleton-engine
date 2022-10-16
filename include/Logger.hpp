#ifndef SKELETON_LOGGER_HPP
#define SKELETON_LOGGER_HPP

#include <ctime>
#include <string>

namespace skeleton {
class Logger {
  public:
	static Logger *instance;
	static Logger *get_instance();
	void log(std::string);
	void error(std::string);
	void warning(std::string);
	~Logger();

  private:
	Logger();
	void print(std::string, std::string);
};
} // namespace skeleton

#endif