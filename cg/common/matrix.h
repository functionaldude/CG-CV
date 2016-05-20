

#ifndef INCLUDED_MATH_MATRIX
#define INCLUDED_MATH_MATRIX

#pragma once

#include "vector.h"

namespace math
{
  template <typename T, unsigned int M, unsigned int N>
  class matrix;

  template <typename T>
  class matrix<T, 2U, 2U>
  {
  public:
    static const unsigned int M = 2U;
    static const unsigned int N = 2U;
    typedef T field_type;

    T _11, _12;
    T _21, _22;

    matrix() = default;

    explicit matrix(T a)
        : _11(a), _12(a), _21(a), _22(a)
    {
    }

    matrix(T m11, T m12, T m21, T m22)
        : _11(m11), _12(m12), _21(m21), _22(m22)
    {
    }

    friend matrix operator*(const matrix& a, const matrix& b)
    {
      return matrix(a._11 * b._11 + a._12 * b._21, a._11 * b._12 + a._12 * b._22, a._21 * b._11 + a._22 * b._21, a._21 * b._12 + a._22 * b._22);
    }

    friend vector<T, 2u> operator*(const matrix& a, const vector<T, 2u>& b)
    {
      return vector<T, 2u>(a._11 * b.x + a._12 * b.y,
                           a._21 * b.x + a._22 * b.y);
    }

    friend matrix operator+(const matrix& a, const matrix& b)
    {
      return matrix(a._11 + b._11, a._12 + b._12, a._21 + b._21, a._22 + b._22);
    }

    friend matrix operator*(T f, const matrix& m)
    {
      return matrix(f * m._11, f * m._12, f * m._21, f * m._22);
    }

    friend matrix operator*(const matrix& m, T f)
    {
      return f * m;
    }
  };

  template <typename T>
  class matrix<T, 3U, 3U>
  {
  public:
    static const unsigned int M = 3U;
    static const unsigned int N = 3U;
    typedef T field_type;

    T _11, _12, _13;
    T _21, _22, _23;
    T _31, _32, _33;

    matrix() = default;

    explicit matrix(T a)
        : _11(a), _12(a), _13(a), _21(a), _22(a), _23(a), _31(a), _32(a), _33(a)
    {
    }

    matrix(T m11, T m12, T m13, T m21, T m22, T m23, T m31, T m32, T m33)
        : _11(m11), _12(m12), _13(m13), _21(m21), _22(m22), _23(m23), _31(m31), _32(m32), _33(m33)
    {
    }

    friend matrix transpose(const matrix& m)
    {
      return matrix(m._11, m._21, m._31, m._12, m._22, m._32, m._13, m._23, m._33);
    }

    friend T determinant(const matrix& m)
    {
      return m._11 * m._22 * m._33 + m._12 * m._23 * m._31 + m._13 * m._21 * m._32 - m._13 * m._22 * m._31 - m._12 * m._21 * m._33 - m._11 * m._23 * m._32;
    }

    friend matrix operator+(const matrix& a, const matrix& b)
    {
      return matrix(a._11 + b._11, a._12 + b._12, a._13 + b._13, a._21 + b._21, a._22 + b._22, a._23 + b._23, a._31 + b._31, a._32 + b._32, a._33 + b._33);
    }

    friend matrix operator*(float f, const matrix& m)
    {
      return matrix(f * m._11, f * m._12, f * m._13, f * m._21, f * m._22, f * m._23, f * m._31, f * m._32, f * m._33);
    }

    friend matrix operator*(const matrix& m, float f)
    {
      return f * m;
    }

    friend matrix operator*(const matrix& a, const matrix& b)
    {
      return matrix(a._11 * b._11 + a._12 * b._21 + a._13 * b._31, a._11 * b._12 + a._12 * b._22 + a._13 * b._32, a._11 * b._13 + a._12 * b._23 + a._13 * b._33, a._21 * b._11 + a._22 * b._21 + a._23 * b._31, a._21 * b._12 + a._22 * b._22 + a._23 * b._32, a._21 * b._13 + a._22 * b._23 + a._23 * b._33, a._31 * b._11 + a._32 * b._21 + a._33 * b._31, a._31 * b._12 + a._32 * b._22 + a._33 * b._32, a._31 * b._13 + a._32 * b._23 + a._33 * b._33);
    }

    friend vector<T, 3U> operator*(const vector<T, 3U>& v, const matrix& m)
    {
      return vector<T, 3U>(v.x * m._11 + v.y * m._21 + v.z * m._31,
                           v.x * m._12 + v.y * m._22 + v.z * m._32,
                           v.x * m._13 + v.y * m._23 + v.z * m._33);
    }

