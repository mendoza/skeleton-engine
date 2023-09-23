#include "ScriptManager.hpp"

namespace skeleton {

void ScriptManager::register_function(const std::string &name,
									  sol::function callback) {
	lua[name] = callback;
}

template <typename T>
void ScriptManager::register_class(const std::string &name) {
	lua.new_usertype<T>(name);
}

void ScriptManager::load_script_file(const std::string &filename) {
	set_engine_data();
	lua.script_file(filename);
}

void ScriptManager::set_engine_data() {
	lua.new_usertype<skeleton::Logger>(
		"Logger", "log", &skeleton::Logger::log, "warning",
		&skeleton::Logger::warning, "error", &skeleton::Logger::error, "create",
		&skeleton::Logger::get_instance);
	skeleton::Logger *logger = logger->get_instance();
	lua["console"] = logger;

	// Expose the necessary SDL structs
	lua.new_usertype<SDL_Color>("SDL_Color", "r", &SDL_Color::r, "g",
								&SDL_Color::g, "b", &SDL_Color::b, "a",
								&SDL_Color::a);
	lua.new_usertype<SDL_Rect>("SDL_Rect", "x", &SDL_Rect::x, "y", &SDL_Rect::y,
							   "h", &SDL_Rect::h, "w", &SDL_Rect::w);

	lua.new_usertype<SDL_Texture>("SDL_Texture");

	lua.new_usertype<skeleton::SkeletonRenderer>(
		"SkeletonRenderer", "new", sol::no_constructor, "update",
		&skeleton::SkeletonRenderer::update, "clear",
		&skeleton::SkeletonRenderer::clear, "shutdown",
		&skeleton::SkeletonRenderer::shutdown, "draw_rect",
		&skeleton::SkeletonRenderer::draw_rect, "get_window_width",
		&skeleton::SkeletonRenderer::get_window_width, "draw_texture",
		&skeleton::SkeletonRenderer::draw_texture, "get_window_height",
		&skeleton::SkeletonRenderer::get_window_height, "set_clear_color",
		&skeleton::SkeletonRenderer::set_clear_color);
}
sol::table ScriptManager::get_table(std::string variable) {
	sol::table table = lua[variable];
	return table;
}
} // namespace skeleton