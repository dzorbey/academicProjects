#include "sphere.h"
#include <cmath>
using namespace std;

// The magic number
const double Pi = 3.1415926535897932384626433832795;

Sphere::Sphere(float rad, int st, int sl, float shade,
               float x, float y, float z)
 : rad(rad), stacks(st), slices(sl), dl_handle(0), shade(shade),
   xp(x), yp(y), zp(z), dxp(0.0), dyp(0.0), dzp(0.0),
   xr(0.0), yr(0.0), zr(0.0), dxr(0.0), dyr(0.0), dzr(0.0)
{
    ConstructDisplayList();
}
/*
Sphere::Sphere(const Sphere& s)
 : rad(s.rad), stacks(s.stacks), slices(s.slices),
   dl_handle(s.dl_handle), shade(s.shade),
   xp(s.xp), yp(s.yp), zp(s.zp), dxp(s.dxp), dyp(s.dyp), dzp(s.dzp),
   xr(s.xr), yr(s.yr), zr(s.zr), dxr(s.dxr), dyr(s.dyr), dzr(s.dzr)
{
    ConstructDisplayList();
}


Sphere& Sphere::operator=(const Sphere& rhs)
{
    *this = Sphere(rhs);
}
*/
Sphere::~Sphere()
{
    DeleteDisplayList();
}

void Sphere::ConstructDisplayList()
{
    // Delete the old list
    DeleteDisplayList();

    // Create a new list name
    dl_handle = glGenLists(1);
    if(!glIsList(dl_handle))
    {
        allegro_message("Fatal error: Could not create a display list!");
        exit(1);
    }

    // Make sure stacks and slices are at reasonable values
    stacks = MAX(2, stacks);
    slices = MAX(3, slices);

    // Precalculate some needed information
    double stack_angle = Pi / 2 + (Pi / stacks);
    double stack_angle_step = -(Pi / stacks);
    double stack_height = 0.0;
    double stack_height_next = 0.0;
    double stack_width = 0.0;
    double stack_width_next = 0.0;
    double slice_angle = 0.0;
    double slice_angle_step = -((Pi * 2) / slices);

    // Compile the display list
    glNewList(dl_handle, GL_COMPILE);
        for(int i = 0; i < stacks; i++)
        {
            stack_angle += stack_angle_step;
            stack_height = sin(stack_angle);
            stack_width = cos(stack_angle);
            stack_height_next = sin(stack_angle + stack_angle_step);
            stack_width_next = cos(stack_angle + stack_angle_step);
            glBegin(GL_QUAD_STRIP);
                glColor3f(1.0, 0.0, 0.0);
                for(int j = 0; j < slices + 1; j++)
                {
                    slice_angle += slice_angle_step;
                    glNormal3d(cos(slice_angle) * stack_width,
                               stack_height,
                               sin(slice_angle) * stack_width);
                    glVertex3d(cos(slice_angle) * rad * stack_width,
                               stack_height * rad,
                               sin(slice_angle) * rad * stack_width);
                    glNormal3d(cos(slice_angle) * stack_width_next,
                               stack_height_next,
                               sin(slice_angle) * stack_width_next);
                    glVertex3d(cos(slice_angle) * rad * stack_width_next,
                               stack_height_next * rad,
                               sin(slice_angle) * rad * stack_width_next);
                }
            glEnd();
        }
    glEndList();
}

void Sphere::DeleteDisplayList()
{
    if(glIsList(dl_handle))
        glDeleteLists(dl_handle, 1);
}

void Sphere::Update()
{
    xp += dxp; yp += dyp; zp += dzp;
    xr += dxr; yr += dyr; zr += dzr;
}


void Sphere::Update2()
{
    if(key[KEY_8])     xp += 0.3;
    if(key[KEY_5])   xp -= 0.3;
    if(key[KEY_4])   yp += 0.3;
    if(key[KEY_6])  yp -= 0.3;
    if(key[KEY_1])      zp += 0.3;
    if(key[KEY_2])      zp -= 0.3;


}





void Sphere::Render()
{
    glPushMatrix();
    glTranslatef(xp, yp, zp);
    glRotatef(xr, 1.0, 0.0, 0.0);
    glRotatef(yr, 0.0, 1.0, 0.0);
    glRotatef(zr, 0.0, 0.0, 1.0);
    glCallList(dl_handle);
    glPopMatrix();
}
