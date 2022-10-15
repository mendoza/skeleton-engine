#pragma once
#include <AnimationManager.hpp>
#include <GameData.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <sol.hpp>

class Component {
  public:
	virtual void update(float dt){};
	virtual void draw(){};
	virtual ~Component(){};
};

class GraphicComponent : public Component {
  public:
	sf::Sprite Sprite;
	GraphicComponent(skeleton::GameDataRef Data, sol::table GC) {
		this->name = GC["sprite_name"];
		Data->Assets.loadTexture(this->name, GC["sprite_filepath"]);
		sf::Texture &text = Data->Assets.getTexture(this->name);
		this->Sprite.setTexture(text);
		sf::Vector2f Vector(GC["sprite_orientation"]["x"],
							GC["sprite_orientation"]["y"]);
		this->spriteRotation = std::atan2(Vector.y, Vector.x) * 180 / M_PI;

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
			this->isAnimated = GC["animated"];
		}

		if (this->isAnimated && GC["animation"] != sol::nil) {
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
			this->currentImage = {
				unsigned(GC["animation"]["initial_image"]["col"]),
				unsigned(GC["animation"]["initial_image"]["row"])};
			this->UvRect = {int(this->currentImage.x * this->UvRect.width),
							int(this->currentImage.y * this->UvRect.height),
							height, width};

			sf::Vector2f Origin(UvRect.left + (width / 2),
								UvRect.top + (height / 2));
			this->Sprite.setOrigin(Origin);

			this->Sprite.setTextureRect(this->UvRect);
		}
	}

	bool shouldPlay() {
		if (this->shouldLoop) {
			return true;
		} else {
			if (!this->hasLooped) {
				return true;
			}
		}
		return false;
	}

	void update(float dt) override {
		if (this->isAnimated && shouldPlay()) {
			this->totalTime += dt;
			if (totalTime >= SwitchTime) {
				totalTime -= SwitchTime;
				currentImage.x++;
				if (currentImage.x >= ImageCount.x) {
					this->hasLooped = true;
					if (this->shouldLoop) {
						currentImage.x = 0;
					} else {
						currentImage.x = ImageCount.x - 1;
					}
				}
			}
			this->UvRect.left = this->currentImage.x * this->UvRect.width;
			this->UvRect.top = this->currentImage.y * this->UvRect.height;
			this->Sprite.setTextureRect(this->UvRect);
		}
	}

	void playAnimation(std::string name, bool shouldLoop) {
		int row = this->Animations.getAnimation(name);
		this->currentImage.y = row;
		this->CurrentAnimation = name;
		this->shouldLoop = shouldLoop;
		this->hasLooped = false;
	}

	std::string getCurrentAnimation() { return this->CurrentAnimation; }

	bool getIsAnimated() { return this->isAnimated; }

	float getSpriteRotation() { return this->spriteRotation; }

	void setSpriteRotation(float rotation) { this->spriteRotation = rotation; }

  private:
	sf::Vector2u ImageCount;
	sf::Vector2u currentImage;
	std::string name;
	std::string CurrentAnimation;
	sf::IntRect UvRect;
	float spriteRotation;
	float SwitchTime = 1 / 6;
	float totalTime = 10.f;
	bool isAnimated = false;
	bool shouldLoop = false;
	bool hasLooped = false;
	skeleton::AnimationManager Animations;
};