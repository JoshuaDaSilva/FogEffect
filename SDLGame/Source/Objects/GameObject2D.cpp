#include "GameObject2D.h"
#include "..\Utils.h"

GameObject2D::GameObject2D()
{

}

GameObject2D::~GameObject2D()
{

}


void GameObject2D::Init(string TextureFile, SDL_Renderer* renderer)
{
	// if a texture is supplied load it up and apply it to the object.
	if(TextureFile != "")
	{
		Utils::LoadSprite(TextureFile.c_str(), renderer, &Dimensions, &sprite);
	}
		
}

void GameObject2D::Draw( SDL_Window* window, SDL_Renderer* renderer)
{
	if (sprite != NULL)
	{
		// create a bounding box based on the dimensions and position.
		SDL_Rect Bounds;
		Bounds.x = transform.position.x;
		Bounds.y = transform.position.y;
		Bounds.w = Dimensions.x;
		Bounds.h = Dimensions.y;

		// adds the sprite to the render queue to be processed and displayed on the screen later.
		SDL_RenderCopy(renderer, sprite, NULL, &Bounds);
	}

}

void GameObject2D::Update()
{

}

void GameObject2D::Destroy()
{

}