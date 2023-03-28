#include "GameObject3D.h"
#include "..\EventHandler.h"

GameObject3D::GameObject3D()
{
}


GameObject3D::~GameObject3D()
{
}

void GameObject3D::Update()
{
	if (iframes > 0)
	{
		iframes--;
	}
}

bool GameObject3D::CheckCollision(GameObject3D otherObj)
{
	Vec3 LocalPos = transform.position;
	Vec3 OtherPos = otherObj.transform.position;

	// perform a check for collision based on the other objects position and dimensions in addition to the local position and dimensions.
	// you can assume our objects positions are central to the object
	if (LocalPos.x - dimensions.x < OtherPos.x - otherObj.dimensions.x ||
		LocalPos.x + dimensions.x > OtherPos.x + otherObj.dimensions.x)
	{
		return true;
	}

	if (LocalPos.y - dimensions.y < OtherPos.y - otherObj.dimensions.y ||
		LocalPos.y + dimensions.y > OtherPos.y + otherObj.dimensions.y)
	{
		return true;

	}

	if( LocalPos.z - dimensions.z < OtherPos.z - otherObj.dimensions.z ||
		LocalPos.z + dimensions.z > OtherPos.z + otherObj.dimensions.z )
	{
		return true;
	}

	return false;
}