    friend vector<T, 3U> operator*(const matrix& m, const vector<T, 3U>& v)
    {
      return vector<T, 3U>(m._11 * v.x + m._12 * v.y + m._13 * v.z,
                           m._21 * v.x + m._22 * v.y + m._23 * v.z,
                           m._31 * v.x + m._32 * v.y + m._33 * v.z);
    }
  };

  template <typename T>
  class matrix<T, 3U, 4U>
  {
  public:
    static const unsigned int M = 3U;
    static const unsigned int N = 4U;
    typedef T field_type;

    T _11, _12, _13, _14;
    T _21, _22, _23, _24;
    T _31, _32, _33, _34;

    matrix() = default;

    explicit matrix(T a)
        : _11(a), _12(a), _13(a), _14(a), _21(a), _22(a), _23(a), _24(a), _31(a), _32(a), _33(a), _34(a)
    {
    }

    matrix(T m11, T m12, T m13, T m14, T m21, T m22, T m23, T m24, T m31, T m32, T m33, T m34)
        : _11(m11), _12(m12), _13(m13), _14(m14), _21(m21), _22(m22), _23(m23), _24(m24), _31(m31), _32(m32), _33(m33), _34(m34)
    {
    }

    friend matrix<T, 4U, 3U> transpose(const matrix& m)
    {
      return matrix<T, 4U, 3U>(m._11, m._21, m._31, m._12, m._22, m._32, m._13, m._23, m._33, m._14, m._24, m._34);
    }

    friend matrix operator+(const matrix& a, const matrix& b)
    {
      return matrix(a._11 + b._11, a._12 + b._12, a._13 + b._13, a._14 + b._14, a._21 + b._21, a._22 + b._22, a._23 + b._23, a._24 + b._24, a._31 + b._31, a._32 + b._32, a._33 + b._33, a._34 + b._34);
    }

    friend matrix operator*(float f, const matrix& m)
    {
      return matrix(f * m._11, f * m._12, f * m._13, f * m._14, f * m._21, f * m._22, f * m._23, f * m._24, f * m._31, f * m._32, f * m._33, f * m._34);
    }

    friend matrix operator*(const matrix& m, float f)
    {
      return f * m;
    }

    friend vector<T, 4U> operator*(const vector<T, 3U>& v, const matrix& m)
    {
      return vector<T, 4U>(v.x * m._11 + v.y * m._21 + v.z * m._31,
                           v.x * m._12 + v.y * m._22 + v.z * m._32,
                           v.x * m._13 + v.y * m._23 + v.z * m._33,
                           v.x * m._14 + v.y * m._24 + v.z * m._34);
    }

    friend vector<T, 3U> operator*(const matrix& m, const vector<T, 4>& v)
    {
      return vector<T, 3U>(m._11 * v.x + m._12 * v.y + m._13 * v.z + m._14 * v.w,
                           m._21 * v.x + m._22 * v.y + m._23 * v.z + m._24 * v.w,
                           m._31 * v.x + m._32 * v.y + m._33 * v.z + m._34 * v.w);
    }
  };

  template <class T>
  class matrix<T, 4, 4>
  {
  public:
    static const unsigned int m = 4;
    static const unsigned int n = 4;
    typedef T value_type;

    T _11, _21, _31, _41;
    T _12, _22, _32, _42;
    T _13, _23, _33, _43;
    T _14, _24, _34, _44;

    matrix() = default;

    explicit matrix(T a)
        : _11(a), _12(a), _13(a), _14(a), _21(a), _22(a), _23(a), _24(a), _31(a), _32(a), _33(a), _34(a), _41(a), _42(a), _43(a), _44(a)
    {
    }

    matrix(T m11, T m12, T m13, T m14, T m21, T m22, T m23, T m24, T m31, T m32, T m33, T m34, T m41, T m42, T m43, T m44)
        : _11(m11), _12(m12), _13(m13), _14(m14), _21(m21), _22(m22), _23(m23), _24(m24), _31(m31), _32(m32), _33(m33), _34(m34), _41(m41), _42(m42), _43(m43), _44(m44)
    {
    }

    friend matrix transpose(const matrix& m)
    {
      return matrix(m._11, m._21, m._31, m._41, m._12, m._22, m._32, m._42, m._13, m._23, m._33, m._43, m._14, m._24, m._34, m._44);
    }

