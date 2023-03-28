#pragma once

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"
#include "SDL.h"

// processing events
#include "EventHandler.h"
#include "LightManager.h"

// creating a basic gameobject
#include "Objects\GameObject2D.h"
#include "Objects\GameObject3D.h"

#include "Objects\Pumpkin.h"
#include "Objects\Wall.h"
#include "Objects\Cube.h"

class GamePlayManager
{
public:
	static GamePlayManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GamePlayManager();
		}
		return instance;
	}

	void InitGameplay();
	void DisplaySplashScreen(SDL_Window* mainWindow, SDL_Renderer* mainRenderer);
	void Update();

private:

	void SwapSplash(SDL_Window* mainWindow, SDL_Renderer* mainRenderer, Uint32 delay, GameObject2D screen);

	GamePlayManager();
	~GamePlayManager();

	Pumpkin pumpkin;
	Box walls;
	Cube cubey;

	static GamePlayManager* instance;
};

