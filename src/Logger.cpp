#include "Logger.hpp"
#include <cstdarg>
#include <ctime>
#include <iostream>
namespace skeleton {
Logger::Logger() = default;

Logger::~Logger() = default;

Logger *Logger::get_instance() {
	if (!instance) {
		instance = new Logger();
	}
	return instance;
}

void Logger::log(const std::string& entry) { skeleton::Logger::print("Log", entry); }
void Logger::error(const std::string& entry) { skeleton::Logger::print("Error", entry); }
void Logger::warning(const std::string& entry) { skeleton::Logger::print("Warning", entry); }

void Logger::logf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	custom_printf("Log", format, args);
	va_end(args);
}

void Logger::print(const std::string& type, const std::string& entry) {
	std::time_t now = std::time(0);
	std::tm *ltm = std::localtime(&now);

	std::string entryTime =
		std::to_string(ltm->tm_hour) + ":" + (ltm->tm_min < 10 ? "0" : "") +
		std::to_string(ltm->tm_min) + ":" + (ltm->tm_sec < 10 ? "0" : "") +
		std::to_string(ltm->tm_sec);

	printf("[%s at %s] %s\n", type.c_str(), entryTime.c_str(), entry.c_str());
}

void Logger::custom_printf(const std::string& type, const char *format, ...) {
	std::time_t now = std::time(nullptr);
	std::tm *ltm = std::localtime(&now);

	std::string entryTime =
		std::to_string(ltm->tm_hour) + ":" + (ltm->tm_min < 10 ? "0" : "") +
		std::to_string(ltm->tm_min) + ":" + (ltm->tm_sec < 10 ? "0" : "") +
		std::to_string(ltm->tm_sec);

	va_list args;
	va_start(args, format);
	std::cout << "["<< type << " at "<<entryTime << "] ";
	vprintf(format, args);
	va_end(args);
}
} // namespace skeleton
