#include <AssetManager.hpp>

namespace skeleton {
void AssetManager::load_texture(std::string name, std::string file_name) {
	sf::Texture tex;
	if (tex.loadFromFile(file_name)) {
		this->textures[name] = tex;
	}
}

sf::Texture &AssetManager::get_texture(std::string name) {
	return this->textures.at(name);
}

void AssetManager::load_font(std::string name, std::string file_name) {
	sf::Font font;
	if (font.loadFromFile(file_name)) {
		this->fonts[name] = font;
	}
}

sf::Font &AssetManager::get_font(std::string name) {
	return this->fonts.at(name);
}

void AssetManager::load_sound(std::string name, std::string file_name) {
	sf::SoundBuffer soundbuffer;
	if (soundbuffer.loadFromFile(file_name)) {
		this->sound_buffers[name] = soundbuffer;
	}
}

sf::SoundBuffer &AssetManager::get_sound(std::string name) {
	return this->sound_buffers.at(name);
}
}; // namespace skeleton