#include <AssetManager.hpp>

namespace Skeleton {
void AssetManager::loadTexture(std::string Name, std::string Filename) {
	sf::Texture tex;
	if (tex.loadFromFile(Filename)) {
		this->Textures[Name] = tex;
	}
}

sf::Texture &AssetManager::getTexture(std::string Name) {
	return this->Textures.at(Name);
}

void AssetManager::loadFont(std::string Name, std::string Filename) {
	sf::Font font;
	if (font.loadFromFile(Filename)) {
		this->Fonts[Name] = font;
	}
}

sf::Font &AssetManager::getFont(std::string Name) {
	return this->Fonts.at(Name);
}

void AssetManager::loadSound(std::string Name, std::string Filename) {
	sf::SoundBuffer soundbuffer;
	if (soundbuffer.loadFromFile(Filename)) {
		this->SoundBuffers[Name] = soundbuffer;
	}
}

sf::SoundBuffer &AssetManager::getSound(std::string Name) {
	return this->SoundBuffers.at(Name);
}
}; // namespace Skeleton