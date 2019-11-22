#pragma once
#include "Graphics.h"

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
	bool application_loop();

public:
	Graphics* graphics;
	SDL_Window* window;
};

