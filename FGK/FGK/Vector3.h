#pragma once
#include "NTypes.h"

class Vector3
{
private:
	float3 coords;

public:
	Vector3(float3 coordinates);

	float Length();

	Vector3 Add(Vector3 givenVector);
	float Dot(Vector3 givenVector);
	Vector3 Cross(Vector3 givenVector);
	Vector3 Normalize();

	float AngleBetweenVectors(Vector3 givenVector);

	float3 GetCoords();
	void WriteCoordsToConsole();
};

