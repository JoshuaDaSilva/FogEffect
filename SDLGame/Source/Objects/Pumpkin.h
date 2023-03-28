#pragma once
#include "ObjModel.h"

class Pumpkin :	public ObjModel
{
public:
	Pumpkin();
	~Pumpkin();

	enum PUMPKIN_MODEL_SHAPES
	{
		CORE = 0,
		STEM,

		NUM_PUMPKIN_SHAPES
	};

	// this is used to process individual vertices for your model
	void ProcessVertice(int shapeId, float vx, float vy, float vz, float r, float g, float b);
	void Update();
	void Init(string modelFile);

private:

	GLfloat pumpkinColor[4] = { 0.8f, 0.5f, 0.3f, 1.0 };
	GLfloat stemColor[4] = { 0.3f, 0.9f, 0.7f, 1.0 };

};