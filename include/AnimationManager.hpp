#ifndef SKELETON_ANIMATION_MANAGER_HPP
#define SKELETON_ANIMATION_MANAGER_HPP
#include <string>
#include <map>
namespace skeleton {
class AnimationManager {

  public:
	AnimationManager() {}
	~AnimationManager() {}

	void add_animation(std::string name, int animation_row);
	int &get_animation(std::string name);

  private:
	std::map<std::string, int> animations;
};
}; // namespace skeleton

#endif