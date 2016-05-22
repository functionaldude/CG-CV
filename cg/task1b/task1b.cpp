#include "Scene1b.h"
#include "surface.h"
#include "Ray.h"
#include "Light.h"
#include "Camera.h"
#include "vector.h"
#include "Intersection.h"
#include "Material.h"
#include "BVHTreeNode.h"
#include <iostream>

#define MAX_DEPTH 5
#define BIAS 1e-4f


//******************************************************************************************************************************************************************
//TODO Implement this function                                                                         
//1. setup camera parameters as described in the document for task 1b                                             
//2. store the calculated color in your output imaged
//
//TODO BONUS
// perform antialiasing as described in the document provided
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//useful functions:
//
//normalize(float3)              -- function for normalizing vectors
//cross(float3,float3)           -- calculates the cross product of 2 vectors
//
//cam_eye                        -- position of camera
//cam_look_at                    -- position of lookat point
//cam_up                         -- up-vector of camera
//f                              -- focal length
//w_s                            -- width of the image plane
//
//Ray ray(float3 p_0, float3 dir)              
//use this function to generate a ray from p_0 in direction dir
//  -- in float3 p_0             -- should contain the starting point of a ray
//  -- in float3 dir             -- should contain the direction of a ray
//  -- return Ray ray            -- returns a Ray
//
//scene.traceRay(Ray ray)                      
//use this to trace a Ray
//  -- in Ray                    -- should contain the ray
//  -- return float3 color       -- returns a color
//******************************************************************************************************************************************************************
void render(const Scene1b &scene, surface<R8G8B8A8> &output_image, const float3 &cam_eye, const float3 &cam_up,
            const float3 &cam_look_at, float w_s, float f, int sample_count) {
    std::cout << "Rendering started. " << std::endl;

    float3 w = normalize(cam_eye - cam_look_at);
    float3 u = normalize(cross(cam_up, w));
    float3 v = cross(w, u);

    float r_x = (float) output_image.width();
    float r_y = (float) output_image.height();

    float ratio = r_x / r_y;
    float h_s = w_s / ratio;

    float offset_w = w_s / r_x;
    float offset_h = h_s / r_y;

    float sp_x = (-w_s / 2.0f) + (offset_w / 2.0f); //start p x
    float sp_y = (h_s / 2.0f) - (offset_h / 2.0f); //start p y
    float sp_z = -f;

    for (int y = 0; y < r_y; y++) {
        for (int x = 0; x < r_x; x++) {
            float3 a(sp_z * w);
            float3 b((sp_y - offset_h * y) * v);
            float3 c((sp_x + offset_w * x) * u);

            float3 vec(a + b + c);

            Ray ray(cam_eye, vec.normalize());

            output_image(x, y) = scene.traceRay(ray);
        }
    }

}

//******************************************************************************************************************************************************************
//TODO Implement this function                                                                         
//1. check if an intersection happens                                             
//2. get the material of the scene
//3. check if the material is reflective
//4. check if the depth is smaller than the maximal bounces
//5. calculate the direction of the reflective ray
//6. generate a reflective ray
//7. call traceRay with the new ray and depth and save the result in final_color                                             
//8. if it is not reflective use phong
//9. store the calculated color in final_color
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//useful:
//
//intersection.maerial_index     -- material index for accessing a material from the scene
//scene.materials                -- a vector containing all material of a scene
//MAX_DEPTH                      -- indicates the maximal bounces
//
//scene.intersectRay(Ray ray, Intersection intersect)
//use this function for intersection tests
//  -- in Ray ray                               -- this variable should contain the ray for intersection testing
//  -- out Intersection intersect               -- contains distance * ray
//  -- return bool                              -- is true if an intersection happened
//
//scene.phong(Ray ray, Intersection intersection)
//use this function to calculate the color using phong
//  -- in Ray ray                                    -- this variable should contain the ray
//  -- in Intersection intersect                     -- should contain the intersection
//  -- return float3 color
//******************************************************************************************************************************************************************
float3 reflect(float3 v, float3 n) {
    float3 v_normal = normalize(v);
    float3 n_normal = normalize(n);
    return v_normal - 2 * dot(v_normal, n_normal) * n_normal;
}

float3 traceRay(const Ray &ray, const Scene1b &scene, int depth) {
    Intersection inter;
    if (depth <= MAX_DEPTH && scene.intersectRay(ray, inter)) {
        inter.position += BIAS * inter.normal;
        // intersection found
        if (scene.materials[inter.material_index].reflective) {
            // reflective
            float3 direction = reflect(ray.dir, inter.normal);
            Ray reflectionRay(inter.position, direction);
            return traceRay(reflectionRay, scene, depth + 1);
        } else {
            // nonreflective
            return scene.phong(ray, inter);
        }
    } else {
        // intersection not found
        return float3(0, 0, 0);
    }
}

