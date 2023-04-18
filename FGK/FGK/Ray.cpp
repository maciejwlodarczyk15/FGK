#include "Ray.h"
#include <iostream>

#define PLUS_ZERO 0.00001
#define MINUS_ZERO -0.0001

Ray::Ray(Vector3 point, Vector3 direct)
{
	origin = point;
	direction = direct;
}

Vector3 Ray::GetPosition()
{
    return origin;
}

Vector3 Ray::GetDirection()
{
    return direction;
}

bool Ray::intersectsSphere(Sphere sphere, Vector3& contactPoint)
{
	Vector3 oc = origin - sphere.GetCenter();

	float a = direction.Dot(direction);
	float b = oc.Dot(direction);
	float c = oc.Dot(oc) - sphere.GetRadius() * sphere.GetRadius();

	float discriminant = b * b - a * c;

    if (discriminant <= 0) {
        return false;
    }
    else {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < 0) {
            return false;
        }
        else {
            contactPoint = origin.Add(direction*temp);
            return true;
        }
    }
}

bool Ray::intersectPlane(Plane plane, Vector3& contactPoint)
{
    const float ndotD = plane.GetNormal().Dot(direction);

    if (ndotD == 0)
    {
        return false;
    }

    float t = plane.GetNormal().Dot(plane.GetPoint() - origin) / ndotD;

    if (t < 0) {
        return false;
    }
    
    contactPoint = origin + direction * t;
    return true;
}

bool Ray::intersectTriangle(Triangle triangle, Vector3& contactPoint)
{
    Plane trianglePlane(triangle.GetVn(), triangle.GetV1(), Intensity(0.0f ,0.0f ,0.0f));
    if (!this->intersectPlane(trianglePlane, contactPoint))
    {
        return false;
    }
    else
    {
        Vector3 fa, fb, fc;
        Vector3 x;

        fa = triangle.GetV1() - contactPoint;
        fb = triangle.GetV2() - contactPoint;
        fc = triangle.GetV3() - contactPoint;

        x = fa.Cross(fb);

        if (x.Dot(triangle.GetVn()) < MINUS_ZERO)
        {
            return false;
        }
        else
        {
            x = fb.Cross(fc);

            if (x.Dot(triangle.GetVn()) < MINUS_ZERO)
            {
                return false;
            }

            x = fc.Cross(fa);
            
            if (x.Dot(triangle.GetVn()) < MINUS_ZERO)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}
