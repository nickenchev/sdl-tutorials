#include <SDL.h>
#include "application.h"

int main(int argc, char *argv[])
{
	Application app(1024, 768);
	app.gameLoop();

	return 0;
}

