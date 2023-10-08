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
	int r;
	int b;
	int g;
	int a;
};
#endif