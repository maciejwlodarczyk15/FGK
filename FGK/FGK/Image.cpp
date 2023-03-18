#include "Image.h"
#include <opencv2/opencv.hpp>

Image::Image(int w, int h)
{
	width = w;
	height = h;
	pixels = new Intensity[width * height];
}

Image::~Image()
{
	delete[] pixels;
}

void Image::SetPixel(int x, int y, Intensity intensity)
{
	int index = y * width + x;
	pixels[index] = intensity;
}

void Image::FillImage(Intensity intensity)
{
    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++)
        {
            SetPixel(x, y, intensity);
        }
    }
}

void Image::DrawOnWindow()
{
    cv::Mat img(height, width, CV_8UC3);
    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            int index = y * width + x;
            img.at<cv::Vec3b>(y, x) = cv::Vec3b(pixels[index].GetBlue() * 255,
                pixels[index].GetGreen() * 255,
                pixels[index].GetRed() * 255);
        }
    }
    cv::imshow("Image", img);
    cv::waitKey(0);
}
