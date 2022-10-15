#ifndef SKELETON_INPUT_MANAGER_HPP
#define SKELETON_INPUT_MANAGER_HPP

#include <SFML/Graphics.hpp>

namespace skeleton {
class InputManager {
  public:
	InputManager() {}
	~InputManager() {}
	bool isSpriteClicked(sf::Sprite &object, sf::Mouse::Button button,
						 sf::RenderWindow &window);

	sf::Vector2i getMousePosition(sf::RenderWindow &window);
};
}; // namespace skeleton

#endif