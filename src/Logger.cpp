#include "Logger.hpp"

namespace skeleton {
Logger::Logger() {}

Logger::~Logger() {}

Logger *Logger::get_instance() {
	if (!instance) {
		instance = new Logger();
	}
	return instance;
}

void Logger::log(std::string entry) { this->print("Log", entry); }
void Logger::error(std::string entry) { this->print("Error", entry); }
void Logger::warning(std::string entry) { this->print("Warning", entry); }

void Logger::logf(const char *format, ...) {
	va_list args;
	va_start(args, format);
	custom_printf("Log", format, args);
	va_end(args);
}

void Logger::print(std::string type, std::string entry) {
	std::time_t now = std::time(0);
	std::tm *ltm = std::localtime(&now);

	std::string entryTime =
		std::to_string(ltm->tm_hour) + ":" + (ltm->tm_min < 10 ? "0" : "") +
		std::to_string(ltm->tm_min) + ":" + (ltm->tm_sec < 10 ? "0" : "") +
		std::to_string(ltm->tm_sec);

	printf("[%s at %s] %s\n", type.c_str(), entryTime.c_str(), entry.c_str());
}

void Logger::custom_printf(std::string type, const char *format, ...) {
	std::time_t now = std::time(0);
	std::tm *ltm = std::localtime(&now);

	std::string entryTime =
		std::to_string(ltm->tm_hour) + ":" + (ltm->tm_min < 10 ? "0" : "") +
		std::to_string(ltm->tm_min) + ":" + (ltm->tm_sec < 10 ? "0" : "") +
		std::to_string(ltm->tm_sec);

	va_list args;
	va_start(args, format);
	std::cout << "[" << entryTime << "] ";
	vprintf(format, args);
	va_end(args);
}
} // namespace skeleton