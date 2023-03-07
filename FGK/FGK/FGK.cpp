#include <iostream>
#include "Vector3.h"

int main()
{
    Vector3 a({1.0f, 3.0f, 9.0f});
    Vector3 b({4.0f, 8.0f, 12.0f});

    Vector3 sumAtoB = a.Add(b);
    Vector3 sumBtoA = b.Add(a);

    std::cout << "\nCoordinates of vector a: \n";
    a.WriteCoordsToConsole();
    std::cout << "\nCoordinates of vector b: \n";
    b.WriteCoordsToConsole();
    std::cout << "\nCoordinates of vector A to B: \n";
    sumAtoB.WriteCoordsToConsole();
    std::cout << "\nCoordinates of vector B to A: \n";
    sumBtoA.WriteCoordsToConsole();

    float dotAwithB = a.Dot(b);
    std::cout << "\nValues of dot product of A and B: \n" << dotAwithB;

    Vector3 crossAwithB = a.Cross(b);
    std::cout << "\nCoordinates of vector cross product of A to B: \n";
    crossAwithB.WriteCoordsToConsole();

    float lengthOfA = a.Length();
    std::cout << "\nLength of a: \n" << lengthOfA;

    Vector3 c({0.0f, 3.0f, 0.0f});
    Vector3 d({5.0f, 5.0f, 0.0f});

    std::cout << "\n\nCoordinates of vector c: \n";
    c.WriteCoordsToConsole();
    std::cout << "\nCoordinates of vector d: \n";
    d.WriteCoordsToConsole();

    float angleBetweenCandD = c.AngleBetweenVectors(d);
    std::cout << "\nAngle between c and d: \n" << angleBetweenCandD;

    Vector3 e({4.0f, 5.0f, 1.0f});
    Vector3 f({4.0f, 1.0f, 3.0f});

    std::cout << "\n\nCoordinates of vector e: \n";
    e.WriteCoordsToConsole();
    std::cout << "\nCoordinates of vector f: \n";
    f.WriteCoordsToConsole();

    Vector3 crossEwithF = e.Cross(f);
    std::cout << "\nVector perpendicular to vectors e and f: \n";
    crossEwithF.WriteCoordsToConsole();

    Vector3 crossEwithFNormalized = crossEwithF.Normalize();
    std::cout << "\nNormalized previous vector: \n";
    crossEwithFNormalized.WriteCoordsToConsole();
}
