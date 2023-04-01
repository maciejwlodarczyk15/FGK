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

Intensity Camera::Phong(int pixelX, int pixelY)
{
    //float px = -1.8f + (pixelX + 0.5f) * screenWidth;
    //float py = 1.0f - (pixelY + 0.5f) * screenHeight;
    //float px = pixelX * aspectRatio * tan(fov / 2.0f);
    //float py = pixelY * tan(fov / 2.0f);
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
    //ray.intersectsSphere(spheres[0], contactPoint);
    //std::cout << "\n";
    //contactPoint.WriteCoordsToConsole();
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
        float specular = 0.5f;
        float a = 32.0f;
        float specularCoef = 0.7f;
        float k = 0.8f;
        float r, g, b, cosinus;
        Vector3 I = ray.GetDirection().Normalize();
        Vector3 N = hitSphere.GetNormal(contactPoint);
        Vector3 R = I - (N * N.Dot(I) * 2.0f);
        
        float ss = ray.GetDirection().Normalize().Dot(R);
        //std::cout << ss << "\n";
        if (ss > 0)
        {
            specular = std::pow(ss, a);
        }
        else
        {
            specular = 0;
        }
        specular *= specularCoef;
        Intensity sIntensity = pLight.GetIntensity() * specular;
        cosinus = (ray.GetDirection() * -1).Normalize().Dot(hitSphere.GetNormal(contactPoint));
        Intensity lightIntensity = pLight.GetIntensity();
        r = lightIntensity.GetRed() * k * cosinus; 
        g = lightIntensity.GetGreen() * k * cosinus;
        b = lightIntensity.GetBlue() * k * cosinus;
        Intensity diffuseIntensity = Intensity(r, g, b) + backgroundColor;
        return sIntensity + diffuseIntensity;
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
            //img.SetPixel(x, y, PixelDivider(p1x, p1y, p2x, p2y, currentDepth));
            img.SetPixel(x, y, Phong(x, y));
        }
    }
    img.DrawOnWindow();
}

