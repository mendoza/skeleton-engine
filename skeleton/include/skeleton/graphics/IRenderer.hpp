#pragma once
#include <skeleton/math/types.hpp>
#include <string>

namespace skeleton::graphics {

class IRenderer {
public:
  IRenderer() = default;
  virtual ~IRenderer() = default;

  virtual void create_window(std::string title, int width, int height,
                             bool debug_mode) = 0;
  virtual void begin() = 0;
  virtual void end() = 0;
  virtual void shutdown() = 0;

  virtual int get_window_width() = 0;
  virtual int get_window_height() = 0;

  virtual void set_draw_color(skeleton::Color color) = 0;
  virtual void draw_rect(skeleton::Rect rect, skeleton::Color color) = 0;
  virtual void
  draw_texture(size_t key, skeleton::Rect *src, skeleton::Rect *dst,
               float angle = 0.0f, skeleton::Flip flip = skeleton::Flip::None,
               uint8_t alpha = 255,
               skeleton::BlendMode blend = skeleton::BlendMode::Blend) = 0;
  virtual void draw_line(skeleton::Vec2 a, skeleton::Vec2 b,
                         skeleton::Color color) = 0;
  virtual void set_debug_mode(bool debug_mode) = 0;

  virtual void set_camera(const skeleton::Camera2D &cam) = 0;
  virtual void reset_camera() = 0;
};

} // namespace skeleton::graphics
