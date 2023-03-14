#pragma once
#include "Buffer.h"
#include "Vector.h"

class Triangle
{
private:
	Buffer mainBuffer;
	Buffer depthBuffer;
	Vector3 v1, v2, v3; // Vertices
	Vector4 c1, c2, c3; // Colors

public:
	Triangle(Vector3 vert1, Vector3 vert2, Vector3 vert3, Vector4 color1, Vector4 color2, Vector4 color3, Buffer mBuffer, Buffer dBuffer);
};

