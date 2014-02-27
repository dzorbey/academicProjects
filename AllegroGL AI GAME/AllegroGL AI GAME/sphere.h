#ifndef SPHERE_H
#define SPHERE_H

#include <alleggl.h>

class Sphere
{
private:
    float rad;
    int stacks, slices;
    GLuint dl_handle;
    float shade;

    void ConstructDisplayList();
    void DeleteDisplayList();

public:
    float xp, yp, zp;
    float dxp, dyp, dzp;
    float xr, yr, zr;
    float dxr, dyr, dzr;

    Sphere(float rad, int st, int sl, float shade,
           float x, float y, float z);
    ~Sphere();

    void Update();
    void Update2();
    void Render();
};

#endif  // SPHERE_H

