#pragma once
class Matrix4x4
{
private:
	float m[4][4];

public:
	Matrix4x4();

	Matrix4x4(float m00, float m01, float m02, float m03,
			  float m10, float m11, float m12, float m13,
			  float m20, float m21, float m22, float m23,
			  float m30, float m31, float m32, float m33);

	float& operator()(int row, int col)
	{
		return m[row][col];
	}

	Matrix4x4 operator*(Matrix4x4 m2)
	{
		Matrix4x4 result;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result(i, j) = m[i][0] * m2(0, j)
							 + m[i][1] * m2(1, j)
						     + m[i][2] * m2(2, j)
							 + m[i][3] * m2(3, j);
			}
		}

		return result;
	}

	Matrix4x4 Indentity();
};

