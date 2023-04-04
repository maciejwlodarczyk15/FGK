#pragma once

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
	Vector3 Reflect(Vector3 normal);
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
	Vector3 operator*(Vector3 givenVector)
	{
		Vector3 newVector(x * givenVector.x, y * givenVector.y, z * givenVector.z);
		return newVector;
	}

	Vector3 operator*(float number)
	{
		Vector3 newVector({ x * number, y * number,z * number });
		return newVector;
	}

	Vector3 operator/(float number)
	{
		Vector3 newVector({ x / number, y / number, z / number });
		return newVector;
	}
	bool operator!=(Vector3 o)
	{
		if (x == o.x && y == o.y && z == o.z)
		{
			return false;
		}
		else
		{
			return true;
		}
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



class Vector4
{
public:
	float x, y, z, w;
	
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	void WriteCoordsToConsole();

	Vector4 operator*(float o) 
	{
		return Vector4(x * o, y * o, z * o, w * o);
	}
	Vector4 operator+(Vector4 v2)
	{
		return Vector4(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
	}
};