    friend matrix operator+(const matrix& a, const matrix& b)
    {
      return matrix(a._11 + b._11, a._12 + b._12, a._13 + b._13, a._14 + b._14, a._21 + b._21, a._22 + b._22, a._23 + b._23, a._24 + b._24, a._31 + b._31, a._32 + b._32, a._33 + b._33, a._34 + b._34, a._41 + b._41, a._42 + b._42, a._43 + b._43, a._44 + b._44);
    }

    friend matrix operator*(float f, const matrix& m)
    {
      return matrix(f * m._11, f * m._12, f * m._13, f * m._14, f * m._21, f * m._22, f * m._23, f * m._24, f * m._31, f * m._32, f * m._33, f * m._34, f * m._41, f * m._42, f * m._43, f * m._44);
    }

    friend matrix operator*(const matrix& m, float f)
    {
      return f * m;
    }

    friend matrix operator*(const matrix& a, const matrix& b)
    {
      return matrix(a._11 * b._11 + a._12 * b._21 + a._13 * b._31 + a._14 * b._41, a._11 * b._12 + a._12 * b._22 + a._13 * b._32 + a._14 * b._42, a._11 * b._13 + a._12 * b._23 + a._13 * b._33 + a._14 * b._43, a._11 * b._14 + a._12 * b._24 + a._13 * b._34 + a._14 * b._44, a._21 * b._11 + a._22 * b._21 + a._23 * b._31 + a._24 * b._41, a._21 * b._12 + a._22 * b._22 + a._23 * b._32 + a._24 * b._42, a._21 * b._13 + a._22 * b._23 + a._23 * b._33 + a._24 * b._43, a._21 * b._14 + a._22 * b._24 + a._23 * b._34 + a._24 * b._44, a._31 * b._11 + a._32 * b._21 + a._33 * b._31 + a._34 * b._41, a._31 * b._12 + a._32 * b._22 + a._33 * b._32 + a._34 * b._42, a._31 * b._13 + a._32 * b._23 + a._33 * b._33 + a._34 * b._43, a._31 * b._14 + a._32 * b._24 + a._33 * b._34 + a._34 * b._44, a._41 * b._11 + a._42 * b._21 + a._43 * b._31 + a._44 * b._41, a._41 * b._12 + a._42 * b._22 + a._43 * b._32 + a._44 * b._42, a._41 * b._13 + a._42 * b._23 + a._43 * b._33 + a._44 * b._43, a._41 * b._14 + a._42 * b._24 + a._43 * b._34 + a._44 * b._44);
    }

    template <class U>
    friend vector<U, 4> operator*(const vector<U, 4>& v, const matrix& m)
    {
      return vector<U, 4>(v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41,
                          v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42,
                          v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43,
                          v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44);
    }

    template <class U>
    friend vector<U, 4> operator*(const matrix& m, const vector<U, 4>& v)
    {
      return vector<U, 4>(m._11 * v.x + m._12 * v.y + m._13 * v.z + m._14 * v.w,
                          m._21 * v.x + m._22 * v.y + m._23 * v.z + m._24 * v.w,
                          m._31 * v.x + m._32 * v.y + m._33 * v.z + m._34 * v.w,
                          m._41 * v.x + m._42 * v.y + m._43 * v.z + m._44 * v.w);
    }
  };

  template <typename T>
  inline T det(const matrix<T, 2U, 2U>& m)
  {
    return m._11 * m._22 - m._21 * m._12;
  }

  template <typename T>
  inline T det(const matrix<T, 3U, 3U>& m)
  {
    return m._11 * det(matrix<T, 2U, 2U>(m._22, m._23, m._32, m._33)) -
           m._12 * det(matrix<T, 2U, 2U>(m._21, m._23, m._31, m._33)) +
           m._13 * det(matrix<T, 2U, 2U>(m._21, m._22, m._31, m._32));
  }

  template <typename T>
  inline T det(const matrix<T, 4U, 4U>& m)
  {
    return m._11 * det(matrix<T, 3U, 3U>(m._22, m._23, m._24, m._32, m._33, m._34, m._42, m._43, m._44)) -
           m._12 * det(matrix<T, 3U, 3U>(m._21, m._23, m._24, m._31, m._33, m._34, m._41, m._43, m._44)) +
           m._13 * det(matrix<T, 3U, 3U>(m._21, m._22, m._24, m._31, m._32, m._34, m._41, m._42, m._44)) -
           m._14 * det(matrix<T, 3U, 3U>(m._21, m._22, m._23, m._31, m._32, m._33, m._41, m._42, m._43));
  }

