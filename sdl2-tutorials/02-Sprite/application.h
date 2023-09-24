#pragma once

#include "sprite.h"

struct SDL_Window;
struct SDL_Renderer;

class Application
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	const int width, height;
	int windowWidth, windowHeight;

	Sprite grass1, ball, spike;

	void draw(const Sprite &sprite, int xPos, int yPos);

public:
	Application(int width, int height);
	~Application();

	void gameLoop();
};
