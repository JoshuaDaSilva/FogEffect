#pragma once
struct Vec3
{
	float x, y, z;
};

struct Transform3D
{
	Vec3 position;
	Vec3 scale;
	Vec3 rotation;
};
