

#ifndef INCLUDED_MATH_VECTOR
#define INCLUDED_MATH_VECTOR

#pragma once

#include "cgmath.h"

namespace math
{
  template <typename T, unsigned int D>
  class vector;

  template <typename T>
  class vector<T, 2U>
  {
  public:
    static const unsigned int dim = 2U;
    typedef T value_type;

    T x;
    T y;

    vector() {}

    explicit vector(T a)
        : x(a), y(a)
    {
    }

    vector(T x, T y)
        : x(x), y(y)
    {
    }

    template <typename U>
    vector(U x, U y)
        : x(static_cast<T>(x)), y(static_cast<T>(y))
    {
    }

    template <typename U>
    vector(const vector<U, 2U>& v)
        : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {
    }

    T operator()(size_t i) const { return (&x)[i]; }
    T& operator()(size_t i) { return (&x)[i]; }

    vector operator-() const
    {
      return vector(-x, -y);
    }

    vector& operator+=(const vector& v)
    {
      x += v.x;
      y += v.y;
      return *this;
    }

    vector& operator-=(const vector& v)
    {
      x -= v.x;
      y -= v.y;
      return *this;
    }

    vector& operator*=(T a)
    {
      x *= a;
      y *= a;
      return *this;
    }

    vector& operator*=(const vector& v)
    {
      x *= v.x;
      y *= v.y;
      return *this;
    }

    vector& normalize()
    {
      T nrm = rcp(length(*this));
      x *= nrm;
      y *= nrm;
      return *this;
    }

    friend inline const vector operator+(const vector& a, const vector& b)
    {
      return vector(a.x + b.x, a.y + b.y);
    }

    friend inline const vector operator-(const vector& a, const vector& b)
    {
      return vector(a.x - b.x, a.y - b.y);
    }

    friend inline const vector operator*(T a, const vector& v)
    {
      return vector(a * v.x, a * v.y);
    }

    friend inline const vector operator*(const vector& v, T a)
    {
      return a * v;
    }

    friend inline const vector operator*(const vector& a, const vector& b)
    {
      return vector(a.x * b.x, a.y * b.y);
    }

    friend inline bool operator==(const vector& a, const vector& b)
    {
      return a.x == b.x && a.y == b.y;
    }

    friend inline const vector abs(const vector& v)
    {
      return vector(abs(v.x), abs(v.y));
    }

    friend inline T dot(const vector& a, const vector& b)
    {
      return a.x * b.x + a.y * b.y;
    }

    friend inline const vector clamp(const vector& v, T lower = 0, T upper = 1)
    {
      return vector(v.x < lower ? lower : v.x > upper ? upper : v.x,
                    v.y < lower ? lower : v.y > upper ? upper : v.y);
    }
  };

  template <typename T>
  class vector<T, 3U>
  {
  public:
    static const unsigned int dim = 3U;
    typedef T value_type;

    T x;
    T y;
    T z;

    vector() {}

    explicit vector(T a)
        : x(a), y(a), z(a)
    {
    }

    vector(T x, T y, T z)
        : x(x), y(y), z(z)
    {
    }

    template <typename U>
    vector(const vector<U, 3U>& v)
        : x(v.x), y(v.y), z(v.z)
    {
    }

    template <typename U>
    vector(const vector<U, 2U>& v, T z)
        : x(v.x), y(v.y), z(z)
    {
    }

    template <typename U>
    vector(T x, const vector<U, 2U>& v)
        : x(x), y(v.x), z(v.y)
    {
    }

    T operator()(size_t i) const { return (&x)[i]; }
    T& operator()(size_t i) { return (&x)[i]; }

    vector operator-() const
    {
      return vector(-x, -y, -z);
    }

    vector& operator+=(const vector& v)
    {
      x += v.x;
      y += v.y;
      z += v.z;
      return *this;
    }

    vector& operator-=(const vector& v)
    {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      return *this;
    }

    vector& operator*=(T a)
    {
      x *= a;
      y *= a;
      z *= a;
      return *this;
    }

    vector& operator*=(const vector& v)
    {
      x *= v.x;
      y *= v.y;
      z *= v.z;
      return *this;
    }

    vector& normalize()
    {
      T nrm = rcp(length(*this));
      x *= nrm;
      y *= nrm;
      z *= nrm;
      return *this;
    }

    friend inline const vector operator+(const vector& a, const vector& b)
    {
      return vector(a.x + b.x, a.y + b.y, a.z + b.z);
    }

