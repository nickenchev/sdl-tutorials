#include <SDL.h>
#include <iostream>
#include <vector>

#include "application.h"

int main(int argc, char *argv[])
{
	Application app(1280, 720);
	app.gameSetup();
	app.gameLoop();

	return 0;
}

