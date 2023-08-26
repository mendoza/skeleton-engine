#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP
#include "Service.hpp"
#include "Spritesheet.hpp"
#include <SDL2/SDL.h>
namespace skeleton {
class Renderer : public Service {
  public:
	Renderer() {}
	~Renderer() {}
	virtual void drawSpritesheet(Spritesheet *spritesheet, int x, int y) = 0;
	virtual void update() = 0;
	virtual void clear() = 0;
	virtual void shutdown() = 0;
};
} // namespace skeleton
#endif