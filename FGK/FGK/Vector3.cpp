#include "Vector3.h"
#include <iostream>
#include <math.h>

#define M_PI 3.14159265358979323846

// Default constructor
Vector3::Vector3()
{
	coords = { 0.0f, 0.0f, 0.0f };
}

Vector3::Vector3(float3 coordinates)
{
	coords = coordinates;
}

float Vector3::Length()
{
	return sqrt(coords.x * coords.x + coords.y * coords.y + coords.z * coords.z);
}

Vector3 Vector3::Add(Vector3 givenVector)
{
	Vector3 newVector({coords.x + givenVector.GetCoords().x, coords.y + givenVector.GetCoords().y, coords.z + givenVector.GetCoords().z});
	return newVector;
}

Vector3 Vector3::Substract(Vector3 givenVector)
{
	Vector3 newVector({coords.x - givenVector.GetCoords().x, coords.y - givenVector.GetCoords() .y, coords.z - givenVector.GetCoords().z});
	return newVector;
}

float Vector3::Dot(Vector3 givenVector)
{
	float result = coords.x * givenVector.GetCoords().x + coords.y * givenVector.GetCoords().y + coords.z * givenVector.GetCoords().z;
	return result;
}

Vector3 Vector3::Cross(Vector3 givenVector)
{
	Vector3 newVector({coords.y * givenVector.GetCoords().z - coords.z * givenVector.GetCoords().y,
					   coords.z * givenVector.GetCoords().x - coords.x * givenVector.GetCoords().z,
					   coords.x * givenVector.GetCoords().y - coords.y * givenVector.GetCoords().x});
	return newVector;
}

Vector3 Vector3::Normalize()
{
	float length = this->Length();
	if (length != 0)
	{
		Vector3 newVector({coords.x /= length, coords.y /= length, coords.z /= length });
		return newVector;
	}
	else 
	{
		return *this;
	}
}

float Vector3::AngleBetweenVectors(Vector3 givenVector)
{
	float dotProduct = this->Dot(givenVector);
	float length1 = this->Length();
	float length2 = givenVector.Length();
	float cosAlpha = (dotProduct) / (length1 * length2);
	float alpha = acos(cosAlpha);
	return alpha * 180.0f / M_PI;
}

float3 Vector3::GetCoords()
{
	return coords;
}

void Vector3::WriteCoordsToConsole()
{
	std::cout << "x: " << coords.x << ", y: " << coords.y << ", z: " << coords.z;
}
