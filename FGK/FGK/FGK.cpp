#include <iostream>
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include "Mesh.h"
#include "Camera.h"
#include "Buffer.h"
#include "Triangle.h"

#include <opencv2/opencv.hpp>

int main()
{
    // Load an image from file
    cv::Mat image = cv::imread("test.jpg");

    // Display the image in a window
    cv::imshow("Test Image", image);
    cv::waitKey(0);

    return 0;
}
