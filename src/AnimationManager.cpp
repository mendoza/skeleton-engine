#include <AnimationManager.hpp>

namespace skeleton {
void AnimationManager::add_animation(std::string name, int animation_row) {
	this->animations[name] = animation_row;
}

int &AnimationManager::get_animation(std::string name) {
	return this->animations.at(name);
}
}; // namespace skeleton