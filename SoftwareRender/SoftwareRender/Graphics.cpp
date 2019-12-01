#include "Graphics.h"
#include <Windows.h>

Graphics::Graphics()
{
	_renderbuffer = 0;
	_surface = 0;
	_zbuffer = 0;
	_shader = 0;
	_vertexdata = 0;
	_vertexcount = 0;
	_colordata = 0;
	_colorcount = 0;
	_uv0data = 0;
	_uv0count = 0;
	_uv1data = 0;
	_uv1count = 0;
	_uv2data = 0;
	_uv2count = 0;
	_uv3data = 0;
	_uv3count = 0;
	_indexdata = 0;
	_indexcount = 0;
	_zwrite = true;
	_src = BlendMode_One;
	_dst = BlendMode_Zero;
	_ztest = CompareFunction_LessEqual;
	_blend = false;
	_point_rasterization = 0;
	_line_rasterization = 0;
	_triangle_rasterization = 0;
	_cullmode = CullMode_Back;
	_clear_color = Color(0, 0, 0, 1);
}

Graphics::~Graphics()
{
	delete[] _zbuffer;
	delete _point_rasterization;
	delete _line_rasterization;
	delete _triangle_rasterization;
}

bool Graphics::init(SDL_Window* window, int width, int height)
{
	_surface = SDL_GetWindowSurface(window);
	if (_surface == nullptr)
	{
		MessageBox(NULL, L"窗口Surface创建失败", L"初始化失败", MB_ERR_INVALID_CHARS);
		return false;
	}
	//SDL_FillRect(_surface, 0, 0);

	_zbuffer = new float[width*height]();
	_width = width;
	_height = height;

	clear(ClearFlags_Color | ClearFlags_Depth);

	_point_rasterization = new PointRasterization();
	_line_rasterization = new LineRasterization();
	_triangle_rasterization = new TriangleRasterization();

	return true;
}

void Graphics::clear(int clearflag)
{
	//if ((clearflag & ClearFlags_Color) != 0) {
	//	int r = int(_clear_color.r * 255.0f);
	//	int g = int(_clear_color.g * 255.0f);
	//	int b = int(_clear_color.b * 255.0f);
	//	int a = int(_clear_color.a * 255.0f);
	//	UINT32 ucolor = SDL_MapRGBA(_surface->format, r, g, b, a);
	//	SDL_FillRect(_surface, 0, ucolor);
	//	
	//	//SDL_FillRect(t, 0, ucolor);
	//}
	//if ((clearflag & ClearFlags_Depth) != 0) {
	//}
	if (SDL_MUSTLOCK(_surface)) {
		if (SDL_LockSurface(_surface) < 0)
			return;
	}
	for(int j=0;j<_height;j++)
	{
		for(int i=0;i<_width;i++)
		{
			if ((clearflag & ClearFlags_Color) != 0)
			{
				set_pixel(i, j, _clear_color);
			}
			if((clearflag & ClearFlags_Depth) != 0)
			{
				set_depth(i, j, 1);
			}
		}
	}
	if (SDL_MUSTLOCK(_surface)) {
		SDL_UnlockSurface(_surface);
	}
}

void Graphics::clear_color(Color color)
{
	_clear_color = color;
}

void Graphics::set_renderbuffer(RenderBuffer* buffer)
{
	_renderbuffer = buffer;
}

void Graphics::set_shader(Shader* shader)
{
	_shader = shader;
}

void Graphics::bind_vertexdata(Vector3* data, int count)
{
	_vertexdata = data;
	_vertexcount = count;
	if (_vertexdata == nullptr)
		_vertexcount = 0;
}

