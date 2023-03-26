#pragma once

#include "Image.h"
#include "Vector.h"
#include "Sphere.h"
#include "Mesh.h"
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
    Intensity objectColor; 
    Intensity backgroundColor;
    std::vector<Sphere> spheres;
    std::vector<Mesh> meshes;

public:
    Camera(Vector3 camPos, Vector3 camTarget,  Vector3 camUp, float fovDegree, float nPlane, float fPlane, int maxDepth,
        Image img, Intensity objectColor, Intensity backgroundColor, std::vector<Sphere> spheres, std::vector<Mesh> meshes, bool isOrtographic);

    void Render();

    Intensity PixelDivider(int x, int y, int depth, int maxDepth);
    Intensity QbDivider(float p1x, float p1y, float p2x, float p2y, int depth);
};

