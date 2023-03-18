#include <iostream>

#include "Image.h"

int main()
{
    Image img(1280, 720);
    Intensity turqoise(0.0f, 1.0f, 1.0f);

    img.FillImage(turqoise);
    img.DrawOnWindow();

    return 0;
}
