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

enum CompareFunction
{
	CompareFunction_Never,
	CompareFunction_Less,
	CompareFunction_Equal,
	CompareFunction_LessEqual,
	CompareFunction_Greater,
	CompareFunction_NotEqual,
	CompareFunction_GreaterEqual,
	CompareFunction_Always,
};

class Graphics : private IRasterizable
{
public:
	Graphics();
	~Graphics();

	bool init(SDL_Window*, int width, int height);
	void clear(int);
	void clear_color(Color color);
	void set_renderbuffer(RenderBuffer* buffer);
	void set_shader(Shader* shader);
	void bind_vertexdata(Vector3*, int);
	//void bind_normaldata(float*, int);
	void bind_colordata(Color*, int);
	void bind_indexdata(unsigned int*, int);
	void draw_primitive(Primitive);
	void set_zwrite(bool);
	void set_ztest(CompareFunction);
	float get_width() { return _width; }
	float get_height() { return _height; }

private:
	void set_pixel(int x, int y, Color color);
	void set_depth(int x, int y, float);
	float get_depth(int x, int y);
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
	CompareFunction _ztest;
	bool _zwrite;
};

