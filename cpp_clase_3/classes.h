#include <vector>

class V3
{
public:
    long double x, y, z;

    V3(long double x_arg, long double y_arg, long double z_arg)
    {
        x = x_arg;
        y = y_arg;
        z = z_arg;
    }
    V3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
};

#pragma region Linear Algebra
long double maxf(long double arg1, long double arg2);
V3 sum(V3 v0, V3 v1);
V3 sub(V3 v0, V3 v1);
V3 mul(V3 v0, long double k);
long double dot(V3 v0, V3 v1);
V3 cross(V3 v0, V3 v1);
long double length(V3 v0);
V3 norm(V3 v0);
V3 reflect(V3 I, V3 N);
#pragma endregion

#pragma region Classes

class Light
{
public:
    V3 position;
    float intensity;

    Light(V3 position1, float intensity1)
    {
        position = position1;
        intensity = intensity1;
    }

    Light() {}
};

class Color
{
public:
    long double r, g, b;
    Color(){};
    Color(long double r_arg, long double g_arg, long double b_arg)
    {
        r = r_arg;
        g = g_arg;
        b = b_arg;
    }
};

class Material
{
public:
    Color diffuse;
    float albedo[2], spec;
    Material(){};
    bool active;

    Material(Color diffuse_arg, float *albedo_arg, float spec_arg)
    {
        diffuse = diffuse_arg;
        albedo[0] = *(albedo_arg);
        albedo[1] = *(albedo_arg + 1);
        spec = spec_arg;
        active = false;
    }
};

class Intersect
{
public:
    long double distance;
    V3 point, normal;
    bool valid, active;

    Intersect(long double distance_arg, V3 point_arg, V3 normal_arg, bool valid_arg)
    {
        distance = distance_arg;
        point = point_arg;
        normal = normal_arg;
        valid = valid_arg;
        active = false;
    }

    Intersect()
    {
    }
};

class Sphere
{
public:
    V3 center;
    float radius;
    Material material;

    Sphere(V3 center_arg, float radius_arg, Material material_arg)
    {
        radius = radius_arg;
        material = material_arg;
        center = center_arg;
    }
    Sphere(){};

    Intersect ray_intersect(V3 orig, V3 direction);
};

class Renderer
{
public:
    int height, width, sceneSize = 0;
    unsigned char *pixels;
    Material currentMaterial;
    Intersect currentIntersect;
    std::vector<Sphere> scene;
    Light light;
    V3 camera;

    Renderer(int x, int y, Sphere scene_arg[], Light light_arg, int sceneSize_arg, V3 camera1)
    {
        width = x;
        height = y;
        sceneSize = sceneSize_arg;
        pixels = new unsigned char[width * height * 3];
        for (int i = 0; i < sceneSize; i++)
        {
            scene.push_back(scene_arg[i]);
        }
        light = light_arg;
        camera = camera1;
    }

    void generateBMP(char *ImageFileName);
    void generateBitmapImage(unsigned char *image, char *imageFileName);
    unsigned char *createBitmapInfoHeader(int height, int width);
    unsigned char *createBitmapFileHeader(int height, int stride);
    void point(int x, int y, Color color);
    bool scene_intersect(V3 orig, V3 directions);
    V3 cast_ray(V3 orig, V3 direction);
    void render();
};
#pragma endregion