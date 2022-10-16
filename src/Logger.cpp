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

void Logger::print(std::string type, std::string entry) {
	std::time_t now = std::time(0);
	std::tm *ltm = std::localtime(&now);

	std::string entryTime =
		std::to_string(ltm->tm_hour) + ":" + (ltm->tm_min < 10 ? "0" : "") +
		std::to_string(ltm->tm_min) + ":" + (ltm->tm_sec < 10 ? "0" : "") +
		std::to_string(ltm->tm_sec);

	printf("[%s at %s]: %s\n", type.c_str(), entryTime.c_str(), entry.c_str());
}
} // namespace skeleton