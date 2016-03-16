#include <cmath>
#include <iostream>

#include "Scene1a.h"
#include "surface.h"


//******************************************************************************************************************************************************************
//TODO Implement this function                                                                         
// 1. setup camera parameters as described in the document                                              
// 2. loop over every pixel, find the intersection                                                      
// 3. store the result of distance in the output image as long as the intersection was successfull      
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//useful functions:
//
// image.width() / image.height() -- gets the width/height of an image
// normalize(float3)              -- function for normalizing vectors
// cross(float3,float3)           -- calculates the cross product of 2 vectors
//
// scene.intersectWithRay(ray, distance)     -- use this function for intersection tests
//  in Ray ray                               -- this variable should contain the ray for intersection testing
//  out float distance                       -- this variable will contain the ray parameter for the point of intersection (use this to color your output_image)
//  return bool                              -- is true if an intersection happened
//******************************************************************************************************************************************************************
void render(const Scene1a& scene, surface<float>& output_image, float w_s, float f)
{
    std::cout<< "Rendering started. "<<std::endl;
    
    // TODO implement this function
    
    int r_x = output_image.width();
    int r_y = output_image.height();
    
    for (int y = 0; y < r_y; y++)
    {
        for (int x = 0; x < r_x; x++)
        {
            output_image(x, y) = (x + y) / static_cast<float>(r_x + r_y);
        }
    }
}

//******************************************************************************************************************************************************************
//TODO Implement this function                                                                         
// 1. calculate the intersection with a sphere according to the document
// 2. if the ray intersects the sphere, write the ray parameter for the 
//    closest point of intersection into t and return true,
//    otherwise return false.
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// useful functions:
//
//  dot(float3,float3)             -- calculates the dot product of two vectors
//  std::sqrt(float)               -- calculates the square root of a number
//******************************************************************************************************************************************************************
bool intersectRaySphere(const float3& p, const float3& d, const float3& c, float r, float& t)
{
    // TODO implement this function
    
    return false;
}


//******************************************************************************************************************************************************************
//TODO Bonus task: implement this function
// 1. calculate the intersection with a plane according to the document
// 2. if the ray intersects the plane in a single point, write the ray
//    parameter for that point into t and return true,
//    otherwise return false.
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// useful functions:
//
//  dot(float3,float3)             -- calculates the dot product of two vectors
//******************************************************************************************************************************************************************
bool intersectRayPlane(const float3& p, const float3& d, const float3& p_0, const float3& n, float& t)
{
    // TODO implement this function
    
    return false;
}
