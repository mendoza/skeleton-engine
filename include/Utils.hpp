#pragma once
#include <Logger.hpp>
#include <sol.hpp>
namespace skeleton {
inline void setLogger(sol::state &L) {

	sol::usertype<skeleton::Logger> loggerUserType =
		L.new_usertype<skeleton::Logger>("Logger");

	loggerUserType["log"] = &skeleton::Logger::Log;
	loggerUserType["warning"] = &skeleton::Logger::Warning;
	loggerUserType["error"] = &skeleton::Logger::Error;
	loggerUserType["create"] = &skeleton::Logger::getInstance;

	skeleton::Logger *logger = logger->getInstance();

	L["console"] = logger;
}
} // namespace skeleton