#include "ShaderManager.h"
#include <cstdio>
#include <iostream>
#include "Utils.h"
#include "vmath.h"
#include "CameraManager.h"
#include "EventHandler.h"

using namespace std;

ShaderManager* ShaderManager::instance = nullptr;

#define LOG_COMPILE_SHADERS 1

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glewExperimental = GL_TRUE;
}

// function to call post Init
void ShaderManager::Startup()
{
	programObj = glCreateProgram();
}

void ShaderManager::LoadVertices(static const GLfloat CubeVB[], int numVerts)
{
	glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
	glBufferData(GL_ARRAY_BUFFER, numVerts, CubeVB, GL_STATIC_DRAW);
}

void ShaderManager::LoadUVs(static const GLfloat uvVB[], int numUVs)
{
	glBindBuffer(GL_ARRAY_BUFFER, UVHandle);
	glBufferData(GL_ARRAY_BUFFER, numUVs, uvVB, GL_STATIC_DRAW);
}

void ShaderManager::LoadNormals(static const GLfloat NormalsVB[], int numNormals)
{
	glBindBuffer(GL_ARRAY_BUFFER, NormalsHandle);
	glBufferData(GL_ARRAY_BUFFER, numNormals, NormalsVB, GL_STATIC_DRAW);
}

void ShaderManager::FindUniformHandles()
{
	TextureUniformHandle = glGetUniformLocation(programObj, "texture0");// Get the initial matrices references from the program.

	ModelViewUniformHandle = glGetUniformLocation(programObj, "mv_matrix");

	ProjectionUniformHandle = glGetUniformLocation(programObj, "proj_matrix");

	AmbientUniformHandle = glGetUniformLocation(programObj, "ambientLight");

	CamPosUniformHandle = glGetUniformLocation(programObj, "CamPos");

	SkyColorUniformHandle = glGetUniformLocation(programObj, "SkyColor");

	DensityUniformHandle = glGetUniformLocation(programObj, "density");

	GradientUniformHandle = glGetUniformLocation(programObj, "gradient");
}

void ShaderManager::LoadShaderFromFile(const char * shaderfile, GLenum type)
{
	GLuint shaderObj = 0;
	FILE * filePtr;
	
#ifdef LOG_COMPILE_SHADERS
	string newStr = "Source\\Shaders\\glslangValidator.exe ";
	newStr.append(shaderfile);
	cout << newStr.c_str();
	system(newStr.c_str());
#endif

	if (fopen_s(&filePtr, shaderfile, "rb"))
	{
		cout << "error opening shader file: " << shaderfile << endl;
		return;
	}

	fseek(filePtr, 0, SEEK_END);
	int size = ftell(filePtr);
	fseek(filePtr, 0, SEEK_SET);

	char *data = new char[size + 1];

	if (!data)
	{
		cout << "No Data inside shader file: " << shaderfile << endl;
		return;
	}

	fread(data, 1, size, filePtr);
	data[size] = 0;
	fclose(filePtr);

	ProcessShaderFile(shaderObj, data, type);

	delete[] data;
}

void ShaderManager::ProcessShaderFile(GLuint shader, char *shaderData, GLenum type)
{

	shader = glCreateShader(type);

	if (!shader)
	{
		cout << "error creating shader: " << shader << endl;
		return;
	}

	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);
	glAttachShader(programObj, shader);
	glDeleteShader(shader);
}

void ShaderManager::LoadShaders(bool recompiled)
{
	LoadShaderFromFile("Source\\Shaders\\Vert.vert" , GL_VERTEX_SHADER);
	LoadShaderFromFile("Source\\Shaders\\Frag.frag" , GL_FRAGMENT_SHADER);

	glLinkProgram(programObj);

	GLint success = GL_FALSE;
	glValidateProgram(programObj);
	glGetProgramiv(programObj, GL_VALIDATE_STATUS, &success);

	if (success == GL_FALSE)
	{
		cout << "ERROR LINKING!!!!\n\n \t check that your out variables match your in variables" << endl;
	}

	if (!recompiled)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &verticesHandle);
		glGenBuffers(1, &UVHandle);
		glGenBuffers(1, &NormalsHandle);
	}

	FindUniformHandles();
}