    friend inline const vector operator-(const vector& a, const vector& b)
    {
      return vector(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    friend inline const vector operator*(T a, const vector& v)
    {
      return vector(a * v.x, a * v.y, a * v.z);
    }

    friend inline const vector operator*(const vector& v, T a)
    {
      return a * v;
    }

    friend inline const vector operator*(const vector& a, const vector& b)
    {
      return vector(a.x * b.x, a.y * b.y, a.z * b.z);
    }

    friend inline bool operator==(const vector& a, const vector& b)
    {
      return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    friend inline const vector abs(const vector& v)
    {
      return vector(abs(v.x), abs(v.y), abs(v.z));
    }

    friend inline T dot(const vector& a, const vector& b)
    {
      return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    friend inline vector cross(const vector& a, const vector& b)
    {
      return vector(a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y - a.y * b.x);
    }

    friend inline const vector clamp(const vector& v, T lower = 0, T upper = 1)
    {
      return vector(v.x < lower ? lower : v.x > upper ? upper : v.x,
                    v.y < lower ? lower : v.y > upper ? upper : v.y,
                    v.z < lower ? lower : v.z > upper ? upper : v.z);
    }
  };

  template <typename T>
  class vector<T, 4U>
  {
  public:
    static const unsigned int dim = 4U;
    typedef T value_type;

    T x;
    T y;
    T z;
    T w;

    vector() {}

    explicit vector(T a)
        : x(a), y(a), z(a), w(a)
    {
    }

    vector(T x, T y, T z, T w)
        : x(x), y(y), z(z), w(w)
    {
    }

    template <typename U>
    vector(const vector<U, 4>& v)
        : x(v.x), y(v.y), z(v.z), w(v.w)
    {
    }

    template <typename U>
    vector(const vector<U, 3>& v, T w)
        : x(v.x), y(v.y), z(v.z), w(w)
    {
    }

    template <typename U>
    vector(T x, const vector<U, 3>& v)
        : x(x), y(v.x), z(v.y), w(v.z)
    {
    }

    T operator()(size_t i) const { return (&x)[i]; }
    T& operator()(size_t i) { return (&x)[i]; }

    vector operator-() const
    {
      return vector(-x, -y, -z, -w);
    }

    vector& operator+=(const vector& v)
    {
      x += v.x;
      y += v.y;
      z += v.z;
      w += v.w;
      return *this;
    }

    vector& operator-=(const vector& v)
    {
      x -= v.x;
      y -= v.y;
      z -= v.z;
      w -= v.w;
      return *this;
    }

    vector& operator*=(T a)
    {
      x *= a;
      y *= a;
      z *= a;
      w *= a;
      return *this;
    }

    vector& operator*=(const vector& v)
    {
      x *= v.x;
      y *= v.y;
      z *= v.z;
      w *= v.w;
      return *this;
    }

    vector& normalize()
    {
      T nrm = rcp(length(*this));
      x *= nrm;
      y *= nrm;
      z *= nrm;
      w *= nrm;
      return *this;
    }

    friend inline const vector operator+(const vector& a, const vector& b)
    {
      return vector(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }

    friend inline const vector operator-(const vector& a, const vector& b)
    {
      return vector(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    }

    friend inline const vector operator*(T a, const vector& v)
    {
      return vector(a * v.x, a * v.y, a * v.z, a * v.w);
    }

    friend inline const vector operator*(const vector& v, T a)
    {
      return a * v;
    }

    friend inline const vector operator*(const vector& a, const vector& b)
    {
      return vector(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
    }

    friend inline bool operator==(const vector& a, const vector& b)
    {
      return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
    }

    friend inline const vector abs(const vector& v)
    {
      return vector(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
    }

    friend inline T dot(const vector& a, const vector& b)
    {
      return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    friend inline const vector clamp(const vector& v, T lower = 0, T upper = 1)
    {
      return vector(v.x < lower ? lower : v.x > upper ? upper : v.x,
                    v.y < lower ? lower : v.y > upper ? upper : v.y,
                    v.z < lower ? lower : v.z > upper ? upper : v.z,
                    v.w < lower ? lower : v.w > upper ? upper : v.w);
    }
  };

  template <typename V>
  inline typename V::value_type length(const V& v)
  {
    return sqrt(dot(v, v));
  }

  template <typename V>
  inline V normalize(const V& v)
  {
    return v * rcp(length(v));
  }

  typedef vector<float, 2U> float2;
  typedef vector<float, 3U> float3;
  typedef vector<float, 4U> float4;

  typedef vector<double, 2U> double2;
  typedef vector<double, 3U> double3;
  typedef vector<double, 4U> double4;

  typedef vector<int, 2U> int2;
  typedef vector<int, 3U> int3;
  typedef vector<int, 4U> int4;
}

using math::float2;
using math::float3;
using math::float4;

using math::double2;
using math::double3;
using math::double4;

using math::int2;
using math::int3;
using math::int4;

#endif // INCLUDED_MATH_VECTOR
