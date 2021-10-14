#pragma once
#include <ctime>
#include <string>

namespace skeleton {
class Logger {
  public:
	static Logger *instance;
	static Logger *getInstance();
	void Log(std::string);
	void Error(std::string);
	void Warning(std::string);
	~Logger();

  private:
	Logger();
	void print(std::string, std::string);
};
} // namespace skeleton
