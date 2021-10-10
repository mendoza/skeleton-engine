#include <AnimationManager.hpp>

namespace skeleton {
void AnimationManager::addAnimation(std::string Name, int AnimationRow) {
	this->Animations[Name] = AnimationRow;
}

int &AnimationManager::getAnimation(std::string Name) {
	return this->Animations.at(Name);
}
}; // namespace skeleton