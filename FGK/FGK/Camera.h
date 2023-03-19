#pragma once

#include "Image.h"
#include "Vector.h"

class Camera {
private:
    Vector3 cameraPosition;
    Image img;
    int screenWidth;
    int screenHeight;
    float aspectRatio;
    float fov;

public:
    Camera(Vector3 camPos, float fovDegree, Image img);

    void Render(Intensity objectColor);
};

