#include <AssetManager.hpp>

namespace Skeleton {
void AssetManager::loadTexture(std::string name, std::string filename) {
  sf::Texture tex;
  if (tex.loadFromFile(filename)) {
    this->_textures[name] = tex;
  }
}

sf::Texture &AssetManager::getTexture(std::string name) {
  return this->_textures.at(name);
}

void AssetManager::loadFont(std::string name, std::string filename) {
  sf::Font font;
  if (font.loadFromFile(filename)) {
    this->_fonts[name] = font;
  }
}

sf::Font &AssetManager::getFont(std::string name) {
  return this->_fonts.at(name);
}

void AssetManager::loadSound(std::string name, std::string filename) {
  sf::SoundBuffer soundbuffer;
  if (soundbuffer.loadFromFile(filename)) {
    this->_soundBuffers[name] = soundbuffer;
  }
}

sf::SoundBuffer &AssetManager::getSound(std::string name) {
  return this->_soundBuffers.at(name);
}

} // namespace Skeleton