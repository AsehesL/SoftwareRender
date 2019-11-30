#pragma once
#include "Graphics.h"
#include "DisplayObject.h"
#include "Camera.h"

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
	DisplayObject* _obj1;
	DisplayObject* _obj2;
	Mesh* _mesh;
	Shader* _shader;
	Camera* _camera;
};

