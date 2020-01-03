#pragma once
#include <Game.hpp>
#include <LuaHelper.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>
namespace Skeleton {
class Component {
public:
  virtual void update(float dt){};
  virtual void draw(){};
  virtual ~Component(){};
};
class GraphicComponent : public Component {
public:
  sf::Sprite sprite;
  sf::Vector2u imageCount;
  sf::Vector2u currentImage;
  std::string name;
  sf::IntRect uvRect;
  float switchTime;
  float totalTime = 0.0f;
  bool animated = false;
  int row = 0;

  GraphicComponent(gameDataRef data, sol::table gc) {
    this->name = gc["name"];
    data->assets.loadTexture(this->name, gc["spriteFilepath"]);
    sf::Texture &text = data->assets.getTexture(this->name);
    sf::Vector2f scale(gc["scale"]["width"], gc["scale"]["height"]);
    if (gc["animation"] != sol::nil) {
      this->totalTime = 0.0f;
      this->animated = true;
      this->imageCount = sf::Vector2u(gc["animation"]["horizontalFrameCount"],
                                      gc["animation"]["verticalFrameCount"]);
      this->uvRect.width = text.getSize().x / float(this->imageCount.x);
      this->uvRect.height = text.getSize().y / float(this->imageCount.y);
      this->row = gc["animation"]["row"];
      this->switchTime = gc["animation"]["switchTime"];
      this->currentImage.x = 0;
      this->currentImage.y = this->row;
      this->sprite.setTextureRect(this->uvRect);
    }
    this->sprite.setTexture(text);
    this->sprite.setScale(scale);
  }

  void update(float dt) override {
    if (this->animated) {
      this->totalTime += dt;
      if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount.x) {
          currentImage.x = 0;
        }
      }
      uvRect.left = currentImage.x * uvRect.width;
      uvRect.top = currentImage.y * uvRect.height;
      this->sprite.setTextureRect(this->uvRect);
    }
  }
};

} // namespace Skeleton