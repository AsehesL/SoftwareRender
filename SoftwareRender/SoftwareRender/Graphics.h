#pragma once
#include "RenderBuffer.h"

extern "C" {
#include "SDL.h"
}

enum ClearFlags
{
	ClearFlags_Color = 1,
	ClearFlags_Depth = 2,
};

enum Primitive
{
	Primitive_Line,
	Primitive_LineStrip,
	Primitive_Triangle,
	Primitive_Point,
};


class Graphics
{
public:
	Graphics();
	~Graphics();

	bool init(SDL_Window*, int width, int height);
	void clear(ClearFlags);
	void clear_color(Uint32 color);
	void set_renderbuffer(RenderBuffer* buffer);
	void bind_vertexdata(float*, int);
	void bind_normaldata(float*, int);
	void bind_colordata(float*, int);
	void bind_indexdata(int*, int);
	void draw_primitive(Primitive, int, int);
	void enable();
	void disable();

private:
	void set_pixel(int x, int y, Uint32 color);
	void set_depth(int x, int y, float);

private:
	float* _zbuffer;
	RenderBuffer* _renderbuffer;
	float* _vertexdata;
	SDL_Surface* _surface;
	int _width, _height;
	Uint32 _clear_color;
};

