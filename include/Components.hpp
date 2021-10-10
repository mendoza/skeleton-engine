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
	sf::IntRect UvRect;
	float SpriteRotation;
	float SwitchTime;
	float TotalTime;
	bool Animated = false;
	int Row = 0;

	GraphicComponent(Skeleton::GameDataRef Data, sol::table GC) {
		this->Name = GC["spriteName"];
		Data->Assets.loadTexture(this->Name, GC["spriteFilepath"]);
		sf::Texture &text = Data->Assets.getTexture(this->Name);
		this->Sprite.setTexture(text);
		sf::Vector2f Vector(GC["spriteOrientation"]["x"],
							GC["spriteOrientation"]["y"]);
		this->SpriteRotation = std::atan2(Vector.y, Vector.x) * 180 / M_PI;

		if (GC["animated"] != sol::nil) {
			this->Animated = GC["animated"];
		}

		if (this->Animated && GC["animation"] != sol::nil) {
			int rows = GC["animation"]["rows"];
			int cols = GC["animation"]["cols"];
			int width = this->Sprite.getTextureRect().width / cols;
			int height = this->Sprite.getTextureRect().height / rows;
			this->ImageCount = {unsigned(cols), unsigned(rows)};
			this->CurrentImage = {
				unsigned(GC["animation"]["initialImage"]["col"]),
				unsigned(GC["animation"]["initialImage"]["row"])};
			this->UvRect = {int(this->CurrentImage.x * this->UvRect.width),
							int(this->CurrentImage.y * this->UvRect.height),
							height, width};
			this->Sprite.setTextureRect(this->UvRect);
		}

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

class LogicComponent : public Component {
  public:
	sol::state L;
	sol::function ScriptUpdate;
	LogicComponent(std::string Path) {
		L.script_file(Path);
		L.open_libraries();
		this->ScriptUpdate = L["update"];
	}
	void update(float dt) override { this->ScriptUpdate(); }

	void draw() override {}
};