void Graphics::bind_texcoorddata(Vector2* data, int count, int channel)
{
	if(channel == 0)
	{
		_uv0data = data;
		_uv0count = count;
		if (_uv0data == nullptr)
			_uv0count = 0;
	}
	else if(channel == 1)
	{
		_uv1data = data;
		_uv1count = count;
		if (_uv1data == nullptr)
			_uv1count = 0;
	}
	else if (channel == 2)
	{
		_uv2data = data;
		_uv2count = count;
		if (_uv2data == nullptr)
			_uv2count = 0;
	}
	else if (channel == 3)
	{
		_uv3data = data;
		_uv3count = count;
		if (_uv3data == nullptr)
			_uv3count = 0;
	}
}

void Graphics::bind_colordata(Color* data, int count)
{
	_colordata = data;
	_colorcount = count;
	if (_colordata == nullptr)
		_colorcount = 0;
}

void Graphics::bind_indexdata(unsigned int* data, int count)
{
	_indexdata = data;
	_indexcount = count;
	if (_indexdata == nullptr)
		_indexcount = 0;
}

void Graphics::draw_primitive(Primitive primitive)
{
	switch (primitive) {
	case Primitive_Point:
		draw_points();
		break;
	case Primitive_Triangle:
		draw_triangles();
		break;
	case Primitive_Line:
		draw_lines();
		break;
	case Primitive_LineStrip:
		draw_linestrips();
		break;
	}
}

void Graphics::set_zwrite(bool enable)
{
	_zwrite = enable;
}

void Graphics::set_ztest(CompareFunction ztest)
{
	_ztest = ztest;
}

void Graphics::set_blendmode(BlendMode src, BlendMode dst)
{
	_src = src;
	_dst = dst;
}

void Graphics::set_blend(bool enable)
{
	_blend = enable;
}

void Graphics::set_cullmode(CullMode cullmode)
{
	_cullmode = cullmode;
}

void Graphics::set_pixel(int x, int y, Color color)
{
	if(_renderbuffer != nullptr)
	{
		_renderbuffer->set_pixel(x, y, color);
		return;
	}

	int r = int(color.r * 255.0f);
	int g = int(color.g * 255.0f);
	int b = int(color.b * 255.0f);
	int a = int(color.a * 255.0f);
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	if (a < 0)
		a = 0;
	else if (a > 255)
		a = 255;
	Uint32 ucolor = SDL_MapRGBA(_surface->format, r, g, b, a);

	if (x < 0 || x >= _width)
		return;
	if (y < 0 || y >= _height)
		return;

	int bpp = _surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = ucolor;
		break;

	case 2:
		*(Uint16 *)p = ucolor;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (ucolor >> 16) & 0xff;
			p[1] = (ucolor >> 8) & 0xff;
			p[2] = ucolor & 0xff;
		}
		else {
			p[0] = ucolor & 0xff;
			p[1] = (ucolor >> 8) & 0xff;
			p[2] = (ucolor >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = ucolor;
		break;
	}
}

void Graphics::set_depth(int x, int y, float depth)
{
	if (_renderbuffer != nullptr) {
		_renderbuffer->set_depth(x, y, depth);
		return;
	}
	if (x < 0 || x >= _width)
		return;
	if (y < 0 || y >= _height)
		return;
	_zbuffer[y*_width + x] = depth;
}

Color Graphics::get_pixel(int x, int y)
{
	int bpp = _surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;
	Uint8 r, g, b, a;

	switch (bpp) {
	case 1:
		SDL_GetRGBA( *p, _surface->format, &r, &g, &b, &a);
		break;
	case 2:
		SDL_GetRGBA(*((Uint16 *)p), _surface->format, &r, &g, &b, &a);
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			SDL_GetRGBA(p[0] << 16 | p[1] << 8 | p[2], _surface->format, &r, &g, &b, &a);
		else
			SDL_GetRGBA(p[0] | p[1] << 8 | p[2] << 16, _surface->format, &r, &g, &b, &a);
		break;

	case 4:
		SDL_GetRGBA(*(Uint32 *)p, _surface->format, &r, &g, &b, &a);
		break;

	default:
		break;
	}
	return Color::rgba32(r, g, b, a);
}

