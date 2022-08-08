#pragma once
#include <Engine.hpp>
#include <sol.hpp>
namespace skeleton {
inline void setLogger(sol::state &L) {
	skeleton::Logger *logger = logger->getInstance();
	L.new_usertype<skeleton::Logger>("Logger", "Log", &skeleton::Logger::Log,
									  "Warning", &skeleton::Logger::Warning,
									  "Error", &skeleton::Logger::Error);
	L.set("logger", logger);
}
} // namespace skeleton