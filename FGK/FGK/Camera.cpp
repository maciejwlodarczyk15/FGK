﻿#include "Camera.h"
#include "Ray.h"
#include <iostream>
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

Camera::Camera(Vector3 camPos, Vector3 camTarget, Vector3 camUp, float fovDegree, float nPlane, float fPlane, int maxDepth,
               Image img, Intensity objectColor, Intensity backgroundColor, 
               std::vector<Sphere> spheres, std::vector<Mesh> meshes, std::vector<PointLight> lights, std::vector<Plane> planes, bool isOrtographic)
{
    cameraPosition = camPos;
    cameraTarget = camTarget;
    cameraVecUp = camUp;

    this->img = img;
    screenWidth = img.GetWidth();
    screenHeight = img.GetHeight();
    aspectRatio = (float)screenWidth / (float)screenHeight;

    fov = tan(fovDegree * M_PI / 360.0f);
    nearPlane = nPlane;
    farPlane = fPlane;
    this->isOrtographic = isOrtographic;

    this->objectColor = objectColor;
    this->backgroundColor = backgroundColor;
    this->spheres = spheres;
    this->maxDepth = maxDepth;
    this->meshes = meshes;
    this->lights = lights;
    this->planes = planes;
}

Intensity Camera::Phong(float px, float py)
{
    // Pixel/Camera settings
    px *= aspectRatio * tan(fov / 2.0f);
    py *= tan(fov / 2.0f);
    Vector3 rayDir(px, py, -1.0f);
    rayDir.Normalize();

    if (!isOrtographic)
    {
        Vector3 cameraDir = (cameraTarget - cameraPosition).Normalize();
        Vector3 cameraVectorRight = cameraVecUp.Cross(cameraDir).Normalize();
        Vector3 cameraUpNew = cameraDir.Cross(cameraVectorRight).Normalize();
        rayDir = (cameraVectorRight * px + cameraUpNew * py + cameraDir / fov).Normalize();
    }

    Ray ray(cameraPosition, rayDir);
    if (isOrtographic)
    {
        Vector3 rayOrigin = cameraPosition + Vector3(1, 0, 0) * px + Vector3(0, 1, 0) * py;
        ray = Ray(rayOrigin, rayDir);
    }

    // Checking if object hit, if hit drawColor = true
    Sphere hitSphere;
    Plane hitPlane;
    bool isSphere = false;

    // Check whether to draw object or background
    Vector3 objectContactPoint;
    bool drawColor = false;
    for (int i = 0; i < spheres.size(); i++)
    {
        if (ray.intersectsSphere(spheres[i], objectContactPoint))
        {
            drawColor = true;
            hitSphere = spheres[i];
            isSphere = true;
            break;
        }
    }
    if (!isSphere)
    {
        for (int i = 0; i < planes.size(); i++)
        {
            if (ray.intersectPlane(planes[i], objectContactPoint))
            {
                drawColor = true;
                hitPlane = planes[i];
                break;
            }
        }
    }
    
    if (drawColor)
    {
        // Ambient light
        Intensity ambientLight = Intensity(0.3f, 0.3f, 0.3f);
        Intensity finalColor;

        if (!isSphere)
        {
            finalColor = ambientLight * hitPlane.GetColor();
        }
        if (isSphere)
        {
            finalColor = ambientLight * objectColor;
        }

        bool isBlocked = false;
        Vector3 blockContactPoint;
        Vector3 normal;
        
        // Normal vector at the hit point
        if (isSphere)
        {
            normal = (objectContactPoint - hitSphere.GetCenter()).Normalize();
        }
        else 
        {
            // Plane has same normal on whole area
            normal = hitPlane.GetNormal();
        }

        // Iterating through all lights
        for (int i = 0; i < lights.size(); i++)
        {
            // Check if blocked, ray -> Position: contact point + offset in direction of light, Direction: from contactPoint to light
            isBlocked = false;
            Ray chaseTheLight = Ray(objectContactPoint + (lights[i].GetPosition() - objectContactPoint).Normalize() * 0.01, (lights[i].GetPosition() - objectContactPoint).Normalize());

            // If object is a sphere
            if (isSphere)
            {
                // Iterate through all spheres
                for (int j = 0; j < spheres.size(); j++)
                {
                    // check if hit any other sphere
                    if (chaseTheLight.intersectsSphere(spheres[i], blockContactPoint))
                    {
                        // Check if distance between original and new is less than original - light = object between
                        if ((objectContactPoint - blockContactPoint).Length() < (objectContactPoint - lights[i].GetPosition()).Length())
                        {
                            isBlocked = true;
                            break;
                        }
                    }
                }
                // Do same for all planes
                for (int j = 0; j < planes.size(); j++)
                {
                    if (chaseTheLight.intersectPlane(planes[j], blockContactPoint))
                    {
                        if ((objectContactPoint - blockContactPoint).Length() < (objectContactPoint - lights[i].GetPosition()).Length())
                        {
                            isBlocked = true;
                            break;
                        }
                    }
                }
            }
            // Same with planes
            if (!isSphere)
            {
                for (int j = 0; j < spheres.size(); j++)
                {
                    if (chaseTheLight.intersectsSphere(spheres[i], blockContactPoint))
                    {
                        // Check if distance between original and new is less than original - light = object between
                        if ((objectContactPoint - blockContactPoint).Length() < (objectContactPoint - lights[i].GetPosition()).Length())
                        {
                            isBlocked = true;
                            break;
                        }
                    }
                }
                for (int j = 0; j < planes.size(); j++)
                {
                    if (chaseTheLight.intersectPlane(planes[j], blockContactPoint))
                    {
                        if ((objectContactPoint - blockContactPoint).Length() < (objectContactPoint - lights[i].GetPosition()).Length())
                        {
                            isBlocked = true;
                            break;
                        }
                    }
                }
            }

            // View direction vector from camera to hit point
            Vector3 viewDir = (objectContactPoint - cameraPosition).Normalize();

            // Reflection direction vector
            Vector3 minusRayDir = ray.GetDirection() * (-1);
            Vector3 reflectDir = minusRayDir.Reflect(normal).Normalize();
            Vector3 helppls = chaseTheLight.GetDirection() - normal * normal.Dot(chaseTheLight.GetDirection()) * 2;

            // Diffuse light
            Vector3 lightDir = (objectContactPoint - lights[i].GetPosition()).Normalize();
            float diff = std::max(0.0f, -normal.Dot(lightDir));
            Intensity diffuseLight;
            if (!isSphere)
            {
                diffuseLight = hitPlane.GetColor() * lights[i].GetColor() * diff;
            }
            if (isSphere)
            {
                diffuseLight = objectColor * lights[i].GetColor() * diff;
            }

            // Specular light
            Vector3 halfwayDir = (lightDir + viewDir).Normalize();
            float specularIntensity = 4.0f;
            float spec = pow(std::max(0.0f, normal.Dot(halfwayDir)), specularIntensity);
            spec = pow(std::max(viewDir.Dot(helppls), 0.0f), specularIntensity);
            Intensity specularLight = lights[i].GetColor() * spec;

            if (!isBlocked)
            {
                finalColor = finalColor + diffuseLight + specularLight;
            }
            if (isBlocked && !isSphere)
            {
                //finalColor = finalColor + diffuseLight + specularLight;
            }
        }
        return finalColor;
    }

    else
        return backgroundColor;
}

