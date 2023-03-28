#include "Cube.h"
#include "..\ShaderManager.h"
#include "..\Utils.h"
#include "..\EventHandler.h"

Cube::Cube()
{
}


Cube::~Cube()
{
}

void Cube::Init()
{
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	velocity.z = 0.0f;

	transform.position.z = -2;
	transform.position.y = -0.75;
	transform.position.x = -1.5;

	dimensions.x = 5.0;	// width
	dimensions.y = 5.0;	// height
	dimensions.z = 5.0;	// length

	static const GLfloat CubeVB[] =
	{
		-0.25f, -0.25f, -0.25f, //back bottom/left
		-0.25f,  0.25f, -0.25f,
		0.25f, -0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,
		-0.25f,  0.25f, -0.25f, //back top/right
		0.25f,  0.25f, -0.25f,

		0.25f, -0.25f, -0.25f,// right side back / bottom
		0.25f,  0.25f, -0.25f,
		0.25f, -0.25f,  0.25f,

		0.25f, -0.25f,  0.25f,
		0.25f,  0.25f, -0.25f, // right side front / top
		0.25f,  0.25f,  0.25f,

		0.25f, -0.25f,  0.25f, // front - bottom right
		0.25f,  0.25f,  0.25f,
		-0.25f, -0.25f,  0.25f,

		-0.25f, -0.25f,  0.25f,
		0.25f,  0.25f,  0.25f, // front - left top
		-0.25f,  0.25f,  0.25f,

		-0.25f, -0.25f,  0.25f, // left side - front bottom
		-0.25f,  0.25f,  0.25f,
		-0.25f, -0.25f, -0.25f,

		-0.25f, -0.25f, -0.25f,
		-0.25f,  0.25f,  0.25f, // left side - back top
		-0.25f,  0.25f, -0.25f,

		0.25f,  0.25f, -0.25f,
		-0.25f,  0.25f, -0.25f, // top back right
		0.25f,  0.25f, 0.25f,

		-0.25f,  0.25f, 0.25f,
		0.25f,  0.25f, 0.25f, // top  front left
		-0.25f,  0.25f, -0.25f,

		-0.25f,  -0.25f, -0.25f, // bottom back right
		0.25f,  -0.25f, -0.25f,
		0.25f,  -0.25f, 0.25f,

		0.25f,  -0.25f, 0.25f, // bottom front left
		-0.25f,  -0.25f, 0.25f,
		-0.25f,  -0.25f, -0.25f,
	};

	static const GLfloat uvVB[] = {
		0.33f, 0.66f, // front - bottom right
		0.33f, 1.00f,
		0.00f, 0.66f,

		0.00f, 0.66f, // front - left top
		0.33f, 1.00f,
		0.00f, 1.00f,

		0.33f, 1.00f,
		0.33f, 0.66f, // right side back / bottom 2
		0.66f, 1.00f,

		0.66f, 1.00f,
		0.33f, 0.66f,
		0.66f, 0.66f, // right side front / top 2

		1.00f, 1.00f, // front - bottom right
		1.00f, 0.66f,
		0.66f, 1.00f,

		0.66f, 1.00f, // front - left top
		1.00f, 0.66f,
		0.66f, 0.66f,

		0.00f, 0.33f, // left side - front bottom
		0.33f, 0.33f,
		0.00f, 0.66f,

		0.00f, 0.66f, // left side - back top
		0.33f, 0.33f,
		0.33f, 0.66f,

		0.66f, 0.66f,
		0.33f, 0.66f, //top
		0.66f, 0.33f,

		0.33f, 0.33f,
		0.66f, 0.33f,
		0.33f, 0.66f,


		0.66f, 0.66f, //bottom
		0.66f, 0.33f,
		1.00f, 0.33f,

		1.00f, 0.33f, //bottom
		1.00f, 0.66f,
		0.66f, 0.66f,
	};

	static const GLfloat normalsVB[] =
	{
		0.0f, 0.0f, -0.25f, //back bottom/left
		0.0f, 0.0f, -0.25f, //back bottom/left
		0.0f, 0.0f, -0.25f, //back bottom/left

		0.0f, 0.0f, -0.25f, //back top/right
		0.0f, 0.0f, -0.25f, //back top/right
		0.0f, 0.0f, -0.25f, //back top/right

		0.25f, 0.0f, 0.0f, // right side back / bottom
		0.25f, 0.0f, 0.0f, // right side back / bottom
		0.25f, 0.0f, 0.0f, // right side back / bottom

		0.25f, 0.0f, 0.0f, // right side front / top
		0.25f, 0.0f, 0.0f, // right side front / top
		0.25f, 0.0f, 0.0f, // right side front / top

		0.0f, 0.0f, 0.25f, // front - bottom right
		0.0f, 0.0f, 0.25f, // front - bottom right
		0.0f, 0.0f, 0.25f, // front - bottom right

		0.0f, 0.0f,  0.25f, // front - left top
		0.0f, 0.0f,  0.25f, // front - left top
		0.0f, 0.0f,  0.25f, // front - left top

		-0.25f, 0.0f, 0.0f, // left side - front bottom
		-0.25f, 0.0f, 0.0f, // left side - front bottom
		-0.25f, 0.0f, 0.0f, // left side - front bottom

		-0.25f, 0.0f, 0.0f, // left side - back top
		-0.25f, 0.0f, 0.0f, // left side - back top
		-0.25f, 0.0f, 0.0f, // left side - back top

		0.0f,  0.25f, 0.0f, // top back right 5
		0.0f,  0.25f, 0.0f, // top back right 5
		0.0f,  0.25f, 0.0f, // top back right 5

		0.0f,  0.25f, 0.0f, // top  front left 5
		0.0f,  0.25f, 0.0f, // top  front left 5
		0.0f,  0.25f, 0.0f, // top  front left 5

		0.0f, -0.25f, 0.0f, // bottom back right 6
		0.0f, -0.25f, 0.0f, // bottom back right 6
		0.0f, -0.25f, 0.0f, // bottom back right 6

		0.0f, -0.25f, 0.0f, // bottom front left 6
		0.0f, -0.25f, 0.0f, // bottom front left 6
		0.0f, -0.25f, 0.0f, // bottom front left 6
	};

	ShaderManager::GetInstance()->LoadVertices(&CubeVB[0], sizeof(CubeVB));
	ShaderManager::GetInstance()->LoadUVs(&uvVB[0], sizeof(uvVB));
	ShaderManager::GetInstance()->LoadNormals(&normalsVB[0], sizeof(normalsVB));
	LoadTexture();
}

void Cube::LoadTexture()
{
	// create a handle for the texture so openGL has an area allocated to manage all our binary image data.
	glGenTextures(1, &Textures[0]);

	// now tell OpenGL this is the texture we are currently using for all subsequent texture calls.
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Textures[0]);

	unsigned int width, height;
	unsigned char* imgData = Utils::loadBMP("Data\\Art\\grass.bmp", width, height);

	// load our texture data up here
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, imgData);

	// configure mipmapping levels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);
}

void Cube::Draw()
{
	ShaderManager::GetInstance()->Render(Textures[0], transform.position);
}

void Cube::Update()
{
}