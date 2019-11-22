#include "Graphics.h"
#include <Windows.h>

Graphics::Graphics()
{
}

Graphics::~Graphics()
{
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

void Graphics::draw_primitive(Primitive primitive, int count, int)
{

}

void Graphics::set_pixel(int x, int y, Uint32 color)
{
	if(_renderbuffer != nullptr)
	{
		_renderbuffer->set_pixel(x, y, color);
		return;
	}
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
