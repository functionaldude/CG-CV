#ifndef MATH_FORMATS_INCLUDED
#define MATH_FORMATS_INCLUDED

#pragma once

#include "vector.h"
#include "color.h"

struct Vertex
{
  float3 p;

  Vertex() {}

  Vertex(const float3& position)
  : p(position)
  {
  }
};

/*
struct Triangle
{
  float3 v0;
  float3 v1;
  float3 v2;

  float3 n0;
  float3 n1;
  float3 n2;

  float2 texture0;
  float2 texture1;
  float2 texture2;

  float4 color;
  unsigned int materialIndex;

//  Vertex normal;
//  float d;

  Triangle() {}

  // TODO

  Triangle(const float3& v0, const float3& v1, const float3& v2, const float4& color)
    : v0(v0), v1(v1), v2(v2), color(color)
    {

    }

  Triangle(const float3& v0, const float3& v1, const float3& v2, const float4& color, const float3& n0,
      const float3& n1, const float3& n2, const float2& texture0, const float2& texture1, const float2& texture2, const unsigned matIndex)
  : v0(v0), v1(v1), v2(v2), color(color), n0(n0), n1(n1), n2(n2), texture0(texture0), texture1(texture1), texture2(texture2), materialIndex(matIndex)
  {

  }
};*/

struct Pointlight
{
  float3 pos;

  float3 color;

  Pointlight(const float3& pos, const float3& color)
  : pos(pos), color(color)
  {

  }

};

struct Line
{

  Vertex v0;
  Vertex v1;
  R8G8B8A8 color;

  Line() {}

  Line(Vertex a, Vertex b, R8G8B8A8 c)
  : v0(a), v1(b), color(c)
  {

  }

};

struct Sphere
{
  Vertex position;
  float radius;
  float4 color;

  int id;
  bool joint;

  Sphere() {}

  Sphere(Vertex p, float r, const float4& color, int id)
  : position(p), radius(r), color(color), id(id), joint(false)
  {

  }

  Sphere(Vertex p, float r, const float4& color, int id, bool joint)
  : position(p), radius(r), color(color), id(id), joint(joint)
  {

  }

  Sphere(Vertex p, float r, const float4& color)
  : position(p), radius(r), color(color), id(0), joint(false)
  {

  }

};

#endif
