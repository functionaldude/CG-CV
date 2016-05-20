


#ifndef SURFACE_INCLUDED
#define SURFACE_INCLUDED

#pragma once


#include <algorithm>
#include <cassert>

#include "color.h"

template<typename T>
class surface
{
public:
  typedef T color_type;

private:
  int _width;
  int _height;
  color_type* _data;

public:

  surface()
    : _data(0),
      _width(0),
      _height(0)
  {
  }

  surface(int width, int height)
    : _width(width),
      _height(height),
      _data(new color_type[width * height])
  {
  }

  surface(int width, int height, const color_type& color)
    : _width(width),
      _height(height),
      _data(new color_type[width * height])
  {
    clear(color);
  }

  surface(const surface& s)
    : _width(s._width),
      _height(s._height),
      _data(new color_type[_width * _height])
  {
    std::copy(s._data, s._data + (_width * _height), _data);
  }

  template <typename U>
  surface(const surface<U>& s)
    : _width(s.width()),
      _height(s.height()),
      _data(new color_type[_width * _height])
  {
    std::copy(s.data(), s.data() + (_width * _height), _data);
  }

  surface& operator= (const surface& s)
  {
    _width = s._width;
    _height = s._height;
    delete[] _data;
    _data = new color_type[_width * _height];
    std::copy(s._data, s._data + (_width * _height), _data);
    return *this;
  }

  surface(const char* filename);

  ~surface() { delete[] _data; }

  int width() const { return _width; }
  int height() const { return _height; }

  const color_type* data() const { return _data; }
  color_type* data() { return _data; }

  void clear(const color_type& c = color_type()) const
  {
	  std::fill(_data, _data + (_width * _height), c);
  }

  const T& operator ()(int x, int y) const
  {
#ifdef _DEBUG
    assert(x >= 0 && y >= 0 && x < _width && y < _height);
#endif
    return _data[y*_width + x];
  }

  T& operator ()(int x, int y)
  {
#ifdef _DEBUG
    assert(x >= 0 && y >= 0 && x < _width && y < _height);
#endif
    return _data[y*_width + x];
  }

  const T& operator ()(int2 coord) const
  {
#ifdef _DEBUG
    assert(coord.x >= 0 && coord.y >= 0 && coord.x < _width && coord.y < _height);
#endif
    return _data[coord.y*_width + coord.x];
  }

  T& operator ()(int2 coord)
  {
#ifdef _DEBUG
    assert(coord.x >= 0 && coord.y >= 0 && coord.x < _width && coord.y < _height);
#endif
    return _data[coord.y*_width + coord.x];
  }

  void save(const char* filename) const;
};

template<>
surface<R8G8B8A8>::surface(const char* filename);

template<>
void surface<R8G8B8A8>::save(const char* filename) const;

extern template class surface<R8G8B8A8>;

#endif  // SURFACE_INCLUDED
