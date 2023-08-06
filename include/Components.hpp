#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP

#include <AnimationManager.hpp>
#include <GameData.hpp>
#include <SDL2/SDL.h>
#include <Spritesheet.hpp>
#include <sol.hpp>

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
	GraphicComponent(sol::table graphic_component) {
		// data->asset_manager.add_surface(this->name,
		// 								graphic_component["sprite_filepath"]);
		// this->spritesheet_image =
		// data->asset_manager.get_surface(this->name);

		this->spritesheet = new skeleton::Spritesheet(
			graphic_component["sprite_filepath"], 4, 3);
	}
	~GraphicComponent() { delete this->spritesheet; }

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

  private:
	skeleton::Spritesheet *spritesheet;
};

#endif