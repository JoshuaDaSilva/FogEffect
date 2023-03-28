#pragma once
#include "SDL.h"

class Utils
{
public:
	static int LoadSprite(const char *file, SDL_Renderer *renderer, SDL_Point* dimensions, SDL_Texture** sprite);
	static unsigned char * loadBMP(const char * imagepath, unsigned int &width, unsigned int &height);
};

