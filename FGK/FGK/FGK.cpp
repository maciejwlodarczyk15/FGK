#include <iostream>
#include "Vector3.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"

int main()
{
    // 2. Sprawdz czy prawidlowo dziala przemiennosc dodawania za pomoca 
    // odpowiedniego zdefiniowania przykladowych wektorow i ich sumy w funkcji main(). 

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

    Vector3 subAB = a.Substract(b);
    std::cout << "\nVector A-B: \n";
    subAB.WriteCoordsToConsole();

    float dotAwithB = a.Dot(b);
    std::cout << "\nValues of dot product of A and B: \n" << dotAwithB;

    Vector3 crossAwithB = a.Cross(b);
    std::cout << "\nCoordinates of vector cross product of A to B: \n";
    crossAwithB.WriteCoordsToConsole();

    float lengthOfA = a.Length();
    std::cout << "\nLength of a: \n" << lengthOfA;

    // 3. Znajdz kat pomiedzy wektorem [0,3,0] a [5,5,0]

    Vector3 c({0.0f, 3.0f, 0.0f});
    Vector3 d({5.0f, 5.0f, 0.0f});

    std::cout << "\n\nCoordinates of vector c: \n";
    c.WriteCoordsToConsole();
    std::cout << "\nCoordinates of vector d: \n";
    d.WriteCoordsToConsole();

    float angleBetweenCandD = c.AngleBetweenVectors(d);
    std::cout << "\nAngle between c and d: \n" << angleBetweenCandD;

    // 4. Znajdz wektor prostopadly do wektorow [4,5,1] i [4,1,3]
    // !!! Iloczyn wektorowy dwoch wektorow daje wektor prostopadly do obu z nich

    Vector3 e({4.0f, 5.0f, 1.0f});
    Vector3 f({4.0f, 1.0f, 3.0f});

    std::cout << "\n\nCoordinates of vector e: \n";
    e.WriteCoordsToConsole();
    std::cout << "\nCoordinates of vector f: \n";
    f.WriteCoordsToConsole();

    Vector3 crossEwithF = e.Cross(f);
    std::cout << "\nVector perpendicular to vectors e and f: \n";
    crossEwithF.WriteCoordsToConsole();

    // 5. Znormalizuj powstaly wektor

    Vector3 crossEwithFNormalized = crossEwithF.Normalize();
    std::cout << "\nNormalized previous vector: \n";
    crossEwithFNormalized.WriteCoordsToConsole();

    // 7. Zdefiniowac sfere S o srodku w punkcie (0,0,0) i promieniu 10.
    Sphere s(10.0f, Vector3({0.0f, 0.0f, 0.0f}));

    // 8. Zdefiniowac promien R1 o poczatku w punkcie (0,0,-20) i skierowany w srodek kuli.
    
    Vector3 rayStarter({ 0.0f, 0.0f, -20.0f });
    Vector3 direction = s.GetCenter().Substract(rayStarter).Normalize();
    std::cout << "\n\nVector pointing at the center of sphere (0, 0, 0) from his starting point (0, 0, -20)\n";
    direction.WriteCoordsToConsole();

    Ray r1(rayStarter, direction);

    // 9. Zdefiniowac promien R2 o poczatku w tym samym punkcie, co R1, skierowany rownolegle do osi Y.

    Ray r2(rayStarter, Vector3({ 0.0f, 1.0f, 0.0f }));

    // 10. Prosze sprawdzic, czy istnieje przeciecie sfery S z promieniami R1 oraz R2.
    // 11. Wynik w postaci wspolrzednych punktu przeciecia nalezy wyswietlic.
    Vector3 contactPointR1({ 0.0, 0.0, 0.0 });
    if (r1.intersectsSphere(s, contactPointR1))
    {
        std::cout << "\nThe ray: R1 intersects with the sphere: S at: \n";
        contactPointR1.WriteCoordsToConsole();
    }
    else
    {
        std::cout << "\nThe ray: R1 does not intersect with the sphere: S";
    }
    Vector3 contactPointR2({ 0.0, 0.0, 0.0 });
    std::cout << "\n";
    if (r2.intersectsSphere(s, contactPointR1))
    {
        std::cout << "\nThe ray: R2 intersects with the sphere: S at: \n";
        contactPointR2.WriteCoordsToConsole();
    }
    else
    {
        std::cout << "\nThe ray: R2 does not intersect with the sphere: S";
    }

    
    // 12. Prosze zdefiniowac dowolny promien R3, tak aby przecinal on sfere S w dokładnie jednym punkcie. 
    // Podac wspolrzedne punktu przeciecia.
    Vector3 contactPointR3({ 0.0, 0.0, 0.0 });
    Ray r3(Vector3({10.0f, 10.0f, 0.0f}), Vector3({0.0f, -1.0f, 0.0f}));
    std::cout << "\n";
    if (r3.intersectsSphere(s, contactPointR3))
    {
        std::cout << "\nThe ray: R3 intersects with the sphere: S at: \n";
        contactPointR3.WriteCoordsToConsole();
    }
    else
    {
        std::cout << "\nThe ray: R3 does not intersect with the sphere: S";
    }

    // 13. Prosze zdefiniowac plaszczyzne P przechodzaca przez punkt (0,0,0), ktorej 
    // wektor normalny tworzy kat 45 stopni z osiami Y i Z.
    //      Vector3 PlaneNormal({ 1.0f, 1.0f, 0.0f });
    //      Vector3 PlaneNormalNormalized = PlaneNormal.Normalize();
    //      Plane p(PlaneNormalNormalized, Vector3({0.0f, 0.0f, 0.0f}));

    // 14. Prosze znalezc punkt przeciecia plaszczyzny P z promieniem R2.
    //     Vector3 contactPointR2P({ 0.0, 0.0, 0.0 });
    //     if (r2.intersectPlane(p, contactPointR2P)) 
    //     {
    //         std::cout << "\nThe ray: R2 intersects with the plane: P at: \n";
    //         contactPointR2P.WriteCoordsToConsole();
    //     }
    //     else 
    //     {
    //         std::cout << "\nThe ray: R2 does not intersect with the plane: P";
    //     }
    //     
    //     std::cout << "\n\n";
    Vector3 chuj({ 0.0f, 0.0f, -20.0f });
    Vector3 rayDirection({ 0.0f, 1.0f, 0.0f });
    Ray r(chuj, rayDirection);

    Vector3 planeNormal = Vector3({ 1.0f, 1.0f, 0.0f }).Normalize();
    Vector3 planePoint({ 0.0f, 0.0f, 0.0f });
    Plane p(planeNormal, planePoint);

    Vector3 contactPoint;
    if (r.intersectPlane(p, contactPoint)){
    //if (intersect(r, p, contactPoint)) {
        std::cout << "Intersection at: ";
        contactPoint.WriteCoordsToConsole();
    }
    else {
        std::cout << "No intersection.\n";
    }
}
