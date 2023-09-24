#include <SDL.h>
#include <iostream>
#include <vector>

#include "application.h"

int main(int argc, char *argv[])
{
	Application app(1920, 1080);
	app.gameLoop();

	return 0;
}

