#include <iostream>

#include "Image.h"
#include "Camera.h"
#include "Mesh.h"

int main()
{
    //Mesh newMesh("Cone.obj");
    std::vector<Mesh> meshes;
    //meshes.push_back(newMesh);

    int screenWidth = 800;
    int screenHeight = 600;

    Image img(screenWidth, screenHeight);

    //Vector3 camPos(0.0f, 10.0f, 10.0f);
    Vector3 camPos(0.0f, 0.0f, 10.0f);
    Vector3 camTarget(0.0f, 0.0f, 0.0f);
    Vector3 camUp(0.0f, 1.0f, 0.0f);
    float fov = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    int maxDepth = 0;

    Intensity objectColor(1.0f, 0.0f, 0.0f);
    Intensity backgroundColor(0.0f, 0.0f, 0.0f);

    std::vector<Sphere> spheres;
    //spheres.push_back(Sphere(0.5f, Vector3(-2.0f, -8.0f, -5.0f)));
    //spheres.push_back(Sphere(0.5f, Vector3(3.0f, -2.0f, -5.0f)));
    spheres.push_back(Sphere(1.0f, Vector3(0.0f, 0.0f, 0.0f)));
    spheres.push_back(Sphere(0.5f, Vector3(-2.0f, -1.0f, -5.0f)));
    spheres.push_back(Sphere(0.5f, Vector3(3.0f, 2.0f, -5.0f)));


    PointLight light1(Vector3(0.0f, 5.0f, 0.0f), Intensity(1.0f, 1.0f, 1.0f), 10.0f, 10.0f, 1.0f, 0.14f, 0.07f);

    Camera camera(camPos, camTarget, camUp, fov, farPlane, farPlane, maxDepth,
        img, objectColor, backgroundColor, spheres, meshes, light1, false);

    camera.Render();

    return 0;
}
