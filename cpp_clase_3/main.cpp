#include "classes.h"
#include <iostream>
int main()
{
    Color temp(100, 100, 80);
    float albedo[2] = {0.6, 0.3};
    Material ivory(temp, albedo, 50);
    
    temp.r = 80;
    temp.g = 0;
    temp.b = 0;
    albedo[0] = 0.9;
    albedo[1] = 0.1;
    Material rubber(temp, albedo, 10);
    Sphere scene[3] = {Sphere(V3(0, -1.5, -10), 1.5, ivory),
                       Sphere(V3(-2, -1, -12), 2, rubber),
                       Sphere(V3(1, 1, -8), 1.7, rubber)};

    Light light(V3(-20, 20, 20), 1.5);
    Renderer r(1000, 1000, scene, light);

    r.render();
    char * imageFileName= (char *)"out.bmp";
    r.generateBMP(imageFileName);
    printf("Finished.\n");
}