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
};

