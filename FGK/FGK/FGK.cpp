#include <iostream>
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Mesh.h"
#include "Camera.h"
#include "Buffer.h"
#include "Triangle.h"

int main()
{
	int width = 264;
	int	height = 264;

	Mesh newMesh("untitled.obj");
	newMesh.GetVertices();
	newMesh.GetNormals();
	newMesh.GetTexcoords();
	newMesh.GetFaces();

	Vector3 position(0.0f, 0.0f, 0.0f);
	Vector3 target(0.0f, 0.0f, 0.0f);
	Vector3 vecUp(0.0f, 1.0f, 0.0f);
	float fov = 90.0f;
	float ratio = (float)width / height;
	float nearClip = 0.01f;
	float farClip = 10000.0f;

	bool isOrtographic = true;

	Camera mainCamera(position, target, vecUp, fov, ratio, nearClip, farClip, isOrtographic);
	
	Buffer buffer(width, height);
	buffer.ClearColor(0xFF00FFFF);

	Buffer depthBuffer(width, height);

	Triangle triangle({ 0.0f, 0.9f, -1.0f }, { 1.0f, 0.9f, 0.0f }, { 0.5f, -0.5f, 0.0f },
					  { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f }, buffer, depthBuffer);
	buffer.Save();
}
