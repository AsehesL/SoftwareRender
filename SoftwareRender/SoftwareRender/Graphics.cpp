#include "Graphics.h"
#include <Windows.h>

Graphics::Graphics()
{
	_renderbuffer = 0;
	_surface = 0;
	_zbuffer = 0;
	_shader = 0;
	_vertexdata = 0;
	_colordata = 0;
	_indexdata = 0;
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
	SDL_FillRect(_surface, 0, 0);

	_zbuffer = new float[width*height];
	_width = width;
	_height = height;

	_point_rasterization = new PointRasterization();
	_line_rasterization = new LineRasterization();
	_triangle_rasterization = new TriangleRasterization();

	return true;
}

void Graphics::clear(int clearflag)
{
	int r = int(_clear_color.r * 255.0f);
	int g = int(_clear_color.g * 255.0f);
	int b = int(_clear_color.b * 255.0f);
	int a = int(_clear_color.a * 255.0f);
	UINT32 ucolor = SDL_MapRGBA(_surface->format, r, g, b, a);
	SDL_FillRect(_surface, 0, ucolor);
	/*for(int j=0;j<_height;j++)
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
	}*/
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

void Graphics::set_zwrite(bool zwrite)
{
	_zwrite = zwrite;
}

void Graphics::set_ztest(CompareFunction ztest)
{
	_ztest = ztest;
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
	UINT32 ucolor = SDL_MapRGBA(_surface->format, r, g, b, a);

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
	for (int i = 0; i < _indexcount; i += 1)
	{
		int index = _indexdata[i];
		if (index >= _vertexcount)
			return;

		VertexInput vertex;
		vertex.vertex = _vertexdata[index];

		if (index < _colorcount)
			vertex.color = _colordata[index];

		FragmentInput output[1];

		_shader->vert(vertex, output[0]);


		_point_rasterization->rasterize(this, output, _width, _height);
		
	}
}

void Graphics::draw_triangles()
{
	if (_shader == nullptr)
		return;
	for(int i=0;i<_indexcount-2;i+=3)
	{
		int i0 = _indexdata[i];
		if (i0 >= _vertexcount)
			return;
		int i1 = _indexdata[i + 1];
		if (i1 >= _vertexcount)
			return;
		int i2 = _indexdata[i + 2];
		if (i2 >= _vertexcount)
			return;

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

		FragmentInput output[3];

		_shader->vert(vertex0, output[0]);
		_shader->vert(vertex1, output[1]);
		_shader->vert(vertex2, output[2]);

		_triangle_rasterization->rasterize(this, output, _width, _height);
	}
}

void Graphics::draw_lines()
{
	if (_shader == nullptr)
		return;
	for (int i = 0; i < _indexcount-1; i += 2)
	{
		int i0 = _indexdata[i];
		if (i0 >= _vertexcount)
			return;
		int i1 = _indexdata[i + 1];
		if (i1 >= _vertexcount)
			return;

		VertexInput vertex0, vertex1;
		vertex0.vertex = _vertexdata[i0];
		vertex1.vertex = _vertexdata[i1];

		if (i0 < _colorcount)
			vertex0.color = _colordata[i0];
		if (i1 < _colorcount)
			vertex1.color = _colordata[i1];

		FragmentInput output[2];

		_shader->vert(vertex0, output[0]);
		_shader->vert(vertex1, output[1]);

		_line_rasterization->rasterize(this, output, _width, _height);
	}
}

void Graphics::draw_linestrips()
{
	if (_shader == nullptr)
		return;
	for (int i = 0; i < _indexcount - 1; i += 1)
	{
		int i0 = _indexdata[i];
		if (i0 >= _vertexcount)
			return;
		int i1 = _indexdata[i + 1];
		if (i1 >= _vertexcount)
			return;

		VertexInput vertex0, vertex1;
		vertex0.vertex = _vertexdata[i0];
		vertex1.vertex = _vertexdata[i1];

		if (i0 < _colorcount)
			vertex0.color = _colordata[i0];
		if (i1 < _colorcount)
			vertex1.color = _colordata[i1];

		FragmentInput output[2];

		_shader->vert(vertex0, output[0]);
		_shader->vert(vertex1, output[1]);

		_line_rasterization->rasterize(this, output, _width, _height);
	}
}

void Graphics::rasterize_fragment(int x, int y, FragmentInput& frag)
{
	Color outcolor;
	float depth = frag.position.z / frag.position.w * 0.5f + 0.5f;

	if(_shader->frag(frag, outcolor))
	{
		set_pixel(x, y, outcolor);
		if (_zwrite) {
			set_depth(x, y, depth);
		}
	}
}
