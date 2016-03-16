#include "Camera.h"

Camera::Camera(const float3 & eye, const float3 & up,
  const float3 & look_at, float focal_length, float image_plane_width)
  : eye(eye)
  , up(up)
  , look_at(look_at)
  , focal_length(focal_length)
  , image_plane_width(image_plane_width)
{
}

Camera::~Camera()
{
}
