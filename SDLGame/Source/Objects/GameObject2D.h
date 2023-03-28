#pragma once
#include "SDL.h"
#include <string>

using namespace std;

struct Transform2D
{
	SDL_Point position;
	SDL_Point scale;
	SDL_Point rotation;
};

class GameObject2D
{
public:
	GameObject2D();
	~GameObject2D();

	// used for any variables and data that needs to be setup on the object before we try to use it.
	void Init(string TextureFile, SDL_Renderer* renderer);

	// used to render the object to the screen
	void Draw(SDL_Window* window, SDL_Renderer* renderer);

	// used to update processing on the object (in case it's moving or has some processing to compute)
	void Update();

	// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
	void Destroy();

private:
	// pos, rot, scale
	Transform2D transform;

	// width and height
	SDL_Point Dimensions;

	// loaded up sprite with information about the texture and it's data
	SDL_Texture* sprite;
};

