#include "CameraManager.h"
#include "vmath.h" // used for matrix, vectors and other math functions
#include "EventHandler.h"

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600


CameraManager* CameraManager::instance = nullptr;

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::SetupCamera()
{
	CameraPosition.x = 0;
	CameraPosition.y = 0;
	CameraPosition.z = 0;
	// reset the rotations to 0 too.
	CameraRotation = CameraPosition;

	static const GLfloat one = 1.0f;

	// GLint x,	GLint y,	GLsizei width,	GLsizei height);
	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearBufferfv(GL_DEPTH, 0, &one);

	// Assign to a 4x4 matrix the projection or view of the world
	// similar to a camera system
	//        ________
	//      /|       /|
	//     / |    /   |
	//    /  |__/_____|
	//   /____/     /  
	//   |    |  / 
	//   |____|/
	//
	//								fovy,				aspect ratio,					near clipping, far clipping
	proj_matrix = vmath::perspective(50.0f,	(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,		1.0f,		20.0f);
}


vmath::mat4 CameraManager::getModifiedProjectionMatrix()
{ 
	vmath::mat4 newMat = proj_matrix * vmath::rotate(CameraRotation.x, CameraRotation.y, CameraRotation.z);
	newMat *= vmath::translate(CameraPosition.x, CameraPosition.y, CameraPosition.z);
	return newMat;
}


void CameraManager::MoveCamera(int x, int y, int z)
{
	CameraPosition.x += x;
	CameraPosition.y += y;
	CameraPosition.z += z;
}

void CameraManager::RotateCamera(float x, float y, float z)
{
	CameraRotation.x += x;
	CameraRotation.y += y;
	CameraRotation.z += z;
}

void CameraManager::Update()
{

	if (EventHandler::events[ControlsEvents::S_PRESSED])
	{
		CameraPosition.y += 0.01f;
	}

	if (EventHandler::events[ControlsEvents::W_PRESSED])
	{
		CameraPosition.y -= 0.01f;
	}

	if (EventHandler::events[ControlsEvents::A_PRESSED])
	{
		float yrotrad;
		yrotrad = (CameraRotation.y / 180 * 3.141592654f);
		CameraPosition.x += float(cos(yrotrad)) / 10.0f;
		CameraPosition.z += float(sin(yrotrad)) / 10.0f;
	}

	if (EventHandler::events[ControlsEvents::D_PRESSED])
	{
		float yrotrad;
		yrotrad = (CameraRotation.y / 180 * 3.141592654f);
		CameraPosition.x -= float(cos(yrotrad)) / 10.0f;
		CameraPosition.z -= float(sin(yrotrad)) / 10.0f;
		
	}
	
	if (EventHandler::events[ControlsEvents::Q_PRESSED])
	{

		float xrotrad, yrotrad;
		yrotrad = (CameraRotation.y / 180 * 3.141592654f);
		xrotrad = (CameraRotation.x / 180 * 3.141592654f);
		CameraPosition.x += float(sin(yrotrad)) / 10.0f;
		CameraPosition.z -= float(cos(yrotrad)) / 10.0f;
		

	}
	if (EventHandler::events[ControlsEvents::E_PRESSED])
	{
		float xrotrad, yrotrad;
		yrotrad = (CameraRotation.y / 180 * 3.141592654f);
		xrotrad = (CameraRotation.x / 180 * 3.141592654f);
		CameraPosition.x -= float(sin(yrotrad)) / 10.0f;
		CameraPosition.z += float(cos(yrotrad)) / 10.0f;
		//CamY += float(sin(xrotrad));
	}
	
}

void CameraManager::Rotate(int x, int y)
{
	float halfWidth = (WINDOW_WIDTH / 2);
	float halfHeight = (WINDOW_HEIGHT / 2);

	// window coordinates are 0-800, 0-600
	// we need to normalize the values from -1.0f -> 1.0f
	// this x and yrot are not backwards... sounds confusing but it's the axis you want to rotate around
	float yRot = (x - halfWidth) / halfWidth;
	float xRot = (y - halfHeight) / halfHeight;

	// we need a deadzone... an area where we don't move (basically the end 40% should only move the camera)
	if (fabs(yRot) < 0.60f)
	{
		yRot = 0.0f;
	}
	else
	{
		if (yRot < 0)
		{
			yRot = ((yRot + 0.6f) / 0.4f);
		}
		else
		{
			yRot = ((yRot - 0.6f) / 0.4f);
		}
		CameraRotation.y += yRot;
	}

}