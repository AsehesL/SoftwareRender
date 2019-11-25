#pragma once
#include "Graphics.h"
#include "ColorShader.h"

extern "C" {
#include "SDL.h"
}

class Application
{
public:
	Application();
	~Application();

	bool init(int width, int height, const char* applicationName);
	void run();
	void close();

private:
	bool application_loop(float time);

public:
	Graphics* graphics;
	SDL_Window* window;
	ColorShader* testshader;
	Vector3* _vertex;
	Color* _colors;
	unsigned int* _triangles;
};

