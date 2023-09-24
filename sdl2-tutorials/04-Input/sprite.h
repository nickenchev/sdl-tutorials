#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Sprite
{
	SDL_Texture *tex;
	int width, height;

public:
	Sprite() : width(0), height(0), tex(nullptr) {}
	Sprite(int width, int height, SDL_Texture *texture) : width(width), height(height)
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

	int w() const { return width; }
	int h() const { return height; }
	SDL_Texture *texture() const { return tex; }

	static Sprite load(const std::string &filePath, SDL_Renderer *renderer)
	{
		SDL_Surface *surface = IMG_Load(filePath.c_str());
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

		return Sprite(surface->w, surface->h, texture);
	}
};

