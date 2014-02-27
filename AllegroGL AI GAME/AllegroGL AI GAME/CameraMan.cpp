#include <allegro.h>
#include <alleggl.h>
#include <cmath>

//const double Deg2Rad = 0.0174532925199432957692369076848861;


// The texture handle
//GLuint Tex;


class CameraMan
{
private:
    float x, y, z;              // Position in world
    float yaw, pitch, roll;     // Rotations

    static const float StandingHeight = 3.0;
    static const float CrouchingHeight = 1.5;

public:
    CameraMan()
     : x(10.0), y(StandingHeight), z(12.0),
       yaw(0.0), pitch(0.0), roll(0.0) {}
    ~CameraMan() {}

    // Walk forwards or backwards by d
    void Walk(float d)
    {
        float nyaw = (-yaw - 90.0) * Deg2Rad;
        x += cos(nyaw) * d;
        z += sin(nyaw) * d;
    }
    // Sidestep left or right by d
    void Sidestep(float d)
    {
        float nyaw = -yaw * Deg2Rad;
        x += cos(nyaw) * d;
        z += sin(nyaw) * d;
    }
    // Crouch at the speed of d
    void Crouch(float d)
    {
        if(y > CrouchingHeight) y -= d;
        if(y < CrouchingHeight) y = CrouchingHeight;
    }
    // Adjust rotations at a certain speed
    void Yaw(float d)   { yaw += d; }
    void Pitch(float d) { pitch += d; }
    void Roll(float d)  { roll += d; }

    // Update the CameraMan for one logic frame
    void Update()
    {
        // Move roll, pitch, and height towards default values
        roll *= 0.98;
        pitch *= 0.98;
        if(y < StandingHeight)  y += 0.05;
    }

    // Apply CameraMan's transformations to the 3D world
    void ApplyTransformations()
    {
        glRotatef(-pitch, 1.0, 0.0, 0.0);
        glRotatef(-roll, 0.0, 0.0, 1.0);
        glRotatef(-yaw, 0.0, 1.0, 0.0);
        glTranslatef(-x, -y, -z);
    }
  
    
};

