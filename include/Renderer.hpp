#ifndef RENDER_SERVICE_HPP
#define RENDER_SERVICE_HPP
#include "Service.hpp"
#include <SDL2/SDL.h>
class DrawableNode;
namespace skeleton {
class Renderer : public Service {
public:
  Renderer() = default;
  ~Renderer() override = default;
  virtual void end() = 0;
  virtual void begin() = 0;
  virtual void shutdown() = 0;
  virtual void draw_rect(int x, int y, int w, int h, int r, int g, int b,
                         int a) = 0;
  virtual int get_window_width() = 0;
  virtual int get_window_height() = 0;
  virtual void set_clear_color(SDL_Color color) = 0;
  virtual void set_debug_mode(bool debug_mode) = 0;
};
} // namespace skeleton
#endif
