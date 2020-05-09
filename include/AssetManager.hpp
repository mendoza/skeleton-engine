#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace Skeleton {
class AssetManager {

  public:
	AssetManager() {}
	~AssetManager() {}

	void loadTexture(std::string Name, std::string Filename);
	sf::Texture &getTexture(std::string Name);

	void loadFont(std::string Name, std::string Filename);
	sf::Font &getFont(std::string Name);

	void loadSound(std::string Name, std::string Filename);
	sf::SoundBuffer &getSound(std::string Name);

  private:
	std::map<std::string, sf::Texture> Textures;
	std::map<std::string, sf::Font> Fonts;
	std::map<std::string, sf::SoundBuffer> SoundBuffers;
};
}; // namespace Skeleton