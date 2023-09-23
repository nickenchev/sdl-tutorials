#pragma once

#include "sprite.h"

struct SDL_Window;
struct SDL_Renderer;

enum class MoveDirection
{
	none, left, right
};

class Application
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int width, height, windowWidth, windowHeight;

	Sprite grass1, ball, spike;

	// movement
	float ballX, ballY;
	MoveDirection moveDirection;

	void draw(const Sprite &sprite, int xPos, int yPos);
	void processKey(SDL_Keycode keycode, bool isDown);

public:
	Application(int width, int height);
	~Application();

	void gameSetup();
	void gameLoop();
};
