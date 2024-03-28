#ifndef SKELETON_RENDER_SERVICE_HPP
#define SKELETON_RENDER_SERVICE_HPP
#include "Renderer.hpp"
#include <SDL.h>
namespace skeleton {
class SkeletonRenderer : public Renderer {
public:
  SkeletonRenderer();
  SkeletonRenderer(std::string title, int width, int height, bool debug_mode);
  ~SkeletonRenderer() override;
  void end() override;
  void begin() override;
  void shutdown() override;
  void draw_rect(int x, int y, int w, int h, int r, int g, int b,
                 int a) override;
  int get_window_width() override;
  int get_window_height() override;
  void set_clear_color(SDL_Color color) override;
  void set_debug_mode(bool debug_mode) override;

  bool debug_mode = false;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Color clear_color = {0, 0, 0, 255};
};
} // namespace skeleton
#endif
