#include "Mesh.h"
#include <fstream>
#include <sstream>

Mesh::Mesh(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		std::cout << "\nCould not open file";	
	}
	else 
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string type;
			iss >> type;

			if (type == "v")
			{
				float x, y, z;
				iss >> x >> y >> z;
				Vector3 position(Vector3(x, y, z));
				vertices.push_back(position);
			}
			if (type == "vn")
			{
				float x, y, z;
				iss >> x >> y >> z;
				Vector3 normal(Vector3(x, y, z));
				normals.push_back(normal);
			}
			else if (type == "vt")
			{
				float x, y;
				iss >> x >> y;
				Vector2 texcoord(Vector2( x, y ));
				texcoords.push_back(texcoord);
			}
			else if (type == "f")
			{
				Face face;

				while (iss >> type)
				{
					std::istringstream viss(type);
					std::string vertex_token;
					std::getline(viss, vertex_token, '/');
					int vertex_index = std::stoi(vertex_token) - 1;
					face.vertexIndices.push_back(vertex_index);
				}

				faces.push_back(face);
			}
		}
	}
	file.close();
}

void Mesh::GetVertices()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		std::cout << "\nv: ";
		vertices[i].WriteCoordsToConsole();
	}
}

void Mesh::GetNormals()
{
	for (int i = 0; i < normals.size(); i++)
	{
		std::cout << "\nvn: ";
		normals[i].WriteCoordsToConsole();
	}
}

void Mesh::GetTexcoords()
{
	for (int i = 0; i < texcoords.size(); i++)
	{
		std::cout << "\nvt: ";
		texcoords[i].WriteCoordsToConsole();
	}
}

void Mesh::GetFaces()
{
	for (int i = 0; i < faces.size(); i++)
	{
		std::cout << "\nf: ";
		faces[i].WriteCoordsToConsole();
	}
}
