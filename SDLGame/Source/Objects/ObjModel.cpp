#include "ObjModel.h"
#include <iostream>
#include "..\EventHandler.h"

void ObjModel::Init(string modelFile)
{
	std::string warn;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelFile.c_str());
}

void ObjModel::Draw()
{
// Loop over shapes
	for (size_t s = 0; s < shapes.size(); s++) 
	{
		// Loop over faces(polygon)
		size_t index_offset = 0;

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) 
		{
			int fv = shapes[s].mesh.num_face_vertices[f];

			glBegin(GL_TRIANGLES);
			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++) {
				// access to vertex
				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
				tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
				tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
				tinyobj::real_t red = attrib.colors[3*idx.vertex_index+0];
				tinyobj::real_t green = attrib.colors[3*idx.vertex_index+1];
				tinyobj::real_t blue = attrib.colors[3*idx.vertex_index+2];
				ProcessVertice(s, vx, vy, vz, red, green, blue);

			}
			glEnd();
			index_offset += fv;
		}
	}

}

void ObjModel::ProcessVertice(int shapeId, float vx, float vy, float vz, float r, float g, float b)
{
	// overide this with specific changes to your model...
	glVertex3f(vx, vy, vz);
}

void ObjModel::Update()
{
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
}

void ObjModel::Destroy()
{
}