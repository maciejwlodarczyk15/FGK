#include "Camera.h"
#include "Ray.h"
#include <iostream>
#include <vector>
#include <cmath>

#define M_PI 3.14159265358979323846

Camera::Camera(Vector3 camPos, Vector3 camTarget, Vector3 camUp, float fovDegree, float nPlane, float fPlane, int maxDepth,
    Image img, Intensity objectColor, Intensity backgroundColor, 
    std::vector<Sphere> spheres, std::vector<Mesh> meshes, PointLight pLight, bool isOrtographic)
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
    this->pLight = pLight;
}

//Intensity Camera::Phong(int pixelX, int pixelY)
//{
//    float p1x = 2.0f * pixelX / screenWidth - 1.0f;
//    float p1y = 1.0f - 2.0f * pixelY / screenHeight;
//    float p2x = 2.0f * (pixelX + 0.5f) / screenWidth - 1.0f;
//    float p2y = 1.0f - 2.0f * (pixelY + 0.5f) / screenHeight;
//    //float px = -1.8f + (pixelX + 0.5f) * screenWidth;
//    //float py = 1.0f - (pixelY + 0.5f) * screenHeight;
//    //float px = pixelX * aspectRatio * tan(fov / 2.0f);
//    //float py = pixelY * tan(fov / 2.0f);
//    float px = (2.0f * (pixelX + 0.5f) / screenWidth - 1.0f) * aspectRatio * tan(fov / 2.0f);
//    float py = (1.0f - 2.0f * (pixelY + 0.5f) / screenHeight) * tan(fov / 2.0f);
//    Vector3 rayDir(px, py, -1.0f);
//    rayDir.Normalize();
//
//    if (!isOrtographic)
//    {
//        Vector3 cameraDir = (cameraTarget - cameraPosition).Normalize();
//        Vector3 cameraVectorRight = cameraVecUp.Cross(cameraDir).Normalize();
//        Vector3 cameraUpNew = cameraDir.Cross(cameraVectorRight).Normalize();
//        rayDir = (cameraVectorRight * px + cameraUpNew * py + cameraDir / fov).Normalize();
//    }
//
//    Ray ray(cameraPosition, rayDir);
//    if (isOrtographic)
//    {
//        Vector3 rayOrigin = cameraPosition + Vector3(1, 0, 0) * px + Vector3(0, 1, 0) * py;
//        ray = Ray(rayOrigin, rayDir);
//    }
//
//    Sphere hitSphere;
// 
//    // Check whether to draw object or background
//    Vector3 contactPoint;
//    bool drawColor = false;
//    //ray.intersectsSphere(spheres[0], contactPoint);
//    //std::cout << "\n";
//    //contactPoint.WriteCoordsToConsole();
//    for (int i = 0; i < spheres.size(); i++)
//    {
//        if (ray.intersectsSphere(spheres[i], contactPoint))
//        {
//            drawColor = true;
//            hitSphere = spheres[i];
//            break;
//        }
//    }
//    if (drawColor)
//    {
//        float specular = 0.5f;         // kolor światła zwierciadlanego
//        float specularCoef = 0.7f;     // współczynnik odbicia zwierciadlanego
//        float a = 32.0f;               // wykładnik połysku
//
//
//        Ray checkBlock(contactPoint, pLight.GetPosition());
//        Vector3 blockContactPoint;
//        bool isBlocked = false;
//        for (int i = 0; i < spheres.size(); i++)
//        {
//            if (checkBlock.intersectsSphere(spheres[i], blockContactPoint))
//            {
//                float distanceObjectLight = (pLight.GetPosition() - contactPoint).Length();
//                float distanceObjectBlock = (blockContactPoint - contactPoint).Length();
//                if (distanceObjectLight >= distanceObjectBlock)
//                {
//                    isBlocked = true;
//                }
//            }
//        }
//
//        if (!isBlocked) {}
//
//
//        Vector3 N = hitSphere.GetNormal(contactPoint);
//        Vector3 L = ray.GetDirection().Normalize();
//        Vector3 R = L - N * L.Dot(N) * 2;
//        Vector3 V = (cameraTarget - cameraPosition).Normalize();
//
//        float ka = 1.0f;                                   // współczynnik oświetlenia otoczenia
//        float kd = std::max(N.Dot(L), 0.0f);               // współczynnik odbicia dyfuzyjnego
//        float ks = std::pow(std::max(R.Dot(V), 0.0f), a);  // współczynnik odbicia zwierciadlanego
//
//        Intensity I = Intensity(0.0f, 0.0f, 0.0f) * ka + Intensity(0.5f, 0.5f, 0.5f) * kd + Intensity(1.0f, 1.0f, 1.0f) * ks;
//        return objectColor * I;
//
//        /*
//        Vector3 I = ray.GetDirection().Normalize();
//        Vector3 N = hitSphere.GetNormal(contactPoint);
//        Vector3 R = I - (N * N.Dot(I) * 2.0f);
//        
//        float ss = ray.GetDirection().Normalize().Dot(R);
//        //std::cout << ss << "\n";
//        if (ss > 0)
//        {
//            specular = std::pow(ss, a);
//        }
//        else
//        {
//            specular = 0;
//        }
//        specular *= specularCoef;
//        Intensity sIntensity = pLight.GetIntensity() * specular;
//        cosinus = (ray.GetDirection() * -1).Normalize().Dot(hitSphere.GetNormal(contactPoint));
//        Intensity lightIntensity = pLight.GetIntensity();
//        r = lightIntensity.GetRed() * k * cosinus; 
//        g = lightIntensity.GetGreen() * k * cosinus;
//        b = lightIntensity.GetBlue() * k * cosinus;
//        Intensity diffuseIntensity = Intensity(r, g, b) + backgroundColor;
//        return sIntensity + diffuseIntensity;
//        */
//    }
//    else
//        return backgroundColor;
//}
Intensity Camera::Phong(int pixelX, int pixelY)
{
    float px = (2.0f * (pixelX + 0.5f) / screenWidth - 1.0f) * aspectRatio * tan(fov / 2.0f);
    float py = (1.0f - 2.0f * (pixelY + 0.5f) / screenHeight) * tan(fov / 2.0f);
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

    Sphere hitSphere;

    // Check whether to draw object or background
    Vector3 contactPoint;
    bool drawColor = false;
    for (int i = 0; i < spheres.size(); i++)
    {
        if (ray.intersectsSphere(spheres[i], contactPoint))
        {
            drawColor = true;
            hitSphere = spheres[i];
            break;
        }
    }
    if (drawColor)
    { 
        // Please work now
        Ray chaseTheLight = Ray(contactPoint, (contactPoint - pLight.GetPosition()).Normalize());

        // Normal vector at the hit point
        Vector3 normal = (contactPoint - hitSphere.GetCenter()).Normalize();
        // View direction vector from camera to hit point
        Vector3 viewDir = (contactPoint - cameraPosition).Normalize();
        //Vector3 viewDir = (cameraPosition - contactPoint).Normalize();
        // Reflection direction vector
        Vector3 minusRayDir = ray.GetDirection() * (-1);
        Vector3 reflectDir = minusRayDir.Reflect(normal).Normalize();
        Vector3 helppls = chaseTheLight.GetDirection() - normal * normal.Dot(chaseTheLight.GetDirection()) * 2;

        // Ambient light
        Intensity ambientLight = Intensity(0.1f, 0.1f, 0.1f);

        // Diffuse light
        Vector3 lightDir = (pLight.GetPosition() - contactPoint).Normalize();
        float diff = std::max(0.0f, normal.Dot(lightDir));
        Intensity diffuseLight = objectColor * pLight.GetColor() * diff;

        // Specular light
        Vector3 halfwayDir = (lightDir + viewDir).Normalize();
        float specularIntensity = 4.0f;
        float spec = pow(std::max(0.0f, normal.Dot(halfwayDir)), specularIntensity); spec = pow(std::max(viewDir.Dot(helppls * (-1)), 0.0f), specularIntensity);
        Intensity specularLight = pLight.GetColor() * spec;

        // Calculate total light intensity
        Intensity totalLightIntensity = ambientLight + diffuseLight + specularLight;

        // Apply light intensity to the object color
        Intensity finalColor = objectColor * (ambientLight + diffuseLight) + specularLight;

        return finalColor;
    }

    else
        return backgroundColor;
}

