#include "application.h"
#include <SDL.h>
#include <iostream>

Application::Application(int width, int height) : width(width), height(height)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		std::cout << "Couldn't initialize SDL2: " << SDL_GetError() << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow("SDL2 Tutorials", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (!window)
	{
		std::cout << "Couldn't create the application window:" << SDL_GetError() << std::endl;
		exit(1);
	}
}

Application::~Application()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Application::gameLoop()
{
	SDL_Event event;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					running = false;
				}
			}
		}
	}
}
