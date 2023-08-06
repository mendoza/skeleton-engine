#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP
#include <SDL2/SDL.h>
#include <Service.hpp>
#include <Spritesheet.hpp>
namespace skeleton {
class Renderer : public Service {
  public:
	~Renderer() {}
	virtual void drawSprite(Spritesheet *spritesheet, int x, int y) = 0;
	virtual void update() = 0;
	virtual void clear() = 0;
};
} // namespace skeleton
#endif