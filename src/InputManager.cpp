#include <InputManager.hpp>

namespace skeleton {
bool InputManager::is_sprite_clicked(sf::Sprite &object, sf::Mouse::Button button,
								   sf::RenderWindow &window) {
	if (sf::Mouse::isButtonPressed(button)) {
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y,
							 object.getGlobalBounds().width,
							 object.getGlobalBounds().height);

		if (tempRect.contains(sf::Mouse::getPosition(window))) {
			return true;
		}
	}
	return false;
}

sf::Vector2i InputManager::get_mouse_position(sf::RenderWindow &window) {
	return sf::Mouse::getPosition(window);
}
}; // namespace skeleton