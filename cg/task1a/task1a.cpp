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

    float r_x = (float)output_image.width();
    float r_y = (float)output_image.height();

    float ratio = r_x / r_y;
    float h_s = w_s / ratio;

    float offset_w = w_s /  r_x;
    float offset_h = h_s /  r_y;

    float sp_x = (-w_s / 2.0f) + (offset_w / 2.0f); //start p x
    float sp_y = (h_s / 2.0f)  - (offset_h / 2.0f); //start p y

    for (int y = 0; y < r_y; y++) {
        for (int x = 0; x < r_x; x++) {
            float3 vec(sp_x + (offset_w * x), sp_y - offset_h * y, -f);
            float distance;
            
            if (scene.intersectWithRay(normalize(vec), distance)) {
                output_image(x, y) = distance;
            }
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
    float3 q = p - c;
    double disk = pow(dot(d, q), 2) - (dot(d, d) * (dot(q, q) - pow(r, 2)));
    if (disk < 0) return false;
    t = static_cast<float>((-1 * dot(d,q) - sqrt(disk)) / dot(d,d));
    return true;
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
    float d2 = dot(p_0, n);
    float dn = dot(d,n);
    if (dn == 0) return false;
    t =  ((-dot(p,n) - d2) / dn);
    return true;
}
