#pragma once
#include "GameObject3D.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"

class Cube : public GameObject3D
{
public:
	Cube();
	~Cube();

	// used for any variables and data that needs to be setup on the object before we try to use it.
	virtual void Init();

	// used to render the object to the screen
	virtual void Draw();

	// used to update processing on the object (in case it's moving or has some processing to compute)
	virtual void Update();

	// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
	virtual void Destroy() {};

	void LoadTexture();

private:

	GLuint Textures[2];
};

