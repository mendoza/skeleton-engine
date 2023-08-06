#ifndef SKELETON_SPRITESHEET_HPP
#define SKELETON_SPRITESHEET_HPP
#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace skeleton {
class Spritesheet {
  public:
	Spritesheet(char *path, int row, int column);
	~Spritesheet();

	void select_sprite(int x, int y);
	void draw_selected_sprite(SDL_Renderer *renderer, SDL_Rect *position);
	SDL_Rect *get_sprite_clip();

  private:
	SDL_Rect clip;
	SDL_Surface *spritesheet_image;
};
} // namespace skeleton
#endif