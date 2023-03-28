#pragma once

#include "GameObject3D.h"

class Box : public GameObject3D
{
public:
	Box();
	~Box();

	// used for any variables and data that needs to be setup on the object before we try to use it.
	void Init(float size);

	// used to render the object to the screen
	virtual void Draw();

	// used to update processing on the object (in case it's moving or has some processing to compute)
	virtual void Update();

	// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
	virtual void Destroy();

private:
	
};

