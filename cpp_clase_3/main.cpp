#include "classes.h"
#include <iostream>
int main()
{
    std::cout << "Started program." << std::endl;
    float albedo[2] = {0.6, 0.3};
    Material ivory(Color(100, 100, 80), albedo, 50);

    albedo[0] = 0.9;
    albedo[1] = 0.1;
    Material rubber(Color(80, 0, 0), albedo, 10);

    albedo[0] = 0.6;
    albedo[1] = 0.8;
    Material whitefur(Color(255, 255, 255), albedo, 50);

    albedo[0] = 0.5;
    albedo[1] = 0.8;
    Material silver(Color(150, 150, 150), albedo, 50);

    albedo[0] = 0.6;
    albedo[1] = 0.3;
    Material black(Color(50, 50, 50), albedo, 50);

    albedo[0] = 0.5;
    albedo[1] = 0.5;
    Material brownfur(Color(189, 126, 74), albedo, 50);

    albedo[0] = 0.5;
    albedo[1] = 0.8;
    Material brownlightfur(Color(255, 204, 153), albedo, 50);

    albedo[0] = 0.5;
    albedo[1] = 0.8;
    Material green(Color(20, 200, 20), albedo, 50);
    double x_displacement = 8;
    std::cout << "Materials set." << std::endl;
    Sphere scene[] = {
        // White bear
        Sphere(V3(-4.5, 3.5, -12), 2.1, whitefur),   // Head
        Sphere(V3(-6, 5.5, -12), 1, whitefur),       // Left ear
        Sphere(V3(-3.2, 5.5, -12), 1, whitefur),     // Right ear
        Sphere(V3(-4.5, 3, -10.25), 1, whitefur),    // Snout
        Sphere(V3(-2.5, 1, -10.25), 1, whitefur),    // Left Arm
        Sphere(V3(-5, 1.5, -10.25), 0.7, rubber),    // Bow tie
        Sphere(V3(-4, 1.5, -10.25), 0.7, rubber),    // Bow tie
        Sphere(V3(-6.55, 1, -10.25), 1, whitefur),   // Right Arm
        Sphere(V3(-6.2, -1.5, -10.25), 1, whitefur), // Right leg
        Sphere(V3(-2.7, -1.5, -10.25), 1, whitefur), // Left leg
        Sphere(V3(-4, 4, -10.25), 0.3, black),       // Eye left
        Sphere(V3(-5, 4, -10.25), 0.3, black),       // Eye Right
        Sphere(V3(-4.5, 3.2, -9.5), 0.3, black),     // Nose
        Sphere(V3(-4.5, 0, -12), 2.5, silver),       // Body

        // Brown Bear
        Sphere(V3(-4.5 + x_displacement, 3.5, -12), 2.1, brownlightfur),   // Head
        Sphere(V3(-6 + x_displacement, 5.5, -12), 1, brownfur),            // Left ear
        Sphere(V3(-3.2 + x_displacement, 5.5, -12), 1, brownfur),          // Right ear
        Sphere(V3(-4.5 + x_displacement, 3, -10.25), 1, brownfur),         // Snout
        Sphere(V3(-2.5 + x_displacement, 1, -10.25), 1, brownlightfur),    // Left Arm
        Sphere(V3(-5 + x_displacement, 1.5, -10.25), 0.7, green),                          // Bow tie
        Sphere(V3(-4 + x_displacement, 1.5, -10.25), 0.7, green),                          // Bow tie
        Sphere(V3(-6.55 + x_displacement, 1, -10.25), 1, brownlightfur),   // Right Arm
        Sphere(V3(-6.2 + x_displacement, -1.5, -10.25), 1, brownlightfur), // Right leg
        Sphere(V3(-2.7 + x_displacement, -1.5, -10.25), 1, brownlightfur), // Left leg
        Sphere(V3(-4 + x_displacement, 4, -10.25), 0.3, black),            // Eye left
        Sphere(V3(-5 + x_displacement, 4, -10.25), 0.3, black),            // Eye Right
        Sphere(V3(-4.5 + x_displacement, 3.2, -9.5), 0.3, black),          // Nose
        Sphere(V3(-4.5 + x_displacement, 0, -12), 2.5, rubber),            // Body
    };
    int sceneSize = sizeof(scene) / sizeof(Sphere);
    std::cout << "Scene set: " << sceneSize << " different objects have been found in the scene." << std::endl;

    Light light(V3(0, 0, 0), 1.65);
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
    std::cout << "Program has finished. Press enter..." << std::endl;
    std::cin >> a;
    return 0;
}