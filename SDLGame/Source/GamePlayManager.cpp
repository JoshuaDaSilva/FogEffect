#include "GamePlayManager.h"
#include <iostream>
#include "CameraManager.h"

GamePlayManager* GamePlayManager::instance = nullptr;


GamePlayManager::GamePlayManager()
{
}


GamePlayManager::~GamePlayManager()
{
}

void GamePlayManager::DisplaySplashScreen(SDL_Window* mainWindow, SDL_Renderer* mainRenderer)
{
	// this object is defined inside the GameObject2D file.
	GameObject2D SplashScreen;
	SplashScreen.Init("Data\\Art\\SplashScreen.bmp", mainRenderer);

	// Draw a black background
	SDL_SetRenderDrawColor(mainRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(mainRenderer);

	SwapSplash(mainWindow, mainRenderer, 1000, SplashScreen);
}

void GamePlayManager::SwapSplash(SDL_Window* mainWindow, SDL_Renderer* mainRenderer, Uint32 delay, GameObject2D screen)
{
	SDL_RenderClear(mainRenderer);
	screen.Draw(mainWindow, mainRenderer);

	// Update the screen!
	SDL_RenderPresent(mainRenderer);
	SDL_Delay(delay);
}


void GamePlayManager::InitGameplay()
{
	glEnable(GL_DEPTH_TEST);

	CameraManager::GetInstance()->SetupCamera();

	cubey.Init();
}


void GamePlayManager::Update()
{
	CameraManager::GetInstance()->Update();
	cubey.Update();
	cubey.Draw();
}