void ShaderManager::Render(GLuint texture, Vec3 position)
{
	glUseProgram(programObj);

	//pass in the vertices for our cube
	const int VERTS_ARTTRIB_ID = 0;
	const int UV_ARTTRIB_ID = 1;
	const int NORMALS_ARTTRIB_ID = 2;

	glEnableVertexAttribArray(VERTS_ARTTRIB_ID);
	glBindBuffer(GL_ARRAY_BUFFER, verticesHandle);
	glVertexAttribPointer(VERTS_ARTTRIB_ID, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);

	glEnableVertexAttribArray(UV_ARTTRIB_ID);
	glBindBuffer(GL_ARRAY_BUFFER, UVHandle);
	glVertexAttribPointer(UV_ARTTRIB_ID, 2, GL_FLOAT, GL_TRUE, 0, (void*)0);

	glEnableVertexAttribArray(NORMALS_ARTTRIB_ID);
	glBindBuffer(GL_ARRAY_BUFFER, NormalsHandle);
	glVertexAttribPointer(NORMALS_ARTTRIB_ID, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);

	// pass our data to openGL to store for the shaders use.
	glUniform1i(TextureUniformHandle, texture);

	// pass our data to openGL to store for the shaders use.
	float CamPos[3] = { CameraManager::GetInstance()->GetCamPosition().x, CameraManager::GetInstance()->GetCamPosition().y, CameraManager::GetInstance()->GetCamPosition().z };
	glUniform3fv(CamPosUniformHandle, 1, &CamPos[0]);

	vmath::mat4 proj_matrix = CameraManager::GetInstance()->getModifiedProjectionMatrix();
	glUniformMatrix4fv(ProjectionUniformHandle, 1, GL_FALSE, proj_matrix);

	vmath::mat4 mv_matrix = vmath::translate(position.x, position.y, position.z);
	glUniformMatrix4fv(ModelViewUniformHandle, 1, GL_FALSE, mv_matrix);

	float LightVals[3] = { 0.6f, 0.6f, 0.6f };
	glUniform3fv(AmbientUniformHandle, 1, &LightVals[0]);

	glUniform3f(SkyColorUniformHandle, color[0], color[1], color[2]);

	glUniform1f(GradientUniformHandle, m_gradient);
	glUniform1f(DensityUniformHandle, m_density);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 12 * 3, 10*10*3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void ShaderManager::Update()
{
	if (EventHandler::events[ControlsEvents::R_PRESSED])
	{
		glDeleteProgram(programObj);
		programObj = glCreateProgram();
		LoadShaders(true);
	}

	if (EventHandler::events[ControlsEvents::K_PRESSED])
	{
		color[0] += 0.2;
		color[1] += 0.1;
		color[2] += 0.05;
	}

	if (EventHandler::events[ControlsEvents::J_PRESSED])
	{
		color[0] -= 0.3;
		color[1] -= 0.7;
		color[2] -= 0.1;
	}

	if (EventHandler::events[ControlsEvents::O_PRESSED])
	{
		m_density += 0.02;
	}

	if (EventHandler::events[ControlsEvents::P_PRESSED])
	{
		m_density -= 0.02;
	}

	if (EventHandler::events[ControlsEvents::U_PRESSED])
	{
		m_gradient += 0.02;
	}

	if (EventHandler::events[ControlsEvents::I_PRESSED])
	{
		m_gradient -= 0.02;
	}

}

void ShaderManager::Shutdown()
{
	glDeleteProgram(programObj);
	glDeleteVertexArrays(1, &vao);
}