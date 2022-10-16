#ifndef SKELETON_ASSET_MANAGER_HPP
#define SKELETON_ASSET_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace skeleton {
class AssetManager {

  public:
	AssetManager() {}
	~AssetManager() {}

	void load_texture(std::string, std::string file_name);
	sf::Texture &get_texture(std::string name);

	void load_font(std::string name, std::string file_name);
	sf::Font &get_font(std::string Name);

	void load_sound(std::string Name, std::string file_name);
	sf::SoundBuffer &get_sound(std::string name);

  private:
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::SoundBuffer> sound_buffers;
};
}; // namespace skeleton

#endif