#pragma once
#include "Vector.h"
#include "Triangle.h"
#include <vector>
#include <string>
#include <iostream>

struct Face 
{
	std::vector<int> vertexIndices;
	void WriteCoordsToConsole() 
	{
		for (int i = 0; i < vertexIndices.size(); i++)
		{
			std::cout << vertexIndices[i] << ", ";
		}
	}
};

class Mesh
{
private:
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector2> texcoords;
	std::vector<Face> faces;
	std::vector<Face> faceTexCoords;
	std::vector<int> faceNormals;
	std::vector<Triangle> triangles;

public:
	Mesh(const std::string& filename);

	std::vector<Triangle> GetTriangles();

	void WriteVertices();
	void WriteNormals();
	void Texcoords();
	void WriteFaces();
	void WriteFaceNormals();
	void WriteTriangles();
};

