#include "classes.h"
#include <iostream>

int main()
{
    std::cout << "Started program." << std::endl;
    // float albedo[2] = {1, 0};
    float albedo[2] = {0.6, 0.3};
    Material ivory(Color(100, 100, 80), albedo, 50);

    std::cout << "Materials set." << std::endl;

    // Declare the Scene here
    Cube scene[] = {
        Cube(V3(0, 0, 0), V3(1, 1, 1), ivory)};
    int sceneSize = sizeof(scene) / sizeof(Cube);
    std::cout << "Scene set: " << sceneSize << " different objects have been found in the scene." << std::endl;

    Light light(V3(-0.5, 1, -2.75), 3);
    std::cout << "Light set." << std::endl;

    V3 camera(-0.5, 1, -2.75);
    std::cout << "Camera generated." << std::endl;

    Renderer r(1000, 1000, scene, light, sceneSize, camera);
    std::cout << "Created renderer." << std::endl;
    r.render();
    std::cout << "Image generated. Going to write to file: out.bmp" << std::endl;

    char *imageFileName = (char *)"out.bmp";
    r.generateBMP(imageFileName);
    std::cout << "Finished generating image." << std::endl;
    std::string a;
    std::cout << "Program has finished." << std::endl;

    return 0;
}