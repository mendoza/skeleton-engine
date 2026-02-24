#pragma once
#include <cmath>
#include <cstdint>

namespace skeleton {

struct Vec2 {
  float x = 0, y = 0;

  Vec2 operator+(const Vec2 &o) const { return {x + o.x, y + o.y}; }
  Vec2 operator-(const Vec2 &o) const { return {x - o.x, y - o.y}; }
  Vec2 operator*(float s) const { return {x * s, y * s}; }
  Vec2 operator/(float s) const { return {x / s, y / s}; }
  Vec2 &operator+=(const Vec2 &o) {
    x += o.x;
    y += o.y;
    return *this;
  }
  Vec2 &operator-=(const Vec2 &o) {
    x -= o.x;
    y -= o.y;
    return *this;
  }
  bool operator==(const Vec2 &o) const { return x == o.x && y == o.y; }
  bool operator!=(const Vec2 &o) const { return !(*this == o); }

  float length() const { return std::sqrt(x * x + y * y); }
  float length_sq() const { return x * x + y * y; }
  Vec2 normalized() const {
    float l = length();
    return l > 0 ? *this / l : Vec2{};
  }

  float dot(const Vec2 &o) const { return x * o.x + y * o.y; }
  float cross(const Vec2 &o) const { return x * o.y - y * o.x; }

  // Linear interpolation toward `o` by factor `t` (0 = this, 1 = o).
  Vec2 lerp(const Vec2 &o, float t) const { return *this + (o - *this) * t; }

  // Rotate by `angle` radians counter-clockwise.
  Vec2 rotated(float angle) const {
    float c = std::cos(angle), s = std::sin(angle);
    return {x * c - y * s, x * s + y * c};
  }
};

struct Rect {
  float x = 0, y = 0, w = 0, h = 0;
};
struct Color {
  uint8_t r = 0, g = 0, b = 0, a = 255;
};

enum class Flip { None = 0, Horizontal = 1, Vertical = 2, Both = 3 };
enum class BlendMode { None, Blend, Add, Mod };

struct Camera2D {
  Vec2 position;
  float zoom = 1.0f;

  Vec2 world_to_screen(Vec2 world, float sw, float sh) const {
    return (world - position) * zoom + Vec2{sw / 2.0f, sh / 2.0f};
  }

  Vec2 screen_to_world(Vec2 screen, float sw, float sh) const {
    return (screen - Vec2{sw / 2.0f, sh / 2.0f}) / zoom + position;
  }
};

} // namespace skeleton