float Graphics::get_depth(int x, int y)
{
	if(_renderbuffer != nullptr)
	{
		return _renderbuffer->get_depth(x, y);
	}
	if (x < 0 || x >= _width)
		return 1;
	if (y < 0 || y >= _height)
		return 1;
	return _zbuffer[y * _width + x];
}

void Graphics::draw_points()
{
	if (_shader == nullptr)
		return;
	if (SDL_MUSTLOCK(_surface)) {
		if (SDL_LockSurface(_surface) < 0)
			return;
	}
	for (int i = 0; i < _indexcount; i += 1)
	{
		int index = _indexdata[i];
		if (index >= _vertexcount) {
			break;
		}

		VertexInput vertex;
		vertex.vertex = _vertexdata[index];

		if (index < _colorcount)
			vertex.color = _colordata[index];

		if (index < _uv0count)
			vertex.uv0 = _uv0data[index];

		if (index < _uv1count)
			vertex.uv1 = _uv1data[index];

		if (index < _uv2count)
			vertex.uv2 = _uv2data[index];

		if (index < _uv3count)
			vertex.uv3 = _uv3data[index];

		FragmentInput output[1];

		_shader->vert(vertex, output[0]);

		if (frustumculling(output, 1) == false)
			continue;

		_point_rasterization->rasterize(this, output, _width, _height);
		
	}
	if (SDL_MUSTLOCK(_surface)) {
		SDL_UnlockSurface(_surface);
	}
}

void Graphics::draw_triangles()
{
	if (_shader == nullptr)
		return;
	if (SDL_MUSTLOCK(_surface)) {
		if (SDL_LockSurface(_surface) < 0)
			return;
	}
	for(int i=0;i<_indexcount-2;i+=3)
	{
		int i0 = _indexdata[i];
		if (i0 >= _vertexcount)
			break;
		int i1 = _indexdata[i + 1];
		if (i1 >= _vertexcount)
			break;
		int i2 = _indexdata[i + 2];
		if (i2 >= _vertexcount)
			break;

		VertexInput vertex0, vertex1, vertex2;
		vertex0.vertex = _vertexdata[i0];
		vertex1.vertex = _vertexdata[i1];
		vertex2.vertex = _vertexdata[i2];

		if (i0 < _colorcount)
			vertex0.color = _colordata[i0];
		if (i1 < _colorcount)
			vertex1.color = _colordata[i1];
		if (i2 < _colorcount)
			vertex2.color = _colordata[i2];

		if (i0 < _uv0count)
			vertex0.uv0 = _uv0data[i0];
		if (i1 < _uv0count)
			vertex1.uv0 = _uv0data[i1];
		if (i2 < _uv0count)
			vertex2.uv0 = _uv0data[i2];

		if (i0 < _uv1count)
			vertex0.uv1 = _uv1data[i0];
		if (i1 < _uv1count)
			vertex1.uv1 = _uv1data[i1];
		if (i2 < _uv1count)
			vertex2.uv1 = _uv1data[i2];

		if (i0 < _uv2count)
			vertex0.uv2 = _uv2data[i0];
		if (i1 < _uv2count)
			vertex1.uv2 = _uv2data[i1];
		if (i2 < _uv2count)
			vertex2.uv2 = _uv2data[i2];

		if (i0 < _uv3count)
			vertex0.uv3 = _uv3data[i0];
		if (i1 < _uv3count)
			vertex1.uv3 = _uv3data[i1];
		if (i2 < _uv3count)
			vertex2.uv3 = _uv3data[i2];
		
		FragmentInput output[3];

		_shader->vert(vertex0, output[0]);
		_shader->vert(vertex1, output[1]);
		_shader->vert(vertex2, output[2]);

		if (frustumculling(output, 3) == false)
			continue;;

		_triangle_rasterization->rasterize(this, output, _width, _height);
	}
	if (SDL_MUSTLOCK(_surface)) {
		SDL_UnlockSurface(_surface);
	}
}

