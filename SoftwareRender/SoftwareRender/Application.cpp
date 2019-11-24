#include "Application.h"
#include <windows.h>
#include "ColorShader.h"

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
			Vector3(-0.5f,  0.0f, 0.0f),
			Vector3(0.0f, 1.0f, 0.0f),
			Vector3 (0.5f, 0.0f, 0.0f),
	};
	Color colordata[] = {
		Color(1.0f,0.0f,0.0f,1.0f),
		Color(0.0f,1.0f,0.0f,1.0f),
		Color(0.0f,0.0f,1.0f,1.0f),
	};
	unsigned int indices[] = {  
		0, 1, 2, 
	};
	ColorShader* cshader = new ColorShader();
	Matrix localtoworld,worldtocamera,projection;
	Vector3 pos(-0.52087f, -0.9703822f, 1.703086f);
	Quaternion rot;
	Quaternion::euler(&rot, 0, 0, 0);
	Vector3 scale(1, 1, 1);
	Matrix::TRS(&localtoworld, pos, rot, scale);
	Matrix::lookat(&worldtocamera, Vector3(-1.0480f, 0.0833f, 0.1733f), Vector3(-1.0480f + 0.2954f, 0.0833f - 0.3929f, 0.1733f + 0.8708f), Vector3(0.1262f, 0.9196f, 0.3721f));
	Matrix::perspective(&projection, 60 * DEG_TO_RAD, ((float)width) / height, 0.3f, 1000.0f);
	cshader->set_model_matrix(&localtoworld);
	cshader->set_view_matrix(&worldtocamera);
	cshader->set_projection_matrix(&projection);

	graphics->bind_vertexdata(vertexdata, 3);
	graphics->bind_colordata(colordata, 3);
	graphics->bind_indexdata(indices, 3);
	graphics->set_shader(cshader);
	graphics->draw_primitive(Primitive_LineStrip);
	graphics->set_shader(0);
	delete cshader;
	cshader = 0;

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
