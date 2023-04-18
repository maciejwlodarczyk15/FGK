#include <iostream>

#include "Image.h"
#include "Camera.h"
#include "Mesh.h"

int main()
{
    std::vector<Mesh> meshes;

    int screenWidth = 800;
    int screenHeight = 600;

    Image img(screenWidth, screenHeight);

    Vector3 camPos(0.0f, 0.0f, 10.0f);
    Vector3 camTarget(0.0f, 0.0f, 0.0f);
    Vector3 camUp(0.0f, 1.0f, 0.0f);
    float fov = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    int maxDepth = 0;

    Intensity backgroundColor(0.0f, 0.0f, 0.0f);

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(1.0f, Vector3(-1.25f, -0.9f, -4.0f), 1, Intensity(1.0f, 1.0f, 1.0f)));
    spheres.push_back(Sphere(1.0f, Vector3(1.25f, -0.9f, -1.5f), 2, Intensity(1.0f, 1.0f, 1.0f)));

    std::vector<PointLight> lights;
    PointLight light1(Vector3(0.0f, 1.9f, 0.0f), Intensity(0.6f, 0.6f, 0.6f), 250.0f, 10.0f, 1.0f, 0.14f, 0.07f);
    lights.push_back(light1);

    std::vector<Plane> planes;

    Plane backPlane(Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, -11.0f), Intensity(1.0f, 1.0f, 1.0f));
    Plane frontPlane(Vector3(0.0f, 0.0f, -1.0f), Vector3(0.0f, 0.0f, 11.0f), Intensity(1.0f, 1.0f, 1.0f));
    Plane leftPlane(Vector3(1.0f, 0.0f, 0.0f), Vector3(-3.0f, 0.0f, 0.0f), Intensity(1.0f, 0.0f, 0.0f));
    Plane rightPlane(Vector3(-1.0f, 0.0f, 0.0f), Vector3(3.0f, 0.0f, 0.0f), Intensity(0.0f, 0.0f, 1.0f));
    Plane upPlane(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, 2.0f, 0.0f), Intensity(1.0f, 1.0f, 1.0f));
    Plane downPlane(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, -2.0f, 0.0f), Intensity(1.0f, 1.0f, 1.0f));

    planes.push_back(leftPlane);
    planes.push_back(downPlane);
    planes.push_back(rightPlane);
    planes.push_back(upPlane);
    planes.push_back(backPlane);
    planes.push_back(frontPlane);
    
    Camera camera(camPos, camTarget, camUp, fov, farPlane, farPlane, maxDepth,
        img, backgroundColor, spheres, meshes, lights, planes, true);

    camera.Render();

    return 0;
}
