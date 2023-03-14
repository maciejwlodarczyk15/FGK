#include "Ray.h"
#include <iostream>

Ray::Ray(Vector3 point, Vector3 direct)
{
	origin = point;
	direction = direct;
}

bool Ray::intersectsSphere(Sphere sphere, Vector3& contactPoint)
{
	Vector3 oc = origin - sphere.GetCenter();

	float a = direction.Dot(direction);
	float b = oc.Dot(direction);
	float c = oc.Dot(oc) - sphere.GetRadius() * sphere.GetRadius();

	float discriminant = b * b - a * c;

    if (discriminant < 0) {
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