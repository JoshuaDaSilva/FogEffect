#pragma once
// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"
#include "vmath.h"
#include "Math.h"

class CameraManager
{
public:
	static CameraManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new CameraManager();
		}
		return instance;
	}
	void SetupCamera();

	vmath::mat4 getBaseProjectionMatrix() { return proj_matrix; }
	vmath::mat4 getModifiedProjectionMatrix();

	void MoveCamera(int x, int y, int z);
	void RotateCamera(float x, float y, float z);
	void Rotate(int x, int y);

	Vec3 GetCamPosition() {	return CameraPosition;}

	void Update();

private:
	CameraManager();
	~CameraManager();


	Vec3 CameraPosition;
	Vec3 CameraRotation;
	vmath::mat4 proj_matrix;

	static CameraManager* instance;
};

