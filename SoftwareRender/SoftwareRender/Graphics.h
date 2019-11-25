#pragma once
#include "Math.h"
#include "RenderBuffer.h"
#include "Color.h"
#include "Shader.h"
#include "Rasterization.h"

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


class Graphics : private IRasterizable
{
public:
	Graphics();
	~Graphics();

	bool init(SDL_Window*, int width, int height);
	void clear(ClearFlags);
	void clear_color(Color color);
	void set_renderbuffer(RenderBuffer* buffer);
	void set_shader(Shader* shader);
	void bind_vertexdata(Vector3*, int);
	void bind_normaldata(float*, int);
	void bind_colordata(Color*, int);
	void bind_indexdata(unsigned int*, int);
	void draw_primitive(Primitive);
	void enable();
	void disable();
	float get_width() { return _width; }
	float get_height() { return _height; }

private:
	void set_pixel(int x, int y, Color color);
	void set_depth(int x, int y, float);
	void draw_points();
	void draw_triangles();
	void draw_lines();
	void draw_linestrips();

	void rasterize_fragment(int x, int y, FragmentInput& frag) override;
	

private:
	float* _zbuffer;
	RenderBuffer* _renderbuffer;
	Shader* _shader;
	Vector3* _vertexdata;
	Color* _colordata;
	unsigned int* _indexdata;
	SDL_Surface* _surface;
	int _width, _height;
	Color _clear_color;
	int _vertexcount, _colorcount, _indexcount;
	PointRasterization* _point_rasterization;
	LineRasterization* _line_rasterization;
	TriangleRasterization* _triangle_rasterization;
};

