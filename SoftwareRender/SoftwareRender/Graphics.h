#pragma once
#include "Math.h"
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
	void bind_vertexdata(Vector3*, int);
	void bind_normaldata(float*, int);
	void bind_colordata(float*, int);
	void bind_indexdata(unsigned int*, int);
	void draw_primitive(Primitive);
	void enable();
	void disable();

private:
	void set_pixel(int x, int y, Uint32 color);
	void set_depth(int x, int y, float);
	void draw_points(int);
	void draw_triangles();

	void draw_triangle(Vector3, Vector3, Vector3);

	int edge_equation(int beginx, int beginy, int endx, int endy, int x, int y);
	bool is_edge_topleft(int x0, int y0, int x1, int y1);
	void get_uv(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float& u, float &v);

private:
	float* _zbuffer;
	RenderBuffer* _renderbuffer;
	Vector3* _vertexdata;
	unsigned int* _indexdata;
	SDL_Surface* _surface;
	int _width, _height;
	Uint32 _clear_color;
	int _vertexcount, _indexcount;
};

