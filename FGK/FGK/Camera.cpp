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
        //=================================================================================================
        //========================================= usuń to potem =========================================
        //=================================================================================================
        //================================= Maciek, jesteśmy DEBILAMI xD ==================================
        //=================================================================================================
        //=============================== Braliśmy nie ten promień co trzeba ==============================
        //============== Braliśmy promień obiekt - kamera, a nie obiekt - źródło światła ==================
        //=================================================================================================
        

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

        // Debugger lmao
        /*
        if (pixelX == 0.49 * screenWidth or pixelX == 0.5 * screenWidth or pixelY == 0.47 * screenHeight or pixelY == 0.48 * screenHeight) {
            return Intensity(0.0f, 0.8f, 0.9f);
        }
        if (pixelX > 0.49 * screenWidth && pixelX < 0.5 * screenWidth && pixelY > 0.47 * screenHeight && pixelY < 0.48 * screenHeight) {
            //specularLight.WriteToConsole();
            //std::cout << ", spec:" << spec << "\n\n
            std::cout << "RayDir: ";
            ray.GetDirection().WriteCoordsToConsole();
            std::cout << ",\nNormal: ";
            normal.WriteCoordsToConsole();
            std::cout << ",\nReflectDir(?): ";
            helppls.WriteCoordsToConsole();
            std::cout << ",\nViewDir: ";
            viewDir.WriteCoordsToConsole();
            std::cout << ",\nDot product: " << viewDir.Dot(helppls * (-1)) << "\n\n";
        } */

        // Apply light intensity to the object color
        Intensity finalColor = objectColor * (ambientLight + diffuseLight) + specularLight;

        return finalColor;
    }
    //if (drawColor)
    //{
    //    // Normal vector at the hit point
    //    Vector3 normal = (contactPoint - hitSphere.GetCenter()).Normalize();
    //    // View direction vector from camera to hit point
    //    Vector3 viewDir = (contactPoint - cameraPosition).Normalize();
    //    //Vector3 viewDir = (cameraPosition - contactPoint).Normalize();
    //    // Reflection direction vector
    //    Vector3 minusRayDir = ray.GetDirection() * (-1);
    //    Vector3 reflectDir = minusRayDir.Reflect(normal).Normalize();
    //
    //    // Ambient light
    //    Intensity ambientLight = Intensity(0.1f, 0.1f, 0.1f);
    //
    //    // Diffuse light
    //    Vector3 lightDir = (pLight.GetPosition() - contactPoint).Normalize();
    //    float diff = std::max(0.0f, normal.Dot(lightDir));
    //    Intensity diffuseLight = objectColor * pLight.GetColor() * diff * pLight.GetIntensity();
    //
    //    // Specular light
    //    float specularIntensity = 64.0f;
    //    float spec = pow(std::max(0.0f, reflectDir.Dot(viewDir)), specularIntensity);
    //    Intensity specularLight = spec * pLight.GetIntensity();//pLight.GetColor() * 
    //
    //    // Calculate total light intensity
    //    Intensity totalLightIntensity = ambientLight + diffuseLight + specularLight;
    //
    //    // Apply light intensity to the object color
    //    Intensity finalColor = objectColor * (ambientLight + diffuseLight) + specularLight;
    //
    //    if (pixelX > screenWidth / 2)
    //    {
    //        std::cout << "viewDir: ";
    //        viewDir.WriteCoordsToConsole();
    //        std::cout << ", reflectDir: ";
    //        reflectDir.WriteCoordsToConsole();
    //        std::cout << ", coeff: " << reflectDir.Dot(viewDir) << "\n";
    //    }
    //
    //    return finalColor;
    //}

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