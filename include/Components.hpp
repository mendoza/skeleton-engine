#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP

#include <AnimationManager.hpp>
#include <GameData.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
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
	sf::Sprite sprite;
	GraphicComponent(skeleton::GameDataRef data, sol::table graphic_component) {
		this->name = graphic_component["sprite_name"];
		data->asset_manager.load_texture(this->name,
										 graphic_component["sprite_filepath"]);
		sf::Texture &text = data->asset_manager.get_texture(this->name);
		this->sprite.setTexture(text);
		sf::Vector2f Vector(graphic_component["sprite_orientation"]["x"],
							graphic_component["sprite_orientation"]["y"]);
		this->sprite_rotation = std::atan2(Vector.y, Vector.x) * 180 / M_PI;

		if (graphic_component["origin"] != sol::nil) {
			sf::Vector2f Origin(graphic_component["origin"]["x"],
								graphic_component["origin"]["y"]);
			this->sprite.setOrigin(Origin);
		}

		if (graphic_component["scale"] != sol::nil) {
			sf::Vector2f Scale(graphic_component["scale"]["width"],
							   graphic_component["scale"]["height"]);
			this->sprite.setScale(Scale);
		}

		if (graphic_component["position"] != sol::nil) {
			sf::Vector2f Position(graphic_component["position"]["x"],
								  graphic_component["position"]["y"]);
			this->sprite.setPosition(Position);
		}

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
			int width = this->sprite.getTextureRect().width / cols;
			int height = this->sprite.getTextureRect().height / rows;
			this->image_count = {unsigned(cols), unsigned(rows)};
			this->timeChunk = sf::seconds(1.0 / float(cols));
			this->current_image = {
				unsigned(
					graphic_component["animation"]["initial_image"]["col"]),
				unsigned(
					graphic_component["animation"]["initial_image"]["row"])};
			this->frame_rect = {
				int(this->current_image.x * this->frame_rect.width),
				int(this->current_image.y * this->frame_rect.height), height,
				width};

			sf::Vector2f Origin(frame_rect.left + (width / 2),
								frame_rect.top + (height / 2));
			this->sprite.setOrigin(Origin);

			this->sprite.setTextureRect(this->frame_rect);
		}
	}

	void update_component(float dt) override {
		if (this->is_animated) {
			this->accumulatedTime += sf::seconds(dt);

			while (accumulatedTime >= timeChunk) {
				accumulatedTime -= timeChunk;
				current_image.x++;
			}
			current_image.x %= image_count.x;

			this->frame_rect.left =
				this->current_image.x * this->frame_rect.width;

			this->frame_rect.top =
				this->current_image.y * this->frame_rect.height;
			this->sprite.setTextureRect(this->frame_rect);
		}
	}

	void play_animation(std::string name) {
		int row = this->animation_manager.get_animation(name);
		this->current_image.y = row;
		this->current_animation = name;
		this->accumulatedTime = sf::Time::Zero;
	}

	std::string get_current_animation() { return this->current_animation; }

	bool get_is_animated() { return this->is_animated; }

	float get_sprite_rotation() { return this->sprite_rotation; }

	void set_sprite_rotation(float rotation) {
		this->sprite_rotation = rotation;
	}

  private:
	sf::Vector2u image_count;
	sf::Vector2u current_image;
	sf::IntRect frame_rect;
	sf::Time accumulatedTime = sf::Time::Zero;
	sf::Time timeChunk{sf::seconds(1.0 / 60.0)};
	std::string name;
	std::string current_animation;

	float sprite_rotation;
	bool is_animated = false;
	bool should_loop = false;
	bool played_once = false;
	skeleton::AnimationManager animation_manager;
};

#endif