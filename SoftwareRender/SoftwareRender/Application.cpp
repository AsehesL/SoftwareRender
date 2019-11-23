#include "Application.h"
#include <windows.h>

Application::Application()
{
}


Application::~Application()
{
}

bool Application::init(int width, int height, const char * applicationName)
{
	int posX, posY;
	posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	window = SDL_CreateWindow(applicationName, posX, posY, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		MessageBox(NULL, L"窗口创建失败", L"初始化失败", MB_ERR_INVALID_CHARS);
		return false;
	}
	graphics = new Graphics();
	if(!graphics->init(window, width, height))
	{
		return false;
	}
	Vector3 vertexdata[] = {
				 Vector3(0.5f,  0.5f, 0.0f),
			 Vector3(0.5f, -0.5f, 0.0f),
			Vector3 (-0.5f, -0.5f, 0.0f),
			Vector3 (-0.5f,  0.5f, 0.0f),
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 2, 1,   // first triangle
		0,3,2,
	};
	graphics->bind_vertexdata(vertexdata, 4);
	graphics->bind_indexdata(indices, 6);
	graphics->draw_primitive(Primitive_Triangle);

	SDL_UpdateWindowSurface(window);
	return true;
}

void Application::run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	bool done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else if (msg.message == WM_PAINT)
		{

		}
		else
		{
			if (!application_loop())
			{
				done = true;
			}
		}
	}
}

void Application::close()
{
	delete graphics;
	graphics = 0;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Application::application_loop()
{
	return true;
}
