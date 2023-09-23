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

	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("SDL2 Tutorials", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
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

	// set a logical resolution, independant of the actual screen/window resolution
	SDL_RenderSetLogicalSize(renderer, width, height);

	// load assets
	grass1 = Sprite::load("data/grass1.png", renderer);
	ball = Sprite::load("data/ball.png", renderer);
	spike = Sprite::load("data/spike.png", renderer);
	gameSetup();
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
	SDL_Rect rect{ .x = xPos, .y = yPos, .w = sprite.width(), .h = sprite.height() };
	SDL_RenderCopy(renderer, sprite.texture(), nullptr, &rect);
}

void Application::gameSetup()
{
	ballX = static_cast<float>(width / 2 - ball.width());
	ballY = static_cast<float>(height - grass1.height() - ball.height());
	moveDirection = MoveDirection::none;
}

void Application::processKey(SDL_Keycode keycode, bool isDown)
{
	switch (keycode)
	{
		case SDLK_a:
		{
			moveDirection = isDown ? MoveDirection::left : MoveDirection::none;
			break;
		}
		case SDLK_d:
		{
			moveDirection = isDown ? MoveDirection::right : MoveDirection::none;
			break;
		}
	}
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
				case SDL_KEYDOWN:
				{
					processKey(event.key.keysym.sym, true);
					break;
				}
				case SDL_KEYUP:
				{
					processKey(event.key.keysym.sym, false);
					break;
				}
				case SDL_QUIT:
				{
					running = false;
				}
			}
		}

		if (moveDirection == MoveDirection::left)
		{
			ballX -= 0.1f;
		}
		if (moveDirection == MoveDirection::right)
		{
			ballX += 0.1f;
		}

		// clear the background
		SDL_SetRenderDrawColor(renderer, 203, 219, 252, 255);
		SDL_RenderClear(renderer);

		// draw game sprites
		const int numTiles = 50;
		for (int x = 0; x < numTiles * grass1.width(); x += grass1.width())
		{
			int y = height - grass1.height();
			draw(grass1, x, y);
		}

		draw(ball, static_cast<int>(ballX), static_cast<int>(ballY));
		draw(spike, 200, height - spike.height()- grass1.height());

		// swap buffers
		SDL_RenderPresent(renderer);
	}
}
