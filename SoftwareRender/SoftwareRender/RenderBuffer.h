#pragma once
extern "C" {
#include "SDL.h"
}

class RenderBuffer
{
public:
	RenderBuffer();
	~RenderBuffer();
	void set_pixel(int, int, Uint32);
	void set_depth(int, int, float);
};

