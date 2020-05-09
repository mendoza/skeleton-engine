#include <Engine.hpp>

int main() {
	sol::state Script;
	Script.script_file("scripts/MetaData.lua");
	sol::table Meta = Script["MetaData"];
	std::string Title = Meta["title"];
	std::string Icon = Meta["icon"];
	int Width = Meta["width"];
	int Height = Meta["height"];
	int Limit = Meta["fpsLimit"];
	bool VSync = Meta["vSync"];
	bool DebugMode = Meta["debugMode"];
	Skeleton::Engine(Width, Height, Title, Icon, Limit, VSync, DebugMode);
	return 0;
}
