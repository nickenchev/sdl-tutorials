#pragma once

struct SDL_Window;

class Application
{
	SDL_Window *window;
	int width, height;

public:
	Application(int width, int height);
	~Application();

	void gameLoop();
};
