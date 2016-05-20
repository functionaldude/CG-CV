


#ifndef COLOR_INCLUDED
#define COLOR_INCLUDED

#pragma once

#include "vector.h"

class R8G8B8A8
{
public:
  typedef unsigned int color_type;
  typedef unsigned char channel_type;

private:
  color_type c;

  static color_type fromRGBA(channel_type r, channel_type g, channel_type b, channel_type a)
  {
    return (a << 24) | (b << 16) | (g << 8) | r;
  }

  static color_type fromRGBAFloat(float r, float g, float b, float a)
  {
    return fromRGBA(static_cast<channel_type>(r * 255.0f),
                    static_cast<channel_type>(g * 255.0f),
                    static_cast<channel_type>(b * 255.0f),
                    static_cast<channel_type>(a * 255.0f));
  }

public:

  R8G8B8A8()
  {
  }

  R8G8B8A8(color_type color)
    : c(color)
  {
  }

  R8G8B8A8(channel_type r, channel_type g, channel_type b, channel_type a = 255)
    : c(fromRGBA(r, g, b, a))
  {
  }

  R8G8B8A8(const int3& v)
    : c(fromRGBA(v.x, v.y, v.z, 255))
  {
  }

  R8G8B8A8(const int4& v)
    : c(fromRGBA(v.x, v.y, v.z, v.w))
  {
  }

  R8G8B8A8(float v)
    : c(fromRGBAFloat(v, v, v, 1.0f))
  {
  }

  R8G8B8A8(const float3& v)
    : c(fromRGBAFloat(v.x, v.y, v.z, 1.0f))
  {
  }

  R8G8B8A8(const float4& v)
    : c(fromRGBAFloat(v.x, v.y, v.z, v.w))
  {
  }

  channel_type r() const { return c & 0xFF; }
  channel_type g() const { return (c >> 8) & 0xFF; }
  channel_type b() const { return (c >> 16) & 0xFF; }
  channel_type a() const { return (c >> 24) & 0xFF; }

  math::float4 toFloat4() const
  {
    return math::float4(r() / 255.f, g() / 255.f, b() / 255.f, a() / 255.f);
  }
};

#endif  // COLOR_INCLUDED
