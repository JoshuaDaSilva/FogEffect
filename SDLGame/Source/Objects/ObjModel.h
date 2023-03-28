#pragma once
#include "GameObject3D.h"
#include "../External/tinyObjLoader.h"

class ObjModel : public GameObject3D
{
public:
	ObjModel() {};
	~ObjModel() {};
	
	// used for any variables and data that needs to be setup on the object before we try to use it.
	void Init(string modelFile);

	// used to render the object to the screen
	virtual void Draw();

	// used to update processing on the object (in case it's moving or has some processing to compute)
	virtual void Update();

	// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
	virtual void Destroy();

protected:
	// this is used to process individual vertices for your model
	virtual void ProcessVertice(int shapeId, float vx, float vy, float vz, float r, float g, float b);

private:

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::material_t> materials;
	std::vector<tinyobj::shape_t> shapes;
};

