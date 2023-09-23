#ifndef SKELETON_COMPONENTS_HPP
#define SKELETON_COMPONENTS_HPP
#include <SDL2/SDL.h>
struct Position {
	int x;
	int y;
};

struct Velocity {
	float x;
	float y;
};
struct Cell {
	bool isAlive;
};

struct Square {
	int width;
	int height;
	// random sdl color
	SDL_Color color = {255, 255, 255, 255};
};
#endif