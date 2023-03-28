#pragma once
#include "SDL.h"

// new OpenGL/GLEW headers:
#define GL3_PROTOTYPES 1
#include "glew.h"
#include "Math.h"


class ShaderManager
{
public:
	static ShaderManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new ShaderManager();
		}
		return instance;
	}

	void Init();

	void Startup();

	void LoadShaders(bool recompiled = false);

	void Render(GLuint texture, Vec3 position);

	void Update();

	void Shutdown();

	void LoadShaderFromFile(const char * shaderfile, GLenum type);
	void LoadVertices(static const GLfloat CubeVB[], int numVerts);
	void LoadUVs(static const GLfloat CubeVB[], int numUVs);
	void LoadNormals(static const GLfloat NormalsVB[], int numNormals);

	float color[3] = { 1.48, 0.13, 0.13 };

private:

	ShaderManager();
	~ShaderManager();

	void ProcessShaderFile(GLuint shader, char *shaderData, GLenum type);
	void FindUniformHandles();

	float m_density = 0.02;
	float m_gradient = 0.02;

	GLuint programObj;
	GLuint vao;

	GLint CamPosUniformHandle;
	GLint TextureUniformHandle;
	GLint ProjectionUniformHandle;
	GLint AmbientUniformHandle;
	GLint ModelViewUniformHandle;
	GLint SkyColorUniformHandle;
	GLint DensityUniformHandle;
	GLint GradientUniformHandle;

	GLuint verticesHandle;
	GLuint UVHandle;
	GLuint NormalsHandle;
	
	static ShaderManager* instance;
};