  template <typename T>
  inline matrix<T, 3U, 3U> adj(const matrix<T, 3U, 3U>& m)
  {
    return transpose(matrix<T, 3U, 3U>(
        det(matrix<T, 2U, 2U>(m._22, m._23, m._32, m._33)),
        -det(matrix<T, 2U, 2U>(m._21, m._23, m._31, m._33)),
        det(matrix<T, 2U, 2U>(m._21, m._22, m._31, m._32)),

        -det(matrix<T, 2U, 2U>(m._12, m._13, m._32, m._33)),
        det(matrix<T, 2U, 2U>(m._11, m._13, m._31, m._33)),
        -det(matrix<T, 2U, 2U>(m._11, m._12, m._31, m._32)),

        det(matrix<T, 2U, 2U>(m._12, m._13, m._22, m._23)),
        -det(matrix<T, 2U, 2U>(m._11, m._13, m._21, m._23)),
        det(matrix<T, 2U, 2U>(m._11, m._12, m._21, m._22))));
  }

  template <typename T>
  inline matrix<T, 4U, 4U> adj(const matrix<T, 4U, 4U>& m)
  {
    return transpose(matrix<T, 4U, 4U>(
        det(matrix<T, 3U, 3U>(m._22, m._23, m._24, m._32, m._33, m._34, m._42, m._43, m._44)),
        -det(matrix<T, 3U, 3U>(m._21, m._23, m._24, m._31, m._33, m._34, m._41, m._43, m._44)),
        det(matrix<T, 3U, 3U>(m._21, m._22, m._24, m._31, m._32, m._34, m._41, m._42, m._44)),
        -det(matrix<T, 3U, 3U>(m._21, m._22, m._23, m._31, m._32, m._33, m._41, m._42, m._43)),

        -det(matrix<T, 3U, 3U>(m._12, m._13, m._14, m._32, m._33, m._34, m._42, m._43, m._44)),
        det(matrix<T, 3U, 3U>(m._11, m._13, m._14, m._31, m._33, m._34, m._41, m._43, m._44)),
        -det(matrix<T, 3U, 3U>(m._11, m._12, m._14, m._31, m._32, m._34, m._41, m._42, m._44)),
        det(matrix<T, 3U, 3U>(m._11, m._12, m._13, m._31, m._32, m._33, m._41, m._42, m._43)),

        det(matrix<T, 3U, 3U>(m._12, m._13, m._14, m._22, m._23, m._24, m._42, m._43, m._44)),
        -det(matrix<T, 3U, 3U>(m._11, m._13, m._14, m._21, m._23, m._24, m._41, m._43, m._44)),
        det(matrix<T, 3U, 3U>(m._11, m._12, m._14, m._21, m._22, m._24, m._41, m._42, m._44)),
        -det(matrix<T, 3U, 3U>(m._11, m._12, m._13, m._21, m._22, m._23, m._41, m._42, m._43)),

        -det(matrix<T, 3U, 3U>(m._12, m._13, m._14, m._22, m._23, m._24, m._32, m._33, m._34)),
        det(matrix<T, 3U, 3U>(m._11, m._13, m._14, m._21, m._23, m._24, m._31, m._33, m._34)),
        -det(matrix<T, 3U, 3U>(m._11, m._12, m._14, m._21, m._22, m._24, m._31, m._32, m._34)),
        det(matrix<T, 3U, 3U>(m._11, m._12, m._13, m._21, m._22, m._23, m._31, m._32, m._33))));
  }

  template <typename T, unsigned int N>
  inline matrix<T, N, N> inverse(const matrix<T, N, N>& M)
  {
    // TODO: optimize; compute det using adj
    return rcp(det(M)) * adj(M);
  }

  typedef matrix<float, 2U, 2U> float2x2;
  typedef matrix<float, 3U, 3U> float3x3;
  typedef matrix<float, 3U, 4U> float3x4;
  typedef matrix<float, 4U, 4U> float4x4;

  template <typename T>
  T identity();

  template <>
  inline float2x2 identity<float2x2>()
  {
    return float2x2(1.0f, 0.0f, 0.0f, 1.0f);
  }

  template <>
  inline float3x3 identity<float3x3>()
  {
    return float3x3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  }

  template <>
  inline float4x4 identity<float4x4>()
  {
    return float4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
  }
}

using math::float2x2;
using math::float3x3;
using math::float3x4;
using math::float4x4;

#endif // INCLUDED_MATH_MATRIX
