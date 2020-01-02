#include <Game.hpp>
#include <LuaHelper.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>
namespace Skeleton {
class Component {
public:
  virtual void update(float dt) = 0;
  virtual void draw() = 0;
  virtual ~Component(){};
};
class GraphicComponent : public Component {
public:
  sf::Sprite sprite;
  gameDataRef data;
  sf::Vector2u imageCount;
  sf::Vector2u currentImage;
  std::string name;
  sf::IntRect uvRect;
  float switchTime;
  float totalTime = 0.0f;
  bool animated = false;
  int row = 0;

  GraphicComponent(gameDataRef data, std::string name, std::string filepath,
                   sf::Vector2u imageCount = sf::Vector2u(0, 0),
                   sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f),
                   bool animated = false, int row = 0,
                   float switchTime = 0.3f) {
    this->data = data;
    this->name = name;
    this->data->assets.loadTexture(this->name, filepath);
    sf::Texture &text = this->data->assets.getTexture(this->name);
    this->sprite.setScale(scale);
    if (animated) {
      this->totalTime = 0.0f;
      this->animated = animated;
      this->uvRect.width = text.getSize().x / float(imageCount.x);
      this->uvRect.height = text.getSize().y / float(imageCount.y);
      this->imageCount = imageCount;
      this->row = row;
      this->switchTime = switchTime;
      this->currentImage.x = 0;
      this->currentImage.y = row;
      this->sprite.setTextureRect(this->uvRect);
    }
    this->sprite.setTexture(text);
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

  void draw() override { this->data->window.draw(this->sprite); }
};
} // namespace Skeleton