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
				Face faceTex;
				int normal_index;

				while (iss >> type)
				{
					std::istringstream viss(type);
					std::string vertex_token;
					std::getline(viss, vertex_token, '/');
					int vertex_index = std::stoi(vertex_token) - 1;
					face.vertexIndices.push_back(vertex_index);

					std::string texCoord_token;
					std::getline(viss, texCoord_token, '/');
					int texCoord_index = std::stoi(texCoord_token) - 1;
					faceTex.vertexIndices.push_back(texCoord_index);

					std::string normal_token;
					std::getline(viss, normal_token, '/');
					normal_index = std::stoi(normal_token) - 1;
				}

				faceNormals.push_back(normal_index);
				faces.push_back(face);
				faceTexCoords.push_back(faceTex);

			}
		}
	}
	file.close();

	for (int i = 0; i < faces.size(); i++)
	{
		Vector3 v1 = vertices[faces[i].vertexIndices[0]];
		Vector3 v2 = vertices[faces[i].vertexIndices[1]];
		Vector3 v3 = vertices[faces[i].vertexIndices[2]];
		Vector3 vn = normals[faceNormals[i]];
		triangles.push_back(Triangle(v1, v2, v3, vn));
	}
}

std::vector<Triangle> Mesh::GetTriangles()
{
	return triangles;
}

void Mesh::WriteVertices()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		std::cout << "\nv: ";
		vertices[i].WriteCoordsToConsole();
	}
}

void Mesh::WriteNormals()
{
	for (int i = 0; i < normals.size(); i++)
	{
		std::cout << "\nvn: ";
		normals[i].WriteCoordsToConsole();
	}
}

void Mesh::Texcoords()
{
	for (int i = 0; i < texcoords.size(); i++)
	{
		std::cout << "\nvt: ";
		texcoords[i].WriteCoordsToConsole();
	}
}

void Mesh::WriteFaces()
{
	for (int i = 0; i < faces.size(); i++)
	{
		std::cout << "\nf: ";
		faces[i].WriteCoordsToConsole();
	}
}

void Mesh::WriteFaceNormals()
{
	for (int i = 0; i < faces.size(); i++)
	{
		std::cout << "\nfn: ";
		std::cout << faceNormals[i];
	}
}

void Mesh::WriteTriangles()
{
	for (int i = 0; i < triangles.size(); i++)
	{
		std::cout << "\nTriangle: v1: ";
		triangles[i].GetV1().WriteCoordsToConsole();
		std::cout << ", v2: ";
		triangles[i].GetV2().WriteCoordsToConsole();
		std::cout << ", v3: ";
		triangles[i].GetV3().WriteCoordsToConsole();
		std::cout << ", vn: ";
		triangles[i].GetVn().WriteCoordsToConsole();
		std::cout << "\n\n";
	}
}
