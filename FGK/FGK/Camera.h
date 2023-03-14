#pragma once
#include "Vector.h"
#include "Matrix4x4.h"
class Camera
{
private:
	Vector3 position;
	Vector3 lookAt;
	Vector3 up;
	float fov;
	float aspectRatio;
	float nearClip;
	float farClip;
	bool isOrtho;

public:
	Camera(Vector3 pos, Vector3 target, Vector3 vecUp, float fov1, float ratio, float nClip, float fClip, bool isOrtho);
	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();
};

