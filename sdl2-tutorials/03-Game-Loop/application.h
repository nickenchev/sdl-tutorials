#pragma once

#include "sprite.h"

struct SDL_Window;
struct SDL_Renderer;

struct Vec2f
{
	float x, y;
	Vec2f() : x(0), y(0) { }
};

class Application
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	const Uint8 *keys;
	int width, height, windowWidth, windowHeight;
	uint32_t prevTime;

	Sprite grass1, ball, spike;
	Vec2f ballPos;

	void draw(const Sprite &sprite, int xPos, int yPos);

public:
	Application(int width, int height);
	~Application();

	void gameLoop();
};
