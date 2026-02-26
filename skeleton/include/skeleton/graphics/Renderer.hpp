#pragma once
#include <SDL.h>
#include <optional>
#include <skeleton/math/types.hpp>
#include <string>
#include <unordered_map>

namespace skeleton::graphics {

class Renderer {
public:
  static Renderer &get_instance() {
    static Renderer instance;
    return instance;
  }

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  void create_window(std::string title, int width, int height, bool debug_mode);
  void begin();
  void end();
  void shutdown();

  int get_window_width();
  int get_window_height();

  void set_draw_color(skeleton::Color color);
  void draw_rect(skeleton::Rect rect, skeleton::Color color);
  void draw_texture(size_t key, skeleton::Rect *src, skeleton::Rect *dst,
                    float angle = 0.0f,
                    skeleton::Flip flip = skeleton::Flip::None,
                    uint8_t alpha = 255,
                    skeleton::BlendMode blend = skeleton::BlendMode::Blend);
  void draw_line(skeleton::Vec2 a, skeleton::Vec2 b, skeleton::Color color);
  void set_debug_mode(bool debug_mode);

  void set_camera(const skeleton::Camera2D &cam);
  void reset_camera();

  SDL_Renderer *get_sdl_renderer() { return renderer; }
  SDL_Window *get_sdl_window() { return window; }
  void store_texture(size_t key, SDL_Texture *texture);

  // Redirect draws to an offscreen texture. Used by the editor to capture
  // the scene before compositing it into an ImGui panel.
  void begin_scene_capture();
  void end_scene_capture();
  SDL_Texture *get_scene_texture() const { return scene_texture_; }

private:
  Renderer();
  ~Renderer();

  bool debug_mode = false;
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Color draw_color = {0, 0, 0, 255};
  std::unordered_map<size_t, SDL_Texture *> textures;
  std::optional<skeleton::Camera2D> active_camera;
  SDL_Texture *scene_texture_ = nullptr;

  Vec2 to_screen(Vec2 p) const;
};

} // namespace skeleton::graphics
