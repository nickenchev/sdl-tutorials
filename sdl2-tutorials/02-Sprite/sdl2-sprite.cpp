#include <SDL.h>
#include <iostream>

struct Application
{
	SDL_Window *window;
};

void initializeSDL(Application &app)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "Couldn't initialize SDL2" << std::endl;
		exit(1);
	}
	app.window = SDL_CreateWindow("SDL2 Tutorials", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_RENDERER_ACCELERATED);
	if (!app.window)
	{
		std::cout << "Couldn't create the application window" << std::endl;
		exit(1);
	}
}

void shutdownSDL(Application &app)
{
	SDL_DestroyWindow(app.window);
	SDL_Quit();
}

void gameLoop(Application &app)
{
	SDL_Event event;
	bool running = true;
	while(running)
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

int main(int argc, char *argv[])
{
	Application app;
	initializeSDL(app);

	gameLoop(app);

	shutdownSDL(app);
	return 0;
}

