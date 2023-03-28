#pragma once

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

class LightManager
{
public:
	static LightManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new LightManager();
		}
		return instance;
	}

	void SetupSimpleLighting();
	void ApplyLighting();

private:

	LightManager();
	~LightManager();

	GLfloat lightColor[4] = { 0.6f, 0.7f, 0.8f, 1.0f };

	static LightManager* instance;
};

