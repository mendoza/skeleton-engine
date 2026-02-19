#pragma once
#include <skeleton/math/types.hpp>
#include <cstddef>

namespace skeleton::graphics {

struct Sprite {
  size_t texture_key = 0;
  skeleton::Rect src;  // source region in the texture (computed from spritesheet)
  float draw_w = 0;
  float draw_h = 0;
};

} // namespace skeleton::graphics
