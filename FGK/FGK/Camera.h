#pragma once

#include "Image.h"
#include "Vector.h"

class Camera {
private:
    Vector3 cameraPosition;
    Vector3 cameraTarget;
    Vector3 cameraVecUp;
    Image img;
    int screenWidth;
    int screenHeight;
    float aspectRatio;
    float fov;
    float nearPlane;
    float farPlane;
    bool isOrtographic;

public:
    //Camera(Vector3 camPos, float fovDegree, Image img);
    Camera(Vector3 camPos, Vector3 camTarget,  Vector3 camUp, float fovDegree, float nPlane, float fPlane, Image img, bool isOrtographic);

    void Render(Intensity objectColor);
};