//******************************************************************************************************************************************************************
//TODO Implement this function                                                                                                                     
//1. get the material of the scene
//2. iterate over all lights
//3. add the ambient color to the final color color
//4. create a ray from the intersection to the light
//5. if intersection was not in the shadow of the light calculate the diffuse and specular color and add it to the final color color
//--------------------------------------------------------------------------------------------------------------------
//useful:
//
//intersection.maerial_index     -- material index for accessing a material from the scene
//scene.materials                -- a vector containing all material of a scene
//scene.lights                   -- a vector containing all lights of a scene
//material.ambient               -- the ambient coefficient of a material
//material.diffuse               -- the diffuse coefficient of a material
//material.specular              -- the specular coefficient of a material
//dot(float3, float3)            -- calculates the dot product of two vectors
//max(float, float)              -- get the maximum of two floats
//******************************************************************************************************************************************************************
float3 phong(const Ray &ray, const Intersection &hit, const Scene1b &scene) {
    float3 color(0.f);

    Material material = scene.materials[hit.material_index];
    for (auto light : scene.lights) {
        float3 lightVec = light->position - hit.position;
        color += light->ambient * material.ambient;

        Intersection inter;
        if (!scene.intersectRay(Ray(hit.position, normalize(lightVec)), inter) || inter.distance > length(lightVec)) {
            // diffuse
            float cosTheta = dot(normalize(lightVec), normalize(hit.normal));
            color += material.diffuse * light->intensities * fmax(cosTheta, 0);

            // specular
            if (cosTheta > 0) {
                float a_r = dot(normalize(ray.dir), normalize(reflect(lightVec, hit.normal)));
                color += material.specular * light->intensities * pow(fmax(a_r, 0), material.shininess);
            }
        }
    }

    return clamp(color);
}


//******************************************************************************************************************************************************************
//TODO Implement this function
//1. if the given node is a leaf node iterate over all triangles
//2. intersect the ray with the triangle
//3. check if the intersection is valid
//4. save your results in intersected_distance, intersected_triangle and intersected_barycentric
//5. if the given node is not a leaf node call intersect for right and left subtree
//6. check if the exists an intersection
//--------------------------------------------------------------------------------------------------------------------
//useful:
//
//BVHTreeNode node               -- node of a BVH tree
//node.triangles                 -- vector of all triangles of a node
//node.left                      -- left subtree of node
//node.right                     -- right subtree of node
//******************************************************************************************************************************************************************
bool intersectRay(const Ray &ray, const BVHTreeNode &node, const Triangle *&intersected_triangle, float &t,
                  float2 &barycentric) {
    /*
    if (!node.triangles.empty())
    {
      for (const Triangle& triangle : node.triangles)
      {
        float inter_dist;
        float2 inter_bary;
        if (triangle.intersectRay(ray, inter_dist, inter_bary))
        {
          t = inter_dist;
          intersected_triangle = &triangle;
          barycentric = inter_bary;
          return true;
        }
      }
    }
    return false;
     */
    if (node.left != nullptr && node.right != nullptr) {
        bool result = false;

        bool hit_left;
        bool hit_right;
        float t_left = 0.0;
        float t_right = 0.0;
        float2 barycentric_left;
        float2 barycentric_right;
        const Triangle *intersected_triangle_left;
        const Triangle *intersected_triangle_right;

        hit_right = node.right->bounds.intersectRay(ray);
        if (hit_right) {
            hit_right = intersectRay(ray, *node.right, intersected_triangle_right, t_right, barycentric_right);
        }
        hit_left = node.left->bounds.intersectRay(ray);
        if (hit_left) {
            hit_left = intersectRay(ray, *node.left, intersected_triangle_left, t_left, barycentric_left);
        }

        if (hit_left && hit_right) {
            if (t_left < t_right) {
                intersected_triangle = intersected_triangle_left;
                t = t_left;
                barycentric = barycentric_left;
            } else {
                intersected_triangle = intersected_triangle_right;
                t = t_right;
                barycentric = barycentric_right;
            }
        } else if (hit_left) {
            intersected_triangle = intersected_triangle_left;
            t = t_left;
            barycentric = barycentric_left;
        } else if (hit_right) {
            intersected_triangle = intersected_triangle_right;
            t = t_right;
            barycentric = barycentric_right;
        }

        return hit_right || hit_left;
    } else {
        bool hit = false;
        for (const Triangle &triangle : node.triangles) {
            float inter_dist;
            float smallest_dist = 0x1.fffffep+127f;
            float2 inter_bary;
            if (triangle.intersectRay(ray, inter_dist, inter_bary)) {
                hit = true;
                if (inter_dist < smallest_dist) {
                    t = inter_dist;
                    smallest_dist = inter_dist;
                    intersected_triangle = &triangle;
                    barycentric = inter_bary;
                }
            }
        }
        return hit;
    }
}
