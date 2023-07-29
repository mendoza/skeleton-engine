#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP

#include <AnimationManager.hpp>
#include <GameData.hpp>
#include <SDL2/SDL.h>
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
	GraphicComponent(skeleton::GameDataRef data, sol::table graphic_component) {
		this->name = graphic_component["sprite_name"];
		data->asset_manager.add_surface(this->name,
										graphic_component["sprite_filepath"]);
		this->spritesheet_image = data->asset_manager.get_surface(this->name);

		if (graphic_component["animated"] != sol::nil) {
			this->is_animated = graphic_component["animated"];
		}

		if (this->is_animated && graphic_component["animation"] != sol::nil) {
			sol::table animations =
				graphic_component["animation"]["animations"];
			int count = animations.size();
			for (int i = 1; i <= count; i++) {
				sol::table item = animations[i];
				this->animation_manager.add_animation(item["name"],
													  item["row"]);
			}
			int rows = graphic_component["animation"]["rows"];
			int cols = graphic_component["animation"]["cols"];

			int width = this->spritesheet_image->w / cols;
			int height = this->spritesheet_image->h / rows;

			this->timeChunk = 1.0 / float(cols);

			this->current_col = unsigned(
				graphic_component["animation"]["initial_image"]["col"]);
			this->current_row = unsigned(
				graphic_component["animation"]["initial_image"]["row"]);

			this->frame_rect = {int(this->current_col * this->frame_rect.w),
								int(this->current_row * this->frame_rect.h),
								height, width};
		}
	}
	~GraphicComponent() { SDL_FreeSurface(this->spritesheet_image); }

	void update_component(float dt) override {
		if (this->is_animated) {
			this->accumulatedTime += dt;

			while (accumulatedTime >= timeChunk) {
				accumulatedTime -= timeChunk;
				this->current_col++;
			}
			this->current_col %= this->cols_count;

			this->frame_rect.x = this->current_col * this->frame_rect.w;

			this->frame_rect.y = this->current_row * this->frame_rect.h;
		}
	}

	void play_animation(std::string name) {
		int row = this->animation_manager.get_animation(name);
		this->current_row = row;
		this->current_animation = name;
		this->accumulatedTime = 0;
	}

	std::string get_current_animation() { return this->current_animation; }

	bool get_is_animated() { return this->is_animated; }

  private:
	SDL_Rect frame_rect;
	SDL_Surface *spritesheet_image;

	uint64_t accumulatedTime = 0;
	double timeChunk = {1.0 / 60.0};
	std::string name;
	std::string current_animation;
	uint32_t current_row = 0;
	uint32_t current_col = 0;
	uint32_t rows_count = 0;
	uint32_t cols_count = 0;
	float sprite_rotation;
	bool is_animated = false;
	bool should_loop = false;
	bool played_once = false;
	skeleton::AnimationManager animation_manager;
};

#endif