void Graphics::draw_lines()
{
	if (_shader == nullptr)
		return;
	if (SDL_MUSTLOCK(_surface)) {
		if (SDL_LockSurface(_surface) < 0)
			return;
	}
	for (int i = 0; i < _indexcount-1; i += 2)
	{
		int i0 = _indexdata[i];
		if (i0 >= _vertexcount)
			break;
		int i1 = _indexdata[i + 1];
		if (i1 >= _vertexcount)
			break;

		VertexInput vertex0, vertex1;
		vertex0.vertex = _vertexdata[i0];
		vertex1.vertex = _vertexdata[i1];

		if (i0 < _colorcount)
			vertex0.color = _colordata[i0];
		if (i1 < _colorcount)
			vertex1.color = _colordata[i1];

		if (i0 < _uv0count)
			vertex0.uv0 = _uv0data[i0];
		if (i1 < _uv0count)
			vertex1.uv0 = _uv0data[i1];

		if (i0 < _uv1count)
			vertex0.uv1 = _uv1data[i0];
		if (i1 < _uv1count)
			vertex1.uv1 = _uv1data[i1];

		if (i0 < _uv2count)
			vertex0.uv2 = _uv2data[i0];
		if (i1 < _uv2count)
			vertex1.uv2 = _uv2data[i1];

		if (i0 < _uv3count)
			vertex0.uv3 = _uv3data[i0];
		if (i1 < _uv3count)
			vertex1.uv3 = _uv3data[i1];

		FragmentInput output[2];

		_shader->vert(vertex0, output[0]);
		_shader->vert(vertex1, output[1]);

		if (frustumculling(output, 2) == false)
			continue;

		_line_rasterization->rasterize(this, output, _width, _height);
	}
	if (SDL_MUSTLOCK(_surface)) {
		SDL_UnlockSurface(_surface);
	}
}

void Graphics::draw_linestrips()
{
	if (_shader == nullptr)
		return;
	if (SDL_MUSTLOCK(_surface)) {
		if (SDL_LockSurface(_surface) < 0)
			return;
	}
	for (int i = 0; i < _indexcount - 1; i += 1)
	{
		int i0 = _indexdata[i];
		if (i0 >= _vertexcount)
			break;
		int i1 = _indexdata[i + 1];
		if (i1 >= _vertexcount)
			break;

		VertexInput vertex0, vertex1;
		vertex0.vertex = _vertexdata[i0];
		vertex1.vertex = _vertexdata[i1];

		if (i0 < _colorcount)
			vertex0.color = _colordata[i0];
		if (i1 < _colorcount)
			vertex1.color = _colordata[i1];

		if (i0 < _uv1count)
			vertex0.uv1 = _uv1data[i0];
		if (i1 < _uv1count)
			vertex1.uv1 = _uv1data[i1];

		if (i0 < _uv2count)
			vertex0.uv2 = _uv2data[i0];
		if (i1 < _uv2count)
			vertex1.uv2 = _uv2data[i1];

		if (i0 < _uv3count)
			vertex0.uv3 = _uv3data[i0];
		if (i1 < _uv3count)
			vertex1.uv3 = _uv3data[i1];

		FragmentInput output[2];

		_shader->vert(vertex0, output[0]);
		_shader->vert(vertex1, output[1]);

		if (frustumculling(output, 2) == false)
			continue;

		_line_rasterization->rasterize(this, output, _width, _height);
	}
	if (SDL_MUSTLOCK(_surface)) {
		SDL_UnlockSurface(_surface);
	}
}

bool Graphics::buffer_compare(CompareFunction func, float current, float target)
{
	switch (func)
	{
	case CompareFunction_Always:
		return true;
	case CompareFunction_Equal:
		return IS_FLOAT_EQUAL(current, target);
	case CompareFunction_Greater:
		return current > target;
	case CompareFunction_Less:
		return current < target;
	case CompareFunction_GreaterEqual:
		return current > target || IS_FLOAT_EQUAL(current, target);
	case CompareFunction_LessEqual:
		return current < target || IS_FLOAT_EQUAL(current, target);
	case CompareFunction_Never:
		return false;
	case CompareFunction_NotEqual:
		return IS_FLOAT_EQUAL(current, target) == false;
	}
	return false;
}

