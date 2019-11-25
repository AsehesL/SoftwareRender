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
	_vertex = new Vector3[3] {
			Vector3(-0.5f,  0.0f, 0.0f),
			Vector3(0.0f, 1.0f, 0.0f),
			Vector3 (0.5f, 0.0f, 0.0f),
	};
	_colors = new Color[3] {
		Color(1.0f,0.0f,0.0f,1.0f),
		Color(0.0f,1.0f,0.0f,1.0f),
		Color(0.0f,0.0f,1.0f,1.0f),
	};
	_triangles = new unsigned int[3] {
		0, 1, 2, 
	};
	testshader = new ColorShader();
	graphics->bind_vertexdata(_vertex, 3);
	graphics->bind_colordata(_colors, 3);
	graphics->bind_indexdata(_triangles, 3);
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
			time += 0.9f;
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
	Vector3 pos(-0.52087f, -0.9703822f, 1.703086f);
	Quaternion rot;
	Quaternion::euler(&rot, 0, time, 0);
	Vector3 scale(1, 1, 1);
	Matrix::TRS(&localtoworld, pos, rot, scale);
	Matrix::lookat(&worldtocamera, Vector3(-1.0480f, 0.0833f, 0.1733f), Vector3(-1.0480f + 0.2954f, 0.0833f - 0.3929f, 0.1733f + 0.8708f), Vector3(0.1262f, 0.9196f, 0.3721f));
	Matrix::perspective(&projection, 60 * DEG_TO_RAD, ((float)graphics->get_width()) / graphics->get_height(), 0.3f, 1000.0f);
	testshader->set_model_matrix(localtoworld);
	testshader->set_view_matrix(worldtocamera);
	testshader->set_projection_matrix(projection);

	graphics->clear_color(Color(0, 0, 0, 1));
	graphics->clear(ClearFlags_Color);
	graphics->set_shader(testshader);
	graphics->draw_primitive(Primitive_Triangle);
	

	return true;
}
