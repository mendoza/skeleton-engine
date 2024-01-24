#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP
#include <Node.hpp>
#include <SDL2/SDL.h>
namespace skeleton {
class Transform : public Node {
public:
  float x;
  float y;
  float rotation;
  float scale_x;
  float scale_y;
};

class Sprite : public Node {
public:
  SDL_Texture *texture;
  SDL_Rect src_rect;
  SDL_Rect dest_rect;
  SDL_RendererFlip flip;
};
} // namespace skeleton
#endif