#pragma once
#include "NTypes.h"

class Vector3
{
public:
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float x, float y, float z): x(x), y(y), z(z) {}

	float Length();

	Vector3 Add(Vector3 givenVector);
	Vector3 Substract(Vector3 givenVector);
	float Dot(Vector3 givenVector);
	Vector3 Cross(Vector3 givenVector);
	Vector3 Normalize();

	float AngleBetweenVectors(Vector3 givenVector);

	void WriteCoordsToConsole();

	Vector3 operator+(Vector3 givenVector)
	{
		Vector3 newVector({ x + givenVector.x, y + givenVector.y , z + givenVector.z });
		return newVector;
	}

	Vector3 operator-(Vector3 givenVector)
	{
		Vector3 newVector({ x - givenVector.x, y - givenVector.y , z - givenVector.z});
		return newVector;
	}

	Vector3 operator*(float number)
	{
		Vector3 newVector({ x * number, y * number,z * number });
		return newVector;
	}
};

class Vector2
{
public:
	float x, y;

	Vector2(): x(0.0f), y(0.0f) {}
	Vector2(float x, float y): x(x), y(y) {}

	void WriteCoordsToConsole();
};
