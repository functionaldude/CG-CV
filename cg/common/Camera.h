#pragma once

#include "vector.h"

class Camera
{
public:
  float3 eye;
  float3 up;
  float3 look_at;
  float focal_length;
  float image_plane_width;

  Camera(const float3& eye, const float3& up, const float3& look_at, float focal_length, float image_plane_width);
  virtual ~Camera();
};

