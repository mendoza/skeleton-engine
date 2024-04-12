#ifndef SKELETON_RENDER_SERVICE_HPP
#define SKELETON_RENDER_SERVICE_HPP
#include "IRenderer.hpp"
#include <SDL.h>
#include <string>
namespace skeleton {
class Renderer : public IRenderer {
public:
  static Renderer &get_instance() {
    static Renderer instance;
    return instance;
  }

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  void create_window(std::string title, int width, int height,
                     bool debug_mode) override;
        void end() override;
  void begin() override;
  void shutdown() override;
  void draw_rect(int x, int y, int w, int h, int r, int g, int b,
                 int a) override;
  int get_window_width() override;
  int get_window_height() override;
  void set_draw_color(SDL_Color color) override;
  void set_debug_mode(bool debug_mode) override;
  void draw_texture(std::string tag, SDL_Rect *src_rect,
                    SDL_Rect *dst_rect) override;
  SDL_Renderer *get_renderer() { return this->renderer; }

private:
  Renderer();
  ~Renderer() override;

  bool debug_mode = false;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Color draw_color = {0, 0, 0, 255};
};
} // namespace skeleton
#endif
