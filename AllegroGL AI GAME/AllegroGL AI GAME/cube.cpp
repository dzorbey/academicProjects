#include "cube.h"

const float Cube::Vertices[8][3] = 
{
    { -0.5,  0.5,  0.5 },
    { -0.5, -0.5,  0.5 },
    {  0.5, -0.5,  0.5 },
    {  0.5,  0.5,  0.5 },
    { -0.5,  0.5, -0.5 },
    { -0.5, -0.5, -0.5 },
    {  0.5, -0.5, -0.5 },
    {  0.5,  0.5, -0.5 }
};

const int Cube::Indices[6][4] = 
{
    { 0, 1, 2, 3 },    
    { 7, 6, 5, 4 },    
    { 3, 2, 6, 7 },    
    { 1, 0, 4, 5 },    
    { 0, 3, 7, 4 },    
    { 5, 6, 2, 1 }    
};
    
const float Cube::Colors[6][3] = 
{
    { 1.0, 0.0, 0.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, 0.0, 1.0 },
    { 1.0, 1.0, 0.0 },
    { 0.0, 1.0, 1.0 },
    { 1.0, 0.0, 1.0 }
};

Cube::Cube(float x, float y, float z, float side_length)
     : sl(side_length), x(x), y(y), z(z), xrot(0.0), yrot(0.0), zrot(0.0)
{
}

void Cube::Update()
{
    if(key[KEY_UP])     xrot += 2.0;
    if(key[KEY_DOWN])   xrot -= 2.0;
    if(key[KEY_A])   yrot += 10.0;
    if(key[KEY_D])  yrot -= 10.0;
    if(key[KEY_Z])      zrot += 2.0;
    if(key[KEY_X])      zrot -= 2.0;
}


void Cube::Update2()
{
    if(key[KEY_K])     x += 0.3;
    if(key[KEY_H])   x -= 0.3;
    if(key[KEY_U])   y += 0.3;
    if(key[KEY_J])  y -= 0.3;
    if(key[KEY_Z])      z += 0.3;
    if(key[KEY_X])      z -= 0.3;
}


void Cube::Render()
{
     
     
 /*   allegro_gl_set_texture_format(GL_RGB8);
    
    BITMAP* slate_bmp = load_bitmap("slate.bmp", 0);
    SlateTex = allegro_gl_make_texture(slate_bmp);
    destroy_bitmap(slate_bmp);

    glEnable(GL_TEXTURE_2D);
     
    glBindTexture(GL_TEXTURE_2D, SlateTex); 
   */  
    glPushMatrix();
    
    //glLoadIdentity();
    
    glTranslatef(x, y, z);
    glScalef(sl, sl, sl);
    glRotatef(xrot, 1.0, 0.0, 0.0);
    glRotatef(yrot, 0.0, 1.0, 0.0);
    glRotatef(zrot, 0.0, 0.0, 1.0);
 
    //glBindTexture(GL_TEXTURE_2D, main.SlateTex); 
    glBegin(GL_QUADS);
        for(int i = 0; i < 6; i++)
        {
            glColor3fv(Colors[i]);
             glTexCoord2i(0, 1);
            glVertex3fv(Vertices[Indices[i][0]]);
             glTexCoord2i(0, 0);
            glVertex3fv(Vertices[Indices[i][1]]);
             glTexCoord2i(1, 0);
            glVertex3fv(Vertices[Indices[i][2]]);
             glTexCoord2i(1, 1);
            glVertex3fv(Vertices[Indices[i][3]]);
        }
    glEnd();
    glFlush();
    
    glPopMatrix();
}
