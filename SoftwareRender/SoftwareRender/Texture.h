#pragma once
#include "ColorShader.h"

extern "C" {
#include "SDL.h"
}

enum WrapMode
{
	WrapMode_Clamp,
	WrapMode_Repeat,
};

class Texture
{
public:
	Texture();
	~Texture();

	bool load(const char*);
	Color sample(float u, float v);
	Color get_pixel(int x, int y);

	int get_width();
	int get_height();

public:
	WrapMode wrapmode;

private:
	SDL_Surface* _surface;
};

