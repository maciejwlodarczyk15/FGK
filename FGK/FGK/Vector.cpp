#include "Vector.h"
#include <iostream>
#include <math.h>

#define M_PI 3.14159265358979323846

// Default constructor
float Vector3::Length()
{
	return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::Add(Vector3 givenVector)
{
	Vector3 newVector({x + givenVector.x, y + givenVector.y, z + givenVector.z});
	return newVector;
}

Vector3 Vector3::Substract(Vector3 givenVector)
{
	Vector3 newVector({x - givenVector.x, y - givenVector.y, z - givenVector.z});
	return newVector;
}

float Vector3::Dot(Vector3 givenVector)
{
	float result = x * givenVector.x + y * givenVector.y + z * givenVector.z;
	return result;
}

Vector3 Vector3::Cross(Vector3 givenVector)
{
	Vector3 newVector({y * givenVector.z - z * givenVector.y,
					   z * givenVector.x - x * givenVector.z,
					   x * givenVector.y - y * givenVector.x});
	return newVector;
}

Vector3 Vector3::Normalize()
{
	float length = this->Length();
	if (length != 0)
	{
		Vector3 newVector({x /= length, y /= length, z /= length });
		return newVector;
	}
	else 
	{
		return *this;
	}
}

Vector3 Vector3::Reflect(Vector3 normal)
{
	return *this - normal * (this->Dot(normal) * 2.0f);
}

Vector3 Vector3::Refract(Vector3 normal, Vector3 incident, float n1, float n2)
{
	float eta = n1 / n2;
	float cosThetaI = normal.Dot(incident);
	float sin2ThetaI = std::max(float(0.0f), float(1 - cosThetaI * cosThetaI));
	float sin2ThetaT = eta * eta * sin2ThetaI;
	
	// Handle total internal reflection for transmission
	if (sin2ThetaT >= 1) return Vector3(0.0f,0.0f,0.0f);
	float cosThetaT = std::sqrt(1 - sin2ThetaT);
	return incident * (-1) * eta + normal * (eta * cosThetaI - cosThetaT);
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

void Vector3::WriteCoordsToConsole()
{
	std::cout << "(x: " << x << ", y: " << y << ", z: " << z << ")";
}

/*
		VECTOR2
*/

void Vector2::WriteCoordsToConsole()
{
	std::cout << "(x: " << x << ", y: " << y << ")";
}

/*
		VECTOR4
*/

void Vector4::WriteCoordsToConsole()
{
	std::cout << "(x: " << x << ", y: " << y << ", z: " <<  z  << ", w: " << w << ")";
}
