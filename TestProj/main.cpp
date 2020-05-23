#include "stdafx.h"
#include "Types.h"
#include "SDLExtensions.h"
#include "Input.h"
#include <chrono>
#include "Scene.h"

static bool isGameRunning = true;

int _tmain(int argc, _TCHAR* argv[])
{

	SDL_Window* wnd = nullptr;
	SDL_Renderer* renderer = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		std::cout << "Unable to init sdl";
		return -1;
	}

	wnd = SDL_CreateWindow("Arcanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
	if (wnd == nullptr)
	{
		std::cout << "Unable to craete window";
		return -1;
	}

	renderer = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Unable to craete window renderer";
		return -1;
	}

	Color clearColor(16, 16, 16, 255);

	{
		Scene scene;
		scene.Setup();

		auto prevTime = std::chrono::steady_clock::now();
		while (isGameRunning)
		{
			SDL_Event evt;
			while (SDL_PollEvent(&evt) > 0)
			{
				switch (evt.type)
				{
				case SDL_KEYUP:
					Input::Get().KeyUp(evt.key.keysym.sym);
					break;
				case SDL_KEYDOWN:
					Input::Get().KeyDown(evt.key.keysym.sym);
					break;
				default:
					break;
				}
			}

			if (Input::Get().GetInput(SDL_KeyCode::SDLK_ESCAPE))
				break;


			auto currentTime = std::chrono::steady_clock::now();
			auto dt = (currentTime - prevTime).count()* (1.f / 10000000.0f);

			prevTime = currentTime;
			scene.Update(dt);

			SDLEx_SetRendererDrawingColor(renderer, clearColor);
			SDL_RenderClear(renderer);

			scene.Render(renderer);

			SDL_RenderPresent(renderer);
		}

	}
	SDL_DestroyWindow(wnd);

	SDL_Quit();
	return 0;
}