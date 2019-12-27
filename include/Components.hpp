#include <Game.hpp>
#include <SFML/Graphics.hpp>
namespace Skeleton {
class GraphicComponent {
public:
  sf::Sprite sprite;
  sf::Vector2i dimentions;
  gameDataRef data;
  sf::Vector2u imageCount;
  int speed = 100;
  bool animated = false;
  int row = 0;
  
  GraphicComponent(gameDataRef data, std::string filepath,
                   sf::Vector2u imageCount = sf::Vector2u(0, 0),
                   sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f),
                   bool animated = false, int row = 0) {
    this->data = data;
    this->data->assets.loadTexture("sprite", filepath);
    sf::Texture &text = this->data->assets.getTexture("sprite");
    this->sprite.setScale(scale);
    this->sprite.setTexture(text);
    if (animated) {
      this->animated = animated;
      this->dimentions.x = text.getSize().x / imageCount.x;
      this->dimentions.y = text.getSize().y / imageCount.y;
      this->imageCount = imageCount;
      this->row = row;
      this->sprite.setTextureRect(
          {0, row * dimentions.y, dimentions.x, dimentions.y});
    }
  }

  void update() {
    if (this->animated) {
      int left =
          dimentions.x *
          static_cast<int>(
              (this->data->_clock.getElapsedTime().asMilliseconds() / speed) %
              imageCount.x);
      int top = dimentions.y * row;
      int width = 20;
      int height = 20;

      this->sprite.setTextureRect({left, top, width, height});
    }
  }

  void draw() { this->data->window.draw(this->sprite); }
};
} // namespace Skeleton