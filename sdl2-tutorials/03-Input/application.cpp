#include "application.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

Application::Application(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight), width(640), height(360)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		std::cout << "Couldn't initialize SDL2: " << SDL_GetError() << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow("SDL2 Input", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		std::cout << "Couldn't create the application window:" << SDL_GetError() << std::endl;
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "Couldn't create renderer: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// initialize extensions
	IMG_Init(IMG_INIT_PNG);

	// configure a logical resolution
	SDL_RenderSetLogicalSize(renderer, width, height);

	// load assets
	grass1 = Sprite::load("data/grass1.png", renderer);
	ball = Sprite::load("data/ball.png", renderer);
	spike = Sprite::load("data/spike.png", renderer);
}

Application::~Application()
{
	grass1.destroy();
	ball.destroy();
	spike.destroy();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Application::draw(const Sprite &sprite, int xPos, int yPos)
{
	SDL_Rect rect{ .x = xPos, .y = yPos, .w = sprite.w(), .h = sprite.h() };
	SDL_RenderCopy(renderer, sprite.texture(), nullptr, &rect);
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

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// draw game sprites
		const int numTiles = 50;
		for (int x = 0; x < numTiles * grass1.w(); x += grass1.w())
		{
			int y = height - grass1.h();
			draw(grass1, x, y);
		}

		draw(ball, width / 2 - ball.w() / 2, height - grass1.h() - ball.h());
		draw(spike, 200, height - spike.h() - grass1.h());

		// swap buffers
		SDL_RenderPresent(renderer);
	}
}
