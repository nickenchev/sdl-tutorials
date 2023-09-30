#include "application.h"

#include <iostream>
#include <array>
#include <SDL.h>
#include <SDL_image.h>
#include <variant>

Application::Application(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight), width(640), height(360), rootWidget(UI::Spacer())
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
	keys = SDL_GetKeyboardState(nullptr);

	// initialize extensions
	IMG_Init(IMG_INIT_PNG);

	// configure a logical resolution
	SDL_RenderSetLogicalSize(renderer, width, height);

	// load assets
	grass1 = Sprite::load("data/grass1.png", renderer);
	ball = Sprite::load("data/ball.png", renderer);
	spike = Sprite::load("data/spike.png", renderer);

	// initialize game
	ballPos.x = static_cast<float>(width / 2 - ball.w() / 2);
	ballXAccel = 20.0f;
	ballXSpeed = 0;
	ballXMaxSpeed = 300.0f;
	prevTime = SDL_GetTicks();

	rootWidget.setLayout(UI::HorizontalLayout());
	rootWidget.setRect(UI::Rect(0, 0, static_cast<float>(width), static_cast<float>(height)));
	rootWidget.addChild(UI::Spacer());
	rootWidget.addChild(UI::Spacer());

	auto &rightPanel = rootWidget.addChild(UI::Spacer());
	rightPanel.setLayout(UI::VerticalLayout());
	UI::Widget &panel = rightPanel.addChild(UI::Panel(UI::Color4(0, 0, 255, 100)));
	panel.addChild(UI::Panel(UI::Color4(255, 0, 255, 255)));
	panel.addChild(UI::Panel(UI::Color4(255, 0, 255, 255)));
	panel.addChild(UI::Spacer());
	rightPanel.addChild(UI::Spacer());

	UI::LayoutVisitor visitor;
	visitor.layout(rootWidget);
}

void Application::drawUI(UI::Widget &widget, int i)
{
	if (std::holds_alternative<UI::Panel>(widget.getControl()))
	{
		const UI::Panel panel = std::get<UI::Panel>(widget.getControl());
		UI::Color4 backgroundColor = panel.getBackgroundColor();

		UI::Rect rect = widget.getRect();
		SDL_Rect box{ .x = static_cast<int>(rect.x), .y = static_cast<int>(rect.y), .w = static_cast<int>(rect.width), .h = static_cast<int>(rect.height) };
		SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		SDL_RenderFillRect(renderer, &box);
	}

	for (auto &child : widget.getChildren())
	{
		drawUI(child, ++i);
	}
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
	bool running = true;
	float interval = 1.0f / 60;
	float accumulator = 0;

	SDL_Event event;
	while (running)
	{
		uint32_t currentTime = SDL_GetTicks();
		float dt = (currentTime - prevTime) / 1000.0f;
		prevTime = currentTime;

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

		accumulator += dt;
		while (accumulator >= interval)
		{
			if (keys[SDL_SCANCODE_A])
			{
				if (ballXSpeed > -ballXMaxSpeed)
				{
					ballXSpeed -= ballXAccel;
				}
			}
			else if (keys[SDL_SCANCODE_D])
			{
				if (ballXSpeed < ballXMaxSpeed)
				{
					ballXSpeed += ballXAccel;
				}
			}
			else
			{
				ballXSpeed *= 0.85f;
				if (abs(ballXSpeed) < 0.01f) ballXSpeed = 0;
			}
			ballPos.x += ballXSpeed * interval;
			accumulator -= interval;
		}

		// draw the game scene
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// draw the grass
		const int numTiles = 50;
		for (int x = 0; x < numTiles * grass1.w(); x += grass1.w())
		{
			int y = height - grass1.h();
			draw(grass1, x, y);
		}

		draw(ball, static_cast<int>(ballPos.x), height - grass1.h() - ball.h());
		draw(spike, 200, height - spike.h() - grass1.h());

		drawUI(rootWidget, 0);

		// swap buffers
		SDL_RenderPresent(renderer);
	}
}
