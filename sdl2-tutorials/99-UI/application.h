#pragma once

#include "sprite.h"
#include "ui.h"

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
	float ballXAccel, ballXSpeed, ballXMaxSpeed;
	Vec2f ballPos;

	// UI Related
	UI::Widget rootWidget;

	void draw(const Sprite &sprite, int xPos, int yPos);
	void drawUI(UI::Widget &widget, int i);

public:
	Application(int width, int height);
	~Application();

	void gameLoop();
};