Color Graphics::blend_color(const Color& srccolor, const Color& dstcolor, BlendMode srcfactor, BlendMode dstfactor)
{
	Color a = get_blend_factor(srccolor, dstcolor, srcfactor);
	Color b = get_blend_factor(srccolor, dstcolor, dstfactor);

	return srccolor * a + dstcolor * b;
}

bool Graphics::frustumculling(FragmentInput* inputs, int count)
{
	if (count <= 0)
		return false;
	float minx = inputs[0].position.x / inputs[0].position.w;
	float maxx = minx;
	float miny = inputs[0].position.y / inputs[0].position.w;
	float maxy = miny;
	float minz = inputs[0].position.z / inputs[0].position.w;
	float maxz = minz;

	for(int i=1;i<count;i++)
	{
		float x = inputs[i].position.x / inputs[i].position.w;
		float y = inputs[i].position.y / inputs[i].position.w;
		float z = inputs[i].position.z / inputs[i].position.w;

		minx = min(x, minx);
		maxx = max(x, maxx);
		miny = min(y, miny);
		maxy = max(y, maxy);
		minz = min(z, minz);
		maxz = max(z, maxz);
	}

	if (minx >= -1.0f && maxx <= 1.0f && miny >= -1.0f && maxy <= 1.0f && minz >= -1.0f && maxz <= 1.0f)
		return true;
	return false;
}

Color Graphics::get_blend_factor(const Color& srccolor, const Color& dstcolor, BlendMode factor)
{
	switch (factor)
	{
	case BlendMode_Zero:
		return Color(0, 0, 0, 0);
	case BlendMode_DstAlpha:
		return Color(dstcolor.a, dstcolor.a, dstcolor.a, dstcolor.a);
	case BlendMode_DstColor:
		return dstcolor;
	case BlendMode_One:
		return Color(1, 1, 1, 1);
	case BlendMode_OneMinusDstAlpha:
		return Color(1.0f - dstcolor.a, 1.0f - dstcolor.a, 1.0f - dstcolor.a, 1.0f - dstcolor.a);
	case BlendMode_OneMinusDstColor:
		return Color(1.0f - dstcolor.r, 1.0f - dstcolor.g, 1.0f - dstcolor.b, 1.0f - dstcolor.a);
	case BlendMode_OneMinusSrcAlpha:
		return Color(1.0f - srccolor.a, 1.0f - srccolor.a, 1.0f - srccolor.a, 1.0f - srccolor.a);
	case BlendMode_OneMinusSrcColor:
		return Color(1.0f - srccolor.r, 1.0f - srccolor.g, 1.0f - srccolor.b, 1.0f - srccolor.a);
	case BlendMode_SrcAlpha:
		return Color(srccolor.a, srccolor.a, srccolor.a, srccolor.a);
	case BlendMode_SrcColor:
		return srccolor;
	}
	return Color(0, 0, 0, 0);
}

void Graphics::rasterize_fragment(int x, int y, FragmentInput& frag)
{
	Color outcolor;
	float depth = frag.position.z / frag.position.w * 0.5f + 0.5f;
	float targetdepth = get_depth(x, y);

	if (buffer_compare(_ztest, depth, targetdepth)) {
		if (_shader->frag(frag, outcolor))
		{
			if(_blend)
			{
				Color dst = get_pixel(x, y);
				if(dst.r > 0.1 || dst.g > 0.1 || dst.b > 0.1)
				{
					int a;
				}
				Color outc = blend_color(outcolor, dst, _src, _dst);
				set_pixel(x, y, outc);
			}
			else
				set_pixel(x, y, outcolor);
			if (_zwrite) {
				set_depth(x, y, depth);
			}
		}
	}else
	{
		return;
	}
}