void Camera::Render()
{
    int currentDepth = 0;

    for (int x = 0; x < screenWidth; x++)
    {
        for (int y = 0; y < screenHeight; y++)
        {
            float p1x = 2.0f * x / screenWidth - 1.0f;
            float p1y = 1.0f - 2.0f * y / screenHeight;
            float p2x = 2.0f * (x + 0.5f) / screenWidth - 1.0f;
            float p2y = 1.0f - 2.0f * (y + 0.5f) / screenHeight;
            img.SetPixel(x, y, Phong((p1x + p2x) / 2, (p1y + p2y) / 2));
            //img.SetPixel(x, y, PixelDivider(p1x, p1y, p2x, p2y, currentDepth)); // Pixel divider
        }
    }
    img.DrawOnWindow();
}

Intensity Camera::PixelDivider(float p1x, float p1y, float p2x, float p2y, int depth) {
    Intensity zero;

    std::vector<Intensity> allColors;

    std::vector<float> pointsX = { (p1x + p2x) / 2, std::min(p1x, p2x), std::max(p1x, p2x), std::min(p1x, p2x), std::max(p1x, p2x) };
    std::vector<float> pointsY = { (p1y + p2y) / 2, std::min(p1y, p2y), std::min(p1y, p2y), std::max(p1y, p2y), std::max(p1y, p2y) };

    bool drawColor = false;

    for (int i = 0; i < 5; i++) {
        float px = pointsX.at(i) * aspectRatio * tan(fov / 2.0f);
        float py = pointsY.at(i) * tan(fov / 2.0f);

        Vector3 rayDir(px, py, -1.0f);
        rayDir.Normalize();

        if (!isOrtographic)
        {
            Vector3 cameraDir = (cameraTarget - cameraPosition).Normalize();
            Vector3 cameraVectorRight = cameraVecUp.Cross(cameraDir).Normalize();
            Vector3 cameraUpNew = cameraDir.Cross(cameraVectorRight).Normalize();
            rayDir = (cameraVectorRight * px + cameraUpNew * py + cameraDir / fov).Normalize();
        }

        Ray ray(cameraPosition, rayDir);

        if (isOrtographic)
        {
            Vector3 rayOrigin = cameraPosition + Vector3(1, 0, 0) * px + Vector3(0, 1, 0) * py;
            ray = Ray(rayOrigin, rayDir);
        }

        // Check whether to draw object or background
        Vector3 contactPoint;
        for (int i = 0; i < spheres.size(); i++)
        {
            if (ray.intersectsSphere(spheres[i], contactPoint))
            {
                drawColor = true;
            }
        }
        std::vector<Mesh> newMeshes;
        for (int i = 0; i < meshes.size(); i++)
        {
            for (int j = 0; j < meshes[i].GetTriangles().size(); j++)
            {
                if (ray.intersectTriangle(meshes[i].GetTriangles()[j], contactPoint))
                {
                    drawColor = true;
                }
            }
        }
        if (drawColor)
        {
            allColors.push_back(Phong(pointsX.at(i), pointsY.at(i)));
        }
        else
        {
            allColors.push_back(backgroundColor);
        }
        drawColor = false;
    }

    // Average color of all the pixels
    Intensity averageColor;

    for (int i = 1; i < allColors.size(); i++)
    {
        if (allColors[0] - allColors[i] != zero && depth < maxDepth)
        {
            averageColor = averageColor + PixelDivider(pointsX[0], pointsY[0], pointsX[i], pointsY[i], depth + 1);
        }
        else
        {
            averageColor = averageColor + (allColors[0] + allColors[i]) / 2;
        }
    }

    return averageColor / 4;
}