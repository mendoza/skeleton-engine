#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP
#include "Service.hpp"
#include <SDL2/SDL.h>
namespace skeleton {
class Renderer : public Service {
  public:
	Renderer() {}
	~Renderer() {}
	virtual void update() = 0;
	virtual void clear() = 0;
	virtual void shutdown() = 0;
	virtual void add_texture(std::string file_path, std::string name) = 0;
	virtual void draw_texture(std::string name, SDL_Rect *clip, int x,
							  int y) = 0;
	virtual SDL_Texture *get_texture(std::string name) = 0;
};
} // namespace skeleton
#endif