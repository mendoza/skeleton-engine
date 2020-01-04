#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>

namespace Skeleton {
class AssetManager {

public:
  AssetManager() {}
  ~AssetManager() {}

  void loadTexture(std::string name, std::string filename);
  sf::Texture &getTexture(std::string name);

  void loadFont(std::string name, std::string filename);
  sf::Font &getFont(std::string name);

  void loadSound(std::string name, std::string filename);
  sf::SoundBuffer &getSound(std::string name);

private:
  std::map<std::string, sf::Texture> _textures;
  std::map<std::string, sf::Font> _fonts;
  std::map<std::string, sf::SoundBuffer> _soundBuffers;
};

}; // namespace Skeleton