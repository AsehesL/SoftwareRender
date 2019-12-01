#include "Application.h"
#include <windows.h>
#include "TextureShader.h"

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

	_mesh = new Mesh();
	/*_mesh->set_vertices(new Vector3[8]{
			Vector3(-0.5f, -0.5f, -0.5f), Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.5f, 0.5f, -0.5f), Vector3(0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, -0.5f, 0.5f), Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.5f, 0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f),
		}, 8);
	_mesh->set_colors(new Color[8]{
		Color(0.0f,0.0f,0.0f,1.0f), Color(1.0f,0.0f,0.0f,1.0f), Color(1.0f,1.0f,0.0f,1.0f), Color(0.0f,1.0f,0.0f,1.0f),
		Color(0.0f,0.0f,1.0f,1.0f), Color(1.0f,0.0f,1.0f,1.0f), Color(1.0f,1.0f,1.0f,1.0f), Color(0.0f,1.0f,1.0f,1.0f),
		});
	_mesh->set_indices(new unsigned int[36]{
		0, 1, 2, 0, 2, 3,
			1, 5, 6, 1, 6, 2,
			5, 4, 7, 5, 7, 6,
			4, 0, 3, 4, 3, 7,
			4, 5, 1, 4, 1, 0,
			3, 2, 6, 3, 6, 7,
		}, 36);*/
	_mesh->set_vertices(new Vector3[24]{ Vector3(0.500f, -0.500f, 0.500f),Vector3(-0.500f, -0.500f, 0.500f),Vector3(0.500f, 0.500f, 0.500f),Vector3(-0.500f, 0.500f, 0.500f),Vector3(0.500f, 0.500f, -0.500f),Vector3(-0.500f, 0.500f, -0.500f),Vector3(0.500f, -0.500f, -0.500f),Vector3(-0.500f, -0.500f, -0.500f),Vector3(0.500f, 0.500f, 0.500f),Vector3(-0.500f, 0.500f, 0.500f),Vector3(0.500f, 0.500f, -0.500f),Vector3(-0.500f, 0.500f, -0.500f),Vector3(0.500f, -0.500f, -0.500f),Vector3(0.500f, -0.500f, 0.500f),Vector3(-0.500f, -0.500f, 0.500f),Vector3(-0.500f, -0.500f, -0.500f),Vector3(-0.500f, -0.500f, 0.500f),Vector3(-0.500f, 0.500f, 0.500f),Vector3(-0.500f, 0.500f, -0.500f),Vector3(-0.500f, -0.500f, -0.500f),Vector3(0.500f, -0.500f, -0.500f),Vector3(0.500f, 0.500f, -0.500f),Vector3(0.500f, 0.500f, 0.500f),Vector3(0.500f, -0.500f, 0.500f), }, 24);
	_mesh->set_uvs(new Vector2[24]{ Vector2(0.000f, 0.000f),Vector2(1.000f, 0.000f),Vector2(0.000f, 1.000f),Vector2(1.000f, 1.000f),Vector2(0.000f, 1.000f),Vector2(1.000f, 1.000f),Vector2(0.000f, 1.000f),Vector2(1.000f, 1.000f),Vector2(0.000f, 0.000f),Vector2(1.000f, 0.000f),Vector2(0.000f, 0.000f),Vector2(1.000f, 0.000f),Vector2(0.000f, 0.000f),Vector2(0.000f, 1.000f),Vector2(1.000f, 1.000f),Vector2(1.000f, 0.000f),Vector2(0.000f, 0.000f),Vector2(0.000f, 1.000f),Vector2(1.000f, 1.000f),Vector2(1.000f, 0.000f),Vector2(0.000f, 0.000f),Vector2(0.000f, 1.000f),Vector2(1.000f, 1.000f),Vector2(1.000f, 0.000f), }, 0);
	_mesh->set_indices(new unsigned int[36]{ 0,2,3,0,3,1,8,4,5,8,5,9,10,6,7,10,7,11,12,13,14,12,14,15,16,17,18,16,18,19,20,21,22,20,22,23, }, 36);
	TextureShader* sd = new TextureShader();
	_tex = new Texture();
	if (!_tex->load("7.bmp"))
		throw "ss";
	sd->set_texture(_tex);
	_shader = sd;
	_obj1 = new DisplayObject(_mesh, _shader);
	_obj2 = new DisplayObject(_mesh, _shader);
	_camera = new Camera(width, height);
	_camera->position = Vector3(-8.365381f, 25.30562f, -15.46281f);
	_camera->euler = Vector3(28.808f, -145.76f, 0.0f);

	_obj1->position = Vector3(-9.640829f, 24.16714f, -17.43065f);
	_obj1->euler = Vector3(-70.339f, 96.92001f, -49.959f);
	_obj2->position = Vector3(-10.76f, 23.73f, -20.55f);
	_obj2->euler = Vector3(8.554001f, -103.278f, 95.492f);

	//graphics->set_zwrite(false);
	//graphics->set_ztest(CompareFunction_Always);
	//graphics->set_blend(true);
	//graphics->set_blendmode(BlendMode_One, BlendMode_One);

	_camera->prepare_render();
	_obj1->draw(graphics);
	_obj2->draw(graphics);

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
			time += 1.0f;
			SDL_UpdateWindowSurface(window);
			Sleep(5);
		}
	}
}

void Application::close()
{
	delete graphics;
	graphics = 0;
	SDL_DestroyWindow(window);
	SDL_Quit();

	delete _mesh;
	delete _shader;
	delete _obj1;
	delete _obj2;
	delete _camera;
	delete _tex;
}

bool Application::application_loop(float time)
{
	graphics->clear(ClearFlags_Color | ClearFlags_Depth);
	_camera->prepare_render();
	Vector3 euler = _obj1->euler;
	euler.y += 12;
	_obj1->euler = euler;
	_obj1->draw(graphics);
	_obj2->draw(graphics);
	return true;
}
