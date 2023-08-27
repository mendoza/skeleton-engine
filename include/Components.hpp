#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP

#include "AnimationManager.hpp"
#include <SDL2/SDL.h>
#include <sol/sol.hpp>

class Component {
  public:
	virtual void update_component(float dt){};
	virtual void draw_component(){};
	virtual ~Component(){};
};
class PositionComponent : public Component {
  public:
	PositionComponent(int x, int y) {
		this->x = x;
		this->y = y;
	}
	int x, y = 0;
};

class GraphicComponent : public Component {
  public:
	std::string texture_name;
	SDL_Rect *clip;
	GraphicComponent(std::string texture_name) {
		this->texture_name = texture_name;
		this->clip = NULL;
	}

	~GraphicComponent() {}

	void update_component(float dt) override {
		// if (this->is_animated) {
		// 	this->accumulatedTime += dt;

		// 	while (accumulatedTime >= timeChunk) {
		// 		accumulatedTime -= timeChunk;
		// 		this->current_col++;
		// 	}
		// 	this->current_col %= this->cols_count;

		// 	this->frame_rect.x = this->current_col * this->frame_rect.w;

		// 	this->frame_rect.y = this->current_row * this->frame_rect.h;
		// }
	}
};

#endif