#include <iostream>

#include "Image.h"
#include "Camera.h"

int main()
{
    int width = 1280;
    int height = 720;

    Image img(width, height);
    Intensity turqoise(0.0f, 1.0f, 1.0f);
    Intensity red(1.0f, 0.0f, 0.0f);

	img.FillImage(turqoise);
    img.DrawOnWindow();

    Camera cam(width, height);
    
    cam.Render(img, turqoise, red);

   

    return 0;
}
