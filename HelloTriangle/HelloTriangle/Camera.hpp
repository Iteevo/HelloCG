//
//  Camera.hpp
//  HelloTriangle
//
//  Created by dn on 6/10/19.
//  Copyright © 2019 Iteevo. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include "Vector.hpp"
#include "Matrix.hpp"
#define Angle2Radian(degree) { 3.1415 / 180 * degree}
class Camera
{
public:
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    
    //Euler Angles
    float Yaw;
    float Pitch;
    
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    Camera(vec3 position = vec3(0,0,0),vec3 up = vec3(0,1.0f,0),float yaw =-90.0f,float pitch = 0 ):Front(vec3(0,0,-1.0f))//left hand ?
    {
        Position = position;
        WorldUp = up;
        Up = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    
    mat4 GetViewMatrix()
    {
        float dirArray[16] = {
            Right.x,Right.y,Right.z,0,
            Up.x,   Up.y,   Up.z,   0,
            Front.x,    Front.y,    Front.z,0,
            0,  0,  0,  1
        };
        float posArray[16] = {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            -Position.x,-Position.y,-Position.z,1
        };
        mat4 mat1(dirArray);
        mat4 mat2(posArray);
        return mat2 * mat1;
    }
    
    mat4 GetProjection(float fov,float aspect,float near,float far)
    {
        float tanHalfFov = tan(fov/2 * Pi / 180.0);
        float mat[16] =
        {
            1.0f / (aspect * tanHalfFov), 0,  0,  0,
            0,                          1.0f/tanHalfFov, 0,0,
            0,0,    -(near + far) / (far - near), - 2 * far * near / far - near,
            0,0,-1,0
        };
        return mat4(mat).Transposed();
    }
    
private:
    void updateCameraVectors()
    {
       // vec3 front;
       // front.x = cos(Pi /180 * Yaw);
      //  front.y = sin(Pi / 180 * Pitch);
      //  front.z = sin(Pi /180 * Yaw) * cos(Pi / 180 * Pitch);
       // front.z = sin(Angle2Radian(Yaw)) * cos(Angle2Radian(Pitch));
       // Front = front.Normalized();
        
       // Up    = Front.Cross(WorldUp).Normalized();
        Right = WorldUp.Cross(Front).Normalized();
    }
};

#endif /* Camera_hpp */
