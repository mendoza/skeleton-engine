#ifndef SCRIPT_MANAGER_HPP
#define SCRIPT_MANAGER_HPP
#include "Logger.hpp"
#include "SkeletonRenderer.hpp"
#include <SDL.h>
#include <sol/sol.hpp>

namespace skeleton {
class ScriptManager {
  public:
	sol::state lua;
	ScriptManager() { lua.open_libraries(sol::lib::base); }
	~ScriptManager() = default;

	void register_function(const std::string &name, sol::function callback);
	template <typename T> void register_class(const std::string &name);
	sol::table get_table(std::string variable);
	void load_script_file(const std::string &filename);
	void set_engine_data();
};
}; // namespace skeleton

#endif
