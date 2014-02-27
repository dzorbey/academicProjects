#ifndef CUBE_H
#define CUBE_H

#include <alleggl.h>
#include <allegro.h>




class Cube
{
public:
    float sl;
    float x, y, z;
    float xrot, yrot, zrot;
    
    GLuint SlateTex;
    
    static const float Vertices[8][3];
    static const int Indices[6][4];
    static const float Colors[6][3];
    
    Cube(float x, float y, float z, float side_length);
    ~Cube() {}
    
    void Update();
    void Render();
       void Update2();
};

#endif  // CUBE_H       
