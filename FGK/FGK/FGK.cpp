﻿#include <iostream>

#include "Image.h"
#include "Camera.h"

int main()
{
    int screenWidth = 1280;
    int screenHeight = 720;

    Image img(screenWidth, screenHeight);

    Vector3 camPos(0.0f, 0.0f, 0.0f);
    Vector3 camTarget(0.0f, 0.0f, -5.0f);
    Vector3 camUp(0.0f, 1.0f, 0.0f);
    float fov = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    Camera camera(camPos, camTarget, camUp,
        fov, farPlane, farPlane, img, true);

    Intensity objectColor(1.0f, 0.0f, 0.0f);
    camera.Render(objectColor);

    return 0;
}
