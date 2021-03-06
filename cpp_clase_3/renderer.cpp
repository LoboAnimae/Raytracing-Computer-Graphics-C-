#include "classes.h"
#include <iostream>
#include <cmath>
#include <fstream>
#define BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define PI 3.141592653589793

long double maxf(long double arg1, long double arg2)
{
    if (arg1 >= arg2)
        return arg1;
    else
        return arg2;
}

V3 sum(V3 v0, V3 v1)
{
    return V3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}
V3 sub(V3 v0, V3 v1)
{
    return V3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}
V3 mul(V3 v0, long double k)
{
    return V3(v0.x * k, v0.y * k, v0.z * k);
}
long double dot(V3 v0, V3 v1)
{
    return (v0.x * v1.x + v0.y * v1.y + v0.z * v1.z);
}
V3 cross(V3 v0, V3 v1)
{
    return V3(
        v0.y * v1.z - v0.z * v1.y,
        v0.z * v1.x - v0.x * v1.z,
        v0.x * v1.y - v0.y * v1.x);
}
long double length(V3 v0)
{
    return (long double)pow(pow(v0.x, 2) + pow(v0.y, 2) + pow(v0.z, 2), 0.5);
}
V3 norm(V3 v0)
{
    long double v0length = length(v0);

    if (!v0length)
    {
        return V3(0, 0, 0);
    }

    return V3(v0.x / v0length, v0.y / v0length, v0.z / v0length);
}
V3 reflect(V3 I, V3 N)
{
    return norm(sub(I, mul(N, 2 * dot(I, N))));
}

struct returnobject
{
    Material material;
    Intersect intersect;
} returner;

void Renderer::generateBMP(char *imageFileName)
{
    unsigned char finalpixels[height][width][3];
    for (int i = 0, counter = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < 3; k++, counter++)
            {
                finalpixels[i][j][k] = pixels[counter];
            }
        }
    }

    generateBitmapImage((unsigned char *)finalpixels, imageFileName);
}

void Renderer::generateBitmapImage(unsigned char *image, char *imageFileName)
{
    int widthInBytes = width * BYTES_PER_PIXEL;

    unsigned char padding[3] = {0, 0, 0};
    int paddingSize = (4 - (widthInBytes) % 4) % 4;

    int stride = (widthInBytes) + paddingSize;

    FILE *imageFile = fopen(imageFileName, "wb");

    unsigned char *fileHeader = createBitmapFileHeader(height, stride);
    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    unsigned char *infoHeader = createBitmapInfoHeader(height, width);
    fwrite(infoHeader, 1, INFO_HEADER_SIZE, imageFile);

    int i;
    for (i = 0; i < height; i++)
    {
        fwrite(image + (i * widthInBytes), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

unsigned char *Renderer::createBitmapInfoHeader(int height, int width)
{
    static unsigned char infoHeader[] = {
        0, 0, 0, 0, /// header size
        0, 0, 0, 0, /// image width
        0, 0, 0, 0, /// image height
        0, 0,       /// number of color planes
        0, 0,       /// bits per pixel
        0, 0, 0, 0, /// compression
        0, 0, 0, 0, /// image size
        0, 0, 0, 0, /// horizontal resolution
        0, 0, 0, 0, /// vertical resolution
        0, 0, 0, 0, /// colors in color table
        0, 0, 0, 0, /// important color count
    };

    infoHeader[0] = (unsigned char)(INFO_HEADER_SIZE);
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);
    infoHeader[12] = (unsigned char)(1);
    infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL * 8);

    return infoHeader;
}

unsigned char *Renderer::createBitmapFileHeader(int height, int stride)
{
    int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[] = {
        0, 0,       /// signature
        0, 0, 0, 0, /// image file size in bytes
        0, 0, 0, 0, /// reserved
        0, 0, 0, 0, /// start of pixel array
    };

    fileHeader[0] = (unsigned char)('B');
    fileHeader[1] = (unsigned char)('M');
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return fileHeader;
}

Intersect Sphere::ray_intersect(V3 orig, V3 direction)
{
    V3 L = sub(center, orig);
    long double tca = dot(L, direction);
    long double l = length(L);
    double d2 = pow(l, 2) - pow(tca, 2);
    Intersect intersect;
    if (d2 > pow(radius, 2))
    {
        intersect.valid = false;
        return intersect;
    }
    long double thc = sqrtf(pow(radius, 2) - d2);
    long double t0 = tca - thc;
    long double t1 = tca + thc;

    if (t0 < 0)
        t0 = t1;
    if (t0 < 0)
    {
        intersect.valid = false;
        return intersect;
    }

    V3 hit = sum(orig, mul(direction, t0));
    V3 normal = norm(sub(hit, center));

    return Intersect(
        t0,
        hit,
        normal,
        true);
}

bool Renderer::scene_intersect(V3 orig, V3 direction)
{
    long double zbuffer = INFINITY;
    Material material;
    Intersect intersect;
    bool returnstatus = false;

    for (int i = 0; i < sceneSize; i++)
    {
        Intersect hit = scene[i].ray_intersect(orig, direction);
        if (hit.valid)
        {
            if (hit.distance < zbuffer)
            {
                zbuffer = hit.distance;
                material = scene[i].material;
                intersect = hit;
                returnstatus = true;
            }
        }
    }

    returner.material = material;
    returner.material.active = true;
    returner.intersect = intersect;
    returner.intersect.active = true;

    return returnstatus;
}

V3 Renderer::cast_ray(V3 orig, V3 direction)
{
    if (!scene_intersect(orig, direction))
    {
        return V3(255, 255, 255);
    }

    V3 light_dir = norm(sub(light.position, returner.intersect.point));
    long double intensity = light.intensity * maxf(0, dot(light_dir, returner.intersect.normal));
    V3 reflection = reflect(light_dir, returner.intersect.normal);
    long double specular_intensity = light.intensity * (pow(maxf(0, -dot(reflection, direction)), returner.material.spec));
    long double diffuse[3] = {};
    diffuse[0] = (long double)returner.material.diffuse.r * intensity * returner.material.albedo[0];
    diffuse[1] = (long double)returner.material.diffuse.g * intensity * returner.material.albedo[0];
    diffuse[2] = (long double)returner.material.diffuse.b * intensity * returner.material.albedo[0];
    long double specular[3] = {255 * specular_intensity * returner.material.albedo[1], 255 * specular_intensity * returner.material.albedo[1], 255 * specular_intensity * returner.material.albedo[1]};
    V3 resultant((diffuse[0] + specular[0]), (diffuse[1] + specular[1]), (diffuse[2] + specular[2]));
    // std::cout << "x: " << resultant.x << " y: " << resultant.y << " z: " << resultant.z << std::endl;
    return resultant;
}

void Renderer::render()
{
    long double fov = (PI / 2);
    for (int y = 0, counter = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++, counter += 3)
        {
            long double i = (2 * (x + 0.5) / width - 1) * tan(fov / 2) * width / height;
            long double j = (2 * (y + 0.5) / height - 1) * tan(fov / 2);
            V3 direction = norm(V3(i, j, -1));
            V3 color_temp = cast_ray(camera, direction);
            Color color(
                color_temp.x,
                color_temp.y,
                color_temp.z);

            pixels[counter] = (unsigned char)color.b;
            pixels[counter + 1] = (unsigned char)color.g;
            pixels[counter + 2] = (unsigned char)color.r;
        }
    }
}