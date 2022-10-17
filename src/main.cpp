#include <Engine.hpp>
#include <lua.hpp>
skeleton::Logger *skeleton::Logger::instance = 0;

int main() {
	sol::state L;
	L.script_file("assets/scripts/config.lua");
	sol::table config = L["config"];
	std::string title = config["title"];
	std::string icon = config["icon"];
	sol::table initial_resolution = config["resolution"];
	unsigned int Width = initial_resolution["width"];
	unsigned int Height = initial_resolution["height"];
	sf::Vector2u resolution = {Width, Height};
	bool debug_mode = config["debug_mode"];
	bool fullscreen = config["fullscreen"];
	skeleton::Engine engine(debug_mode);
	engine.build_window(resolution, title, icon, fullscreen);
	return 0;
}
