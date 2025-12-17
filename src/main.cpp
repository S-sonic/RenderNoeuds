#include <iostream>
#include <SDL3/SDL.h>

int main(int argc, char** argv)
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
	{
		std::cerr << "Init error : " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	auto window = SDL_CreateWindow("RenderNoeuds", 720, 405, SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cerr << "Window creation error : " << SDL_GetError() << std::endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	bool isRunning = true;

	while (isRunning)
	{
		// render here

		// input
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EventType::SDL_EVENT_QUIT:
				isRunning = false;
				break;
			}
		}
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}