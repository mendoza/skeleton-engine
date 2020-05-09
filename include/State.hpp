#pragma once
#include <SFML/System/Clock.hpp>
namespace Skeleton {
class State {

  public:
	virtual void init() = 0;
	virtual void handleInput() = 0;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual void pause() {}
	virtual void resume() {}

	sf::Clock Clock;
};
}; // namespace Skeleton