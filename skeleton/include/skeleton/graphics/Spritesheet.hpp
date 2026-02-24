#pragma once
#include <cstddef>
#include <skeleton/math/types.hpp>

namespace skeleton::graphics {

struct Spritesheet {
  size_t texture_key = 0;
  int frame_w = 0;
  int frame_h = 0;
  int spacing = 0; // pixels between frames
  int margin = 0;  // pixels around the border of the whole sheet

  skeleton::Rect get_frame(int col, int row) const {
    return {
        (float)(margin + col * (frame_w + spacing)),
        (float)(margin + row * (frame_h + spacing)),
        (float)frame_w,
        (float)frame_h,
    };
  }
};

} // namespace skeleton::graphics
