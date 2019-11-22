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
