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
	float TotalTime;
	bool Animated = false;
	skeleton::AnimationManager Animations;

	GraphicComponent(skeleton::GameDataRef Data, sol::table GC) {
		this->Name = GC["spriteName"];
		Data->Assets.loadTexture(this->Name, GC["spriteFilepath"]);
		sf::Texture &text = Data->Assets.getTexture(this->Name);
		this->Sprite.setTexture(text);
		sf::Vector2f Vector(GC["spriteOrientation"]["x"],
							GC["spriteOrientation"]["y"]);
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
			this->SwitchTime = GC["animation"]["switchTime"];
			this->CurrentImage = {
				unsigned(GC["animation"]["initialImage"]["col"]),
				unsigned(GC["animation"]["initialImage"]["row"])};
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

class LogicComponent : public Component {
  public:
	sol::state L;
	sol::function ScriptUpdate;
	skeleton::Logger *console = console->getInstance();

	LogicComponent(std::string Path) {
		L.open_libraries();
		L.script_file(Path);
		this->ScriptUpdate = L["update"];
		this->L.new_usertype<skeleton::Logger>(
			"console", "Log", &skeleton::Logger::Log, "Warning",
			&skeleton::Logger::Warning, "Error", &skeleton::Logger::Error);
		this->L["console"] = console;
	}
	void update(float dt) override { this->ScriptUpdate(dt); }

	void draw() override {}
	~LogicComponent() { delete console; }
};