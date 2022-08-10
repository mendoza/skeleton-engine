#pragma once
#include <Engine.hpp>

class Component {
  public:
	virtual void update(float dt){};
	virtual void draw(){};
	virtual ~Component(){};
};

class GraphicComponent : public Component {
  public:
	sf::Sprite Sprite;
	sf::Vector2u ImageCount;
	sf::Vector2u CurrentImage;
	std::string Name;
	std::string CurrentAnimation;
	sf::IntRect UvRect;
	float SpriteRotation;
	float SwitchTime = 1 / 6;
	float TotalTime = 0;
	bool Animated = false;
	skeleton::AnimationManager Animations;

	GraphicComponent(skeleton::GameDataRef Data, sol::table GC) {
		this->Name = GC["sprite_name"];
		Data->Assets.loadTexture(this->Name, GC["sprite_filepath"]);
		sf::Texture &text = Data->Assets.getTexture(this->Name);
		this->Sprite.setTexture(text);
		sf::Vector2f Vector(GC["sprite_orientation"]["x"],
							GC["sprite_orientation"]["y"]);
		this->SpriteRotation = std::atan2(Vector.y, Vector.x) * 180 / M_PI;

		if (GC["origin"] != sol::nil) {
			sf::Vector2f Origin(GC["origin"]["x"], GC["origin"]["y"]);
			this->Sprite.setOrigin(Origin);
		}

		if (GC["scale"] != sol::nil) {
			sf::Vector2f Scale(GC["scale"]["width"], GC["scale"]["height"]);
			this->Sprite.setScale(Scale);
		}

		if (GC["position"] != sol::nil) {
			sf::Vector2f Position(GC["position"]["x"], GC["position"]["y"]);
			this->Sprite.setPosition(Position);
		}

		if (GC["animated"] != sol::nil) {
			this->Animated = GC["animated"];
		}

		if (this->Animated && GC["animation"] != sol::nil) {
			sol::table animations = GC["animation"]["animations"];
			int count = animations.size();
			for (int i = 1; i <= count; i++) {
				sol::table item = animations[i];
				this->Animations.addAnimation(item["name"], item["row"]);
			}
			int rows = GC["animation"]["rows"];
			int cols = GC["animation"]["cols"];
			int width = this->Sprite.getTextureRect().width / cols;
			int height = this->Sprite.getTextureRect().height / rows;
			this->ImageCount = {unsigned(cols), unsigned(rows)};
			this->SwitchTime = GC["animation"]["switch_time"];
			this->CurrentImage = {
				unsigned(GC["animation"]["initial_image"]["col"]),
				unsigned(GC["animation"]["initial_image"]["row"])};
			this->UvRect = {int(this->CurrentImage.x * this->UvRect.width),
							int(this->CurrentImage.y * this->UvRect.height),
							height, width};

			sf::Vector2f Origin(UvRect.left + (width / 2),
								UvRect.top + (height / 2));
			this->Sprite.setOrigin(Origin);

			this->Sprite.setTextureRect(this->UvRect);
		}
	}

	void update(float dt) override {
		if (this->Animated) {
			this->TotalTime += dt;
			if (TotalTime >= SwitchTime) {
				TotalTime -= SwitchTime;
				CurrentImage.x++;
				if (CurrentImage.x >= ImageCount.x) {
					CurrentImage.x = 0;
				}
			}
			this->UvRect.left = this->CurrentImage.x * this->UvRect.width;
			this->UvRect.top = this->CurrentImage.y * this->UvRect.height;
			this->Sprite.setTextureRect(this->UvRect);
		}
	}
};