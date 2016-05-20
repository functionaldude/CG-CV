


#ifndef INCLUDED_MATH
#define INCLUDED_MATH

#pragma once

#include <cmath>
#include <algorithm>


namespace math
{
  template <typename T>
  struct constants;

  template <>
  struct constants<float>
  {
    static float  one() { return 1.0f; }
    static float zero() { return 0.0f; }
    static float   pi() { return 3.1415926535897932384626434f; }
    static float    e() { return 2.7182818284590452353602875f; }
  };

  template <>
  struct constants<double>
  {
    static double  one() { return 1.0; }
    static double zero() { return 0.0; }
    static double   pi() { return 3.1415926535897932384626434; }
    static double    e() { return 2.7182818284590452353602875; }
  };

  template <>
  struct constants<long double>
  {
    static long double  one() { return 1.0; }
    static long double zero() { return 0.0; }
    static long double   pi() { return 3.1415926535897932384626434; }
    static long double    e() { return 2.7182818284590452353602875; }
  };

  using std::abs;

  using std::exp;
  using std::frexp;
  using std::ldexp;
  using std::log;
  using std::log10;
  using std::modf;

  using std::cos;
  using std::sin;
  using std::tan;
  using std::acos;
  using std::asin;
  using std::atan;
  using std::atan2;
  using std::cosh;
  using std::sinh;
  using std::tanh;

  using std::pow;
  using std::sqrt;

  using std::floor;
  using std::ceil;

  using std::fmod;

  inline float rcp(float v)
  {
    return 1.0f / v;
  }

  inline double rcp(double v)
  {
    return 1.0 / v;
  }

  inline long double rcp(long double v)
  {
    return 1.0 / v;
  }
}

#endif  // INCLUDED_MATH
