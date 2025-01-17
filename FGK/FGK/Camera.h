#pragma once

#include "Image.h"
#include "Vector.h"
#include "Sphere.h"
#include "Mesh.h"
#include "PointLight.h"
#include "Plane.h"
#include "Ray.h"
#include <vector>

class Camera {
private:
    Vector3 cameraPosition;
    Vector3 cameraTarget;
    Vector3 cameraVecUp;
    Image img;
    int screenWidth;
    int screenHeight;
    int maxDepth;
    float aspectRatio;
    float fov;
    float nearPlane;
    float farPlane;
    bool isOrtographic;
    Intensity backgroundColor;
    std::vector<Sphere> spheres;
    std::vector<Mesh> meshes;
    std::vector<PointLight> lights;
    std::vector<Plane> planes;

public:
    Camera(Vector3 camPos, Vector3 camTarget,  Vector3 camUp, float fovDegree, float nPlane, float fPlane, int maxDepth,
        Image img, Intensity backgroundColor, 
        std::vector<Sphere> spheres, std::vector<Mesh> meshes, std::vector<PointLight> lights, std::vector<Plane> planes, bool isOrtographic);

    void Render();

    //Intensity PixelDivider(float p1x, float p1y, float p2x, float p2y, int depth);

    Intensity Phong(Ray givenRay, int reflectionDepth);
};

