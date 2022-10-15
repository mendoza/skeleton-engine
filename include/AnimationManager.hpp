#ifndef SKELETON_ANIMATION_MANAGER_HPP
#define SKELETON_ANIMATION_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace skeleton {
class AnimationManager {

  public:
	AnimationManager() {}
	~AnimationManager() {}

	void addAnimation(std::string Name, int AnimationRow);
	int &getAnimation(std::string Name);

  private:
	std::map<std::string, int> Animations;
};
}; // namespace skeleton

#endif