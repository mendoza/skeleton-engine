#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP
#include <SDL2/SDL.h>
struct Position {
	float x;
	float y;
};

struct Velocity {
	float x;
	float y;
};

struct Square {
	int width;
	int height;
	// random sdl color
	SDL_Color color = {255, 255, 255, 255};
};
#endif