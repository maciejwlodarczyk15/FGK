#include <iostream>
#include "Vector3.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Mesh.h"

int main()
{
	Mesh newMesh("untitled.obj");
	newMesh.GetVertices();
	newMesh.GetNormals();
	newMesh.GetTexcoords();
	newMesh.GetFaces();
}
