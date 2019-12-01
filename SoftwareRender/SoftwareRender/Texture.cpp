#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

bool Texture::load(const char* path)
{
	_surface = SDL_LoadBMP(path);
	return _surface != nullptr;
}

Color Texture::sample(float u, float v)
{
	if (SDL_MUSTLOCK(_surface)) {
		if (SDL_LockSurface(_surface) < 0)
			return Color(0,0,0,0);
	}

	int x = int(u * (get_width() - 1));
	int y = int(v * (get_height() - 1));

	Color color = get_pixel(x, y);

	if (SDL_MUSTLOCK(_surface)) {
		SDL_UnlockSurface(_surface);
	}

	return color;
}

Color Texture::get_pixel(int x, int y)
{
	int bpp = _surface->format->BytesPerPixel;

	Uint8 *p = (Uint8 *)_surface->pixels + y * _surface->pitch + x * bpp;
	Uint8 r, g, b, a;

	switch (bpp) {
	case 1:
		SDL_GetRGBA(*p, _surface->format, &r, &g, &b, &a);
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

int Texture::get_width()
{
	return _surface->w;
}

int Texture::get_height()
{
	return _surface->h;
}
