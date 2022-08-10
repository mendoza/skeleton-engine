#include <Engine.hpp>
skeleton::Logger *skeleton::Logger::instance = 0;

int main() {
	sol::state Script;
	Script.script_file("assets/scripts/config.lua");
	sol::table config = Script["config"];
	std::string Title = config["title"];
	std::string Icon = config["icon"];
	int Width = config["width"];
	int Height = config["height"];
	bool DebugMode = config["debug_mode"];
	skeleton::Engine engine(DebugMode);
	engine.buildWindow(Width, Height, Title, Icon);
	return 0;
}
