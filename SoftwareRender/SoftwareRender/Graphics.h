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

enum BlendMode
{
	BlendMode_Zero,
	BlendMode_One,
	BlendMode_DstColor,
	BlendMode_SrcColor,
	BlendMode_OneMinusDstColor,
	BlendMode_SrcAlpha,
	BlendMode_OneMinusSrcColor,
	BlendMode_DstAlpha,
	BlendMode_OneMinusDstAlpha,
	BlendMode_OneMinusSrcAlpha,
};

enum CullMode
{
	CullMode_Off,
	CullMode_Front,
	CullMode_Back,
};

enum StencilOp
{
	StencilOp_Keep,
	StencilOp_Zero,
	StencilOp_Replace,
	StencilOp_IncrementSaturate,
	StencilOp_DecrementSaturate,
	StencilOp_Invert,
	StencilOp_IncrementWrap,
	StencilOp_DecrementWrap,
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
	void bind_texcoorddata(Vector2*, int, int);
	//void bind_normaldata(float*, int);
	void bind_colordata(Color*, int);
	void bind_indexdata(unsigned int*, int);
	void draw_primitive(Primitive);

	void set_zwrite(bool);
	void set_ztest(CompareFunction);
	void set_blendmode(BlendMode src, BlendMode dst);
	void set_blend(bool);
	void set_cullmode(CullMode cullmode);
	/*void set_stenciltest(bool);
	void set_stencilId(int);
	void set_stenciltest(CompareFunction);
	void set_stencilpass(StencilOp);
	void set_stencilfail(StencilOp);
	void set_stencilzfail(StencilOp);
	void set_stencilreadmask(unsigned int);
	void set_stencilwritemask(unsigned int);*/

	int get_width() { return _width; }
	int get_height() { return _height; }

private:
	void set_pixel(int x, int y, Color color);
	void set_depth(int x, int y, float);
	Color get_pixel(int x, int y);
	float get_depth(int x, int y);
	void draw_points();
	void draw_triangles();
	void draw_lines();
	void draw_linestrips();
	static bool buffer_compare(CompareFunction func, float current, float target);
	static Color blend_color(const Color& srccolor, const Color& dstcolor, BlendMode srcfactor, BlendMode dstfactor);
	static bool frustumculling(FragmentInput* inputs, int count);
	static Color get_blend_factor(const Color& srccolor, const Color& dstcolor, BlendMode factor);

	void rasterize_fragment(int x, int y, FragmentInput& frag) override;
	

private:
	float* _zbuffer;
	RenderBuffer* _renderbuffer;
	Shader* _shader;
	Vector3* _vertexdata;
	Vector2* _uv0data;
	Vector2* _uv1data;
	Vector2* _uv2data;
	Vector2* _uv3data;
	Color* _colordata;
	unsigned int* _indexdata;
	SDL_Surface* _surface;

	int _width, _height;
	Color _clear_color;
	int _vertexcount, _colorcount, _indexcount, _uv0count, _uv1count, _uv2count, _uv3count;
	PointRasterization* _point_rasterization;
	LineRasterization* _line_rasterization;
	TriangleRasterization* _triangle_rasterization;
	CompareFunction _ztest;
	bool _zwrite;
	bool _blend;
	BlendMode _src, _dst;
	CullMode _cullmode;
};

