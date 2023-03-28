#include "Wall.h"

Box::Box()
{
}

Box::~Box()
{
}
void Box::Init(float size)
{
	float vertex[90] = {
		//back
		size, size, -size,
		-size, size, -size,
		-size, -size, -size,

		-size, -size, -size,
		size, -size, -size,
		size, size, -size,

		//front
		//size, size, size,
		//-size, size, size,
		//-size, -size, size,

		//-size, -size, size,
		//size, -size, size,
		//size, size, size,


		//right
		size, size, size,
		size, size, -size,
		size, -size, -size,

		size, -size, -size,
		size, -size, size,
		size, size, size,

		//left
		-size, -size, -size,
		-size, size, -size,
		-size, size, size,

		-size, size, size,
		-size, -size, size,
		-size, -size, -size,


		//bottom
		size, -size, size,
		size, -size, -size,
		-size, -size, -size,

		-size, -size, -size,
		-size, -size, size,
		size, -size, size,

		//top

		size, size, -size,
		size, size, size,
		-size, size, -size,

		size, size, size,
		-size, size, size,
		-size, size, -size,
	};

	// generate a handle or name
	glGenBuffers(1, &bufferHandle);

	// bind the buffer as the active buffer for OpenGL to modify
	glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);

	// insert the data from the data array into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);

	transform.position.x = 0.0f;
	transform.position.y = 0.0f;
	transform.position.z = -20.0f;

	dimensions.x = size;
	dimensions.y = size;
	dimensions.z = size;
}

// used to render the object to the screen
void Box::Draw()
{

	GLfloat wallColor[4] = { 0.8f, 0.25f, 0.25f, 1.0 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, wallColor);
	glColor3f(0.8f, 0.25f, 0.25f);

	glBindBuffer(GL_ARRAY_BUFFER, bufferHandle);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, 90 / 3);
	glDisableClientState(GL_VERTEX_ARRAY);
}

// used to update processing on the object (in case it's moving or has some processing to compute)
void Box::Update()
{
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
}

// when the object is destroyed to ensure any memory allocated during it's lifetime is cleaned up.
void Box::Destroy()
{
}