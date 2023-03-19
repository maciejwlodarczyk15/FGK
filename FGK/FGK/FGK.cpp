#include <iostream>

#include "Image.h"
#include "Camera.h"

int main()
{
    int screenWidth = 1280;
    int screenHeight = 720;

    Image img(screenWidth, screenHeight);

    Vector3 camPos(0.0f, 0.0f, 0.0f);
    Camera camera(camPos, 60.0, img);

    Intensity objectColor(1.0f, 0.0f, 0.0f);
    camera.Render(objectColor);

    return 0;
}
