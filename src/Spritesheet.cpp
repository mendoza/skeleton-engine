#include <Spritesheet.hpp>

namespace skeleton {
Spritesheet::Spritesheet(std::string path, int row, int column) {
	this->spritesheet_image = IMG_Load(path.c_str());

	this->clip.w = spritesheet_image->w / column;
	this->clip.h = spritesheet_image->h / row;
}

Spritesheet::~Spritesheet() { SDL_FreeSurface(spritesheet_image); }

void Spritesheet::select_sprite(int x, int y) {
	this->clip.x = x * this->clip.w;
	this->clip.y = y * this->clip.h;
}

void Spritesheet::draw_selected_sprite(SDL_Renderer *renderer,
									   SDL_Rect *position) {
	SDL_Texture *text =
		SDL_CreateTextureFromSurface(renderer, this->spritesheet_image);
	SDL_RenderCopy(renderer, text, &this->clip, position);
}

SDL_Rect *Spritesheet::get_sprite_clip() { return &this->clip; }
} // namespace skeleton