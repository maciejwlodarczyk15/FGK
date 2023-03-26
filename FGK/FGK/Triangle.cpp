#include "Triangle.h"

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 vn)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->vn = vn;
}

Vector3 Triangle::GetVn()
{
	return vn;
}

Vector3 Triangle::GetV1()
{
	return v1;
}

Vector3 Triangle::GetV2()
{
	return v2;
}

Vector3 Triangle::GetV3()
{
	return v3;
}