Intensity Camera::PixelDivider(float p1x, float p1y, float p2x, float p2y, int depth) 
{
    Intensity zero;

    std::vector<Intensity> allColors;
    
    std::vector<float> pointsX = { (p1x + p2x) / 2, std::min(p1x, p2x), std::max(p1x, p2x), std::min(p1x, p2x), std::max(p1x, p2x) };
    std::vector<float> pointsY = { (p1y + p2y) / 2, std::min(p1y, p2y), std::min(p1y, p2y), std::max(p1y, p2y), std::max(p1y, p2y) };

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

    //   Sphere hitSphere;
    //
    //   // Check whether to draw object or background
    //   Vector3 contactPoint;
    //   bool drawColor = false;
    //   for (int i = 0; i < spheres.size(); i++)
    //   {
    //       if (ray.intersectsSphere(spheres[i], contactPoint))
    //       {
    //           drawColor = true;
    //           hitSphere = spheres[i];
    //           break;
    //       }
    //   } 
    //   std::vector<Mesh> newMeshes;
    //   for (int k = 0; k < meshes.size(); k++)
    //   {
    //       for (int j = 0; j < meshes[k].GetTriangles().size(); j++)
    //       {
    //           if (ray.intersectTriangle(meshes[k].GetTriangles()[j], contactPoint))
    //           {
    //               drawColor = true;
    //               break;
    //           }
    //       }
    //       if (drawColor) 
    //       {
    //           break;
    //       }
    //   }
    //   if (drawColor)
    //   {
    //       Ray checkBlock(contactPoint, pLight.GetPosition());
    //       Vector3 blockContactPoint;
    //       bool isBlocked = false;
    //       for (int i = 0; i < spheres.size(); i++)
    //       {
    //           if (checkBlock.intersectsSphere(spheres[i], blockContactPoint))
    //           {
    //               float distanceObjectLight = (pLight.GetPosition() - contactPoint).Length();
    //               float distanceObjectBlock = (blockContactPoint - contactPoint).Length();
    //               if (distanceObjectLight >= distanceObjectBlock)
    //               {
    //                   isBlocked = true;
    //               }
    //           }
    //       }
    //       
    //       if (!isBlocked)
    //       {
    //           float distance = (contactPoint - pLight.GetPosition()).Length();
    //           
    //           if (distance > pLight.GetRange())
    //           {
    //               allColors.push_back(backgroundColor);
    //           }
    //           else
    //           {
    //               float specular = 0.5f;
    //               float a = 32.0f;
    //               float specularCoef = 0.7f;
    //               float k = 0.8f;
    //               float r, g, b, cosinus;
    //               Vector3 I = ray.GetDirection().Normalize();
    //               Vector3 N = hitSphere.GetNormal(contactPoint);
    //               Vector3 R = I - (N * N.Dot(I) * 2.0f);
    //
    //               float ss = ray.GetDirection().Normalize().Dot(R);
    //               if (-ss > 0)
    //               {
    //                   specular = std::pow(ss, a);
    //               }
    //               else
    //               {
    //                   specular = 0;
    //               }
    //               specular *= specularCoef;
    //               Intensity sIntensity = pLight.GetIntensity() * specular;
    //               cosinus = ray.GetDirection().Normalize().Dot(hitSphere.GetNormal(contactPoint));
    //               Intensity lightIntensity = pLight.GetIntensity();
    //               r = lightIntensity.GetRed() * k * cosinus; 
    //               g = lightIntensity.GetGreen() * k * cosinus;
    //               b = lightIntensity.GetBlue() * k * cosinus;
    //               Intensity diffuseIntensity = Intensity(1, g, b) + backgroundColor;
    //               allColors.push_back(sIntensity + diffuseIntensity);
    //               //float attenuation = 1.0f / (pLight.GetConstant() + pLight.GetLinear() * distance + pLight.GetQuadratic() * distance);
                    //
                    //Vector3 lightDirection = (pLight.GetPosition() - contactPoint).Normalize();
                    //
                    //float diffuse = std::max((hitSphere.GetNormal(contactPoint).Dot(lightDirection)), 0.0f);
                    //
                    //Vector3 viewDirection = (cameraPosition - contactPoint).Normalize();
                    //
                    //float dotProduct = (lightDirection * -1).Dot(hitSphere.GetNormal(contactPoint));
                    //Vector3 reflected = (lightDirection * -1) - hitSphere.GetNormal(contactPoint) * dotProduct * 2;
                    //
                    //float specular = std::pow(std::max(viewDirection.Dot(reflected), 0.0f), 1.0f);
                    //
                    //
                    ////Vector3 finalColor = Vector3(objectColor) * diffuse * Vector3(pLight.GetIntensity()) * Vector3(pLight.GetColor()) * attenuation + pLight.GetColor() * pLight.GetIntensity() * specular * attenuation;
                    ////Vector3 finalColor = objectColor * diffuse * pLight.GetIntensity() * Vector3(pLight.GetColor()) * attenuation + pLight.GetColor() * pLight.GetIntensity() * specular * attenuation;
                    //Intensity finalColor = objectColor * diffuse * pLight.GetIntensity() * pLight.GetColor() * attenuation + pLight.GetColor() * pLight.GetIntensity() * specular * attenuation;
                    //allColors.push_back(Intensity(finalColor));
    //           }
    //       }
    //
    //   
    //       //// Light 
            //Vector3 intersectionToLight = (pLight.GetPosition() - contactPoint).Normalize();
            //// Calculate length from light to contact point
            //float distanceToLight = (pLight.GetPosition() - contactPoint).Length();
            //float attenuation = 1.0f / (pLight.GetConstant() + pLight.GetLinear() * distanceToLight + pLight.GetQuadratic() * distanceToLight * distanceToLight);
            //Intensity lightColor = pLight.GetColor() * pLight.GetIntensity() * attenuation;
            //
            //Intensity resultColor = objectColor * lightColor;
    //
    //
    //       //allColors.push_back(objectColor * lightColor);'
            // 
            //std::cout << "\nC: ";
            //objectColor.WriteToConsole();
            //std::cout << "\nL: ";
            //lightColor.WriteToConsole();
            //std::cout << "\nCL: ";
            //resultColor.WriteToConsole();
    //
    //       //allColors.push_back(objectColor);
            //allColors.push_back(resultColor);
    //       
    }
    //   else
    //   {
    //       allColors.push_back(backgroundColor);
    //   }
    //   drawColor = false;
    //

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