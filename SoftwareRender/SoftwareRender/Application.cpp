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
	_vertex = new Vector3[8] {
			Vector3(-0.5f, -0.5f, -0.5f), Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.5f, 0.5f, -0.5f), Vector3(0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, 0.5f), Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f),
	};
	_colors = new Color[8] {
		Color(0.0f,0.0f,0.0f,1.0f), Color(1.0f,0.0f,0.0f,1.0f), Color(1.0f,1.0f,0.0f,1.0f), Color(0.0f,1.0f,0.0f,1.0f),
		Color(0.0f,0.0f,1.0f,1.0f), Color(1.0f,0.0f,1.0f,1.0f), Color(1.0f,1.0f,1.0f,1.0f), Color(0.0f,1.0f,1.0f,1.0f),
	};
	_triangles = new unsigned int[36] {
		0, 1, 2, 0, 2, 3,
			1, 5, 6, 1, 6, 2,
			5, 4, 7, 5, 7, 6,
			4, 0, 3, 4, 3, 7,
			4, 5, 1, 4, 1, 0,
			3, 2, 6, 3, 6, 7,
	};
	testshader = new ColorShader();
	graphics->bind_vertexdata(_vertex, 8);
	graphics->bind_colordata(_colors, 8);
	graphics->bind_indexdata(_triangles, 36);
	graphics->set_shader(testshader);

	SDL_UpdateWindowSurface(window);
	return true;
}

void Application::run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	bool done = false;
	float time = 0.0f;
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
			if (!application_loop(time))
			{
				done = true;
			}
			time += 4.9f;
			SDL_UpdateWindowSurface(window);
		}
	}
}

void Application::close()
{
	delete graphics;
	graphics = 0;
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete testshader;
	delete[] _vertex;
	delete[] _colors;
	delete[] _triangles;
}

bool Application::application_loop(float time)
{
	Matrix localtoworld, worldtocamera, projection;
	Vector3 pos(-0.2846542f, -1.165807f, 2.7674f);
	Quaternion rot;
	Quaternion::euler(&rot, 22.19f, time, 20.05f);
	Vector3 scale(1, 1, 1);
	Matrix::TRS(&localtoworld, pos, rot, scale);
	Matrix::lookat(&worldtocamera, Vector3(0.9647f, 0.1606f, 4.2133f), Vector3(0.9647f - 0.5050f, 0.1606f - 0.5978f, 4.2133f - 0.6225f), Vector3(-0.3767f, 0.8016f, -0.4643f));
	Matrix::perspective(&projection, 60 * DEG_TO_RAD, ((float)graphics->get_width()) / graphics->get_height(), 0.3f, 1000.0f);
	testshader->set_model_matrix(localtoworld);
	testshader->set_view_matrix(worldtocamera);
	testshader->set_projection_matrix(projection);

	graphics->clear_color(Color(0, 0, 0, 1));
	graphics->clear(ClearFlags_Color | ClearFlags_Depth);
	graphics->set_shader(testshader);
	graphics->draw_primitive(Primitive_LineStrip);
	

	return true;
}
