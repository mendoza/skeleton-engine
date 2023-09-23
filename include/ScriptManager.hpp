#ifndef SCRIPT_MANAGER_HPP
#define SCRIPT_MANAGER_HPP
#include <sol/sol.hpp>

namespace skeleton {
class ScriptManager {
  public:
	sol::state lua;
	ScriptManager() { lua.open_libraries(sol::lib::base); }
	~ScriptManager() = default;

	void registerFunction(const std::string &name, sol::function callback) {
		lua[name] = callback;
	}

	template <typename T> void registerClass(const std::string &name) {
		lua.new_usertype<T>(name);
	}

	void loadScriptFile(const std::string &filename) {
		lua.script_file(filename);
	}
};
}; // namespace skeleton

#endif