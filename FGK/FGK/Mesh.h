#pragma once
#include "Vector3.h"
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

public:
	Mesh(const std::string& filename);

	void GetVertices();
	void GetNormals();
	void GetTexcoords();
	void GetFaces();
};

