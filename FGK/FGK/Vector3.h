#pragma once
#include "NTypes.h"

class Vector3
{
private:
	float3 coords;

public:
	Vector3(float3 coordinates);
	Vector3();

	float Length();

	Vector3 Add(Vector3 givenVector);
	Vector3 Substract(Vector3 givenVector);
	float Dot(Vector3 givenVector);
	Vector3 Cross(Vector3 givenVector);
	Vector3 Normalize();

	float AngleBetweenVectors(Vector3 givenVector);

	float3 GetCoords();
	void WriteCoordsToConsole();

	Vector3 operator+(Vector3 givenVector)
	{
		Vector3 newVector({ coords.x + givenVector.GetCoords().x, coords.y + givenVector.GetCoords().y , coords.z + givenVector.GetCoords().z });
		return newVector;
	}

	Vector3 operator-(Vector3 givenVector)
	{
		Vector3 newVector({coords.x - givenVector.GetCoords().x, coords.y - givenVector.GetCoords().y , coords.z - givenVector.GetCoords().z});
		return newVector;
	}

	Vector3 operator*(float number)
	{
		Vector3 newVector({ coords.x * number, coords.y * number, coords.z * number });
		return newVector;
	}
};

