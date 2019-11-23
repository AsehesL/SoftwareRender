#include "Graphics.h"
#include <Windows.h>

Graphics::Graphics()
{
	_renderbuffer = 0;
	_surface = 0;
	_zbuffer = 0;
}

Graphics::~Graphics()
{
	delete[] _zbuffer;
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

	return true;
}

void Graphics::clear(ClearFlags clearflag)
{
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
}

void Graphics::clear_color(Uint32 color)
{
	_clear_color = color;
}

void Graphics::set_renderbuffer(RenderBuffer* buffer)
{
	_renderbuffer = buffer;
}

void Graphics::bind_vertexdata(Vector3* data, int count)
{
	_vertexdata = data;
	_vertexcount = count;
	if (_vertexdata == nullptr)
		_vertexcount = 0;
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
		//draw_point(count);
		break;
	case Primitive_Triangle:
		draw_triangles();
		break;
	}
}

void Graphics::set_pixel(int x, int y, Uint32 color)
{
	if(_renderbuffer != nullptr)
	{
		_renderbuffer->set_pixel(x, y, color);
		return;
	}
	if (x < 0 || x >= _width)
		return;
	if (y < 0 || y >= _height)
		return;

	int bpp = _surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = color;
		break;

	case 2:
		*(Uint16 *)p = color;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (color >> 16) & 0xff;
			p[1] = (color >> 8) & 0xff;
			p[2] = color & 0xff;
		}
		else {
			p[0] = color & 0xff;
			p[1] = (color >> 8) & 0xff;
			p[2] = (color >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = color;
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

void Graphics::draw_triangles()
{
	for(int i=0;i<_indexcount;i+=3)
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

		Vector3 v0 = _vertexdata[i0];
		Vector3 v1 = _vertexdata[i1];
		Vector3 v2 = _vertexdata[i2];

		draw_triangle(v0, v1, v2);
	}
}

void Graphics::draw_triangle(Vector3 v0, Vector3 v1, Vector3 v2)
{
	int screenV0x = int((v0.x + 1) * 0.5f * _width);
	int screenV0y = int((v0.y + 1) * 0.5f * _height);
	int screenV1x = int((v1.x + 1) * 0.5f * _width);
	int screenV1y = int((v1.y + 1) * 0.5f * _height);
	int screenV2x = int((v2.x + 1) * 0.5f * _width);
	int screenV2y = int((v2.y + 1) * 0.5f * _height);

	int minx = min_i(screenV0x, min_i(screenV1x, screenV2x));
	int miny = min_i(screenV0y, min_i(screenV1y, screenV2y));
	int maxx = max_i(screenV0x, max_i(screenV1x, screenV2x));
	int maxy = max_i(screenV0y, max_i(screenV1y, screenV2y));

	minx = clamp_i(minx, 0, _width - 1);
	maxx = clamp_i(maxx, 0, _width - 1);
	miny = clamp_i(miny, 0, _height - 1);
	maxy = clamp_i(maxy, 0, _height - 1);

	for (int i = minx; i <= maxx; i++)
	{
		for (int j = miny; j <= maxy; j++)
		{
			int bias0 = is_edge_topleft(screenV1x, screenV1y, screenV2x, screenV2y) ? 0 : -1;
			int bias1 = is_edge_topleft(screenV2x, screenV2y, screenV0x, screenV0y) ? 0 : -1;
			int bias2 = is_edge_topleft(screenV0x, screenV0y, screenV1x, screenV1y) ? 0 : -1;

			int w0 = edge_equation(screenV1x, screenV1y, screenV2x, screenV2y, i, j) + bias0;
			int w1 = edge_equation(screenV2x, screenV2y, screenV0x, screenV0y, i, j) + bias1;
			int w2 = edge_equation(screenV0x, screenV0y, screenV1x, screenV1y, i, j) + bias2;

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				float u, v;
				get_uv(screenV0x, screenV0y, screenV1x, screenV1y, screenV2x, screenV2y, i, j, u, v);
				//int r
				//Color col = (1.0f - u - v) * Color.red + v * Color.green + u * Color.blue;
				set_pixel(i, j, SDL_MapRGB(_surface->format, 255, 255, 255));
			}
		}
	}
}

int Graphics::edge_equation(int beginx, int beginy, int endx, int endy, int x, int y)
{
	return (endx - beginx) * (y - beginy) - (endy - beginy) * (x - beginx);
}

bool Graphics::is_edge_topleft(int x0, int y0, int x1, int y1)
{
	if (y0 == y1 && x0 > x1)
		return true;
	if (y0 > y1)
		return true;
	return false;
}

void Graphics::get_uv(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float& u, float& v)
{
	float v0x = x2 - x0;
	float v0y = y2 - y0;
	float v1x = x1 - x0;
	float v1y = y1 - y0;
	float v2x = x - x0;
	float v2y = y - y0;

	float dot00 = v0x * v0x + v0y * v0y;
	float dot01 = v0x * v1x + v0y * v1y;
	float dot02 = v0x * v2x + v0y * v2y;
	float dot11 = v1x * v1x + v1y * v1y;
	float dot12 = v1x * v2x + v1y * v2y;

	float inverDeno = 1.0f / (dot00 * dot11 - dot01 * dot01);

	u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
	v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
}

//void Graphics::draw_point(int)
//{
//}