Intensity Camera::Phong(float px, float py)
{
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

    Sphere hitSphere;

    // Check whether to draw object or background
    Vector3 contactPoint;
    bool drawColor = false;
    for (int i = 0; i < spheres.size(); i++)
    {
        if (ray.intersectsSphere(spheres[i], contactPoint))
        {
            drawColor = true;
            hitSphere = spheres[i];
            break;
        }
    }
    if (drawColor)
    {
        // Please work now
        Ray chaseTheLight = Ray(contactPoint, (contactPoint - pLight.GetPosition()).Normalize());

        // Normal vector at the hit point
        Vector3 normal = (contactPoint - hitSphere.GetCenter()).Normalize();
        // View direction vector from camera to hit point
        Vector3 viewDir = (contactPoint - cameraPosition).Normalize();
        // Reflection direction vector
        Vector3 minusRayDir = ray.GetDirection() * (-1);
        Vector3 reflectDir = minusRayDir.Reflect(normal).Normalize();
        Vector3 helppls = chaseTheLight.GetDirection() - normal * normal.Dot(chaseTheLight.GetDirection()) * 2;

        // Ambient light
        Intensity ambientLight = Intensity(0.1f, 0.1f, 0.1f);

        // Diffuse light
        Vector3 lightDir = (pLight.GetPosition() - contactPoint).Normalize();
        float diff = std::max(0.0f, normal.Dot(lightDir));
        Intensity diffuseLight = objectColor * pLight.GetColor() * diff;

        // Specular light
        Vector3 halfwayDir = (lightDir + viewDir).Normalize();
        float specularIntensity = 4.0f;
        float spec = pow(std::max(0.0f, normal.Dot(halfwayDir)), specularIntensity); spec = pow(std::max(viewDir.Dot(helppls * (-1)), 0.0f), specularIntensity);
        Intensity specularLight = pLight.GetColor() * spec;

        // Calculate total light intensity
        Intensity totalLightIntensity = ambientLight + diffuseLight + specularLight;

        // Apply light intensity to the object color
        Intensity finalColor = objectColor * (ambientLight + diffuseLight) + specularLight;

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
            img.SetPixel(x, y, Phong((p1x + p2x) / 2, (p1y + p2y) / 2));  // Phong float
            //img.SetPixel(x, y, PixelDivider(p1x, p1y, p2x, p2y, currentDepth)); // Pixel divider
            //img.SetPixel(x, y, Phong(x, y));  // Phong int
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
        //std::vector<Mesh> newMeshes;
        //for (int i = 0; i < meshes.size(); i++)
        //{
        //    for (int j = 0; j < meshes[i].GetTriangles().size(); j++)
        //    {
        //        if (ray.intersectTriangle(meshes[i].GetTriangles()[j], contactPoint))
        //        {
        //            drawColor = true;
        //        }
        //    }
        //}
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