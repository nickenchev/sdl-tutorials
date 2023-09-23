#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Sprite
{
	SDL_Texture *tex;
	int w, h;

public:
	Sprite() : w(0), h(0), tex(nullptr) {}
	Sprite(int width, int height, SDL_Texture *texture) : w(width), h(height)
	{
		this->tex = texture;
	}

	void destroy()
	{
		if (tex)
		{
			SDL_DestroyTexture(tex);
		}
	}

	int width() const { return w; }
	int height() const { return h; }
	SDL_Texture *texture() const { return tex; }

	static Sprite load(const std::string &filePath, SDL_Renderer *renderer)
	{
		SDL_Surface *surface = IMG_Load(filePath.c_str());
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

		return Sprite(surface->w, surface->h, texture);
	}
};

