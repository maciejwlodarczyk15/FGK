#include "Camera.h"
#include <cmath>
#define M_PI 3.14159265358979323846

Camera::Camera(Vector3 pos, Vector3 target, Vector3 vecUp, float fov1, float ratio, float nClip, float fClip, bool isOrtho)
{
    position = pos;
    lookAt = target;
    up = vecUp;
    fov = fov1;
    aspectRatio = ratio;
    nearClip = nClip;
    farClip = fClip;
    this->isOrtho = isOrtho;
}

Matrix4x4 Camera::GetViewMatrix()
{
    Vector3 zAxis = (lookAt - position).Normalize();
    Vector3 xAxis = up.Cross(zAxis).Normalize();
    Vector3 yAxis = zAxis.Cross(xAxis);
    
    Matrix4x4 result;
    result.Indentity();
    result(0, 0) = xAxis.x;
    result(0, 1) = xAxis.y;
    result(0, 2) = xAxis.z;
    result(0, 3) = -xAxis.Dot(position);
    result(1, 0) = yAxis.x;
    result(1, 1) = yAxis.y;
    result(1, 2) = yAxis.z;
    result(1, 3) = -yAxis.Dot(position);
    result(2, 0) = zAxis.x;
    result(2, 1) = zAxis.y;
    result(2, 2) = zAxis.z;
    result(2, 3) = zAxis.Dot(position);

    return result;
}

Matrix4x4 Camera::GetProjectionMatrix()
{
    Matrix4x4 result;
    result.Indentity();

    if (isOrtho)
    {

    }
    else
    {
        float f = 1.0f / tan(fov * 0.5f * (float)M_PI / 180.0f);
        result(0, 0) = f / aspectRatio;
        result(1, 1) = f;
        result(2, 2) = (farClip + nearClip) / (nearClip - farClip);
        result(2, 3) = -1.0f;
        result(3, 2) = (2 * farClip * nearClip) / (nearClip - farClip);
    }
    return result;
}
