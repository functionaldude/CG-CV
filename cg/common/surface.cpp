


#include <string>
#include <stdexcept>
#include <cstdio>


#include "png.h"

#include "surface.h"


template<>
surface<R8G8B8A8>::surface(const char* filename)
{
  png_structp png_ptr;
  png_infop info_ptr;
  FILE *fp;

  fp = fopen(filename, "rb");
  if (fp == NULL)
    throw std::runtime_error(std::string("unable to open '") + filename + "'");

  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (png_ptr == NULL)
  {
    fclose(fp);
    throw std::runtime_error("png_create_read_struct() failed");
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL)
  {
    fclose(fp);
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    throw std::runtime_error("png_create_info_struct() failed");
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    fclose(fp);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    throw std::runtime_error(std::string("error reading '") + filename + "'");
  }

  png_init_io(png_ptr, fp);

  png_read_info(png_ptr, info_ptr);

  png_uint_32 width, height;
  int bit_depth, color_type, interlace_method, compression_method, filter_method;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_method, &compression_method, &filter_method);

  if (bit_depth != 8 || color_type != PNG_COLOR_TYPE_RGB_ALPHA)
  {
    fclose(fp);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    throw std::runtime_error(std::string("error reading '") + filename + "'");
  }

  _width = width;
  _height = height;
  _data = new surface::color_type[_width * _height];

  png_bytepp rows = new png_bytep[_height];
  for (int y = 0; y < _height; ++y)
    rows[y] = reinterpret_cast<png_bytep>(_data + y * _width);

  png_read_image(png_ptr, rows);

  delete[] rows;

  png_read_end(png_ptr, info_ptr);

  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  fclose(fp);
}

template<>
void surface<R8G8B8A8>::save(const char* filename) const
{
  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;

  fp = fopen(filename, "wb");
  if (fp == NULL)
    throw std::runtime_error(std::string("unable to open '") + filename + "'");

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (png_ptr == NULL)
  {
    fclose(fp);
    throw std::runtime_error("png_create_write_struct() failed");
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL)
  {
    fclose(fp);
    png_destroy_write_struct(&png_ptr,  NULL);
    throw std::runtime_error("png_create_info_struct() failed");
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    fclose(fp);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    throw std::runtime_error(std::string("error writing '") + filename + "'");
  }

  png_init_io(png_ptr, fp);

  png_set_IHDR(png_ptr, info_ptr, _width, _height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  png_write_info(png_ptr, info_ptr);

  png_bytepp rows = new png_bytep[_height];
  for (int y = 0; y < _height; ++y)
    rows[y] = reinterpret_cast<png_bytep>(_data + y * _width);

  png_write_image(png_ptr, rows);

  delete[] rows;

  png_write_end(png_ptr, info_ptr);

  png_destroy_write_struct(&png_ptr, &info_ptr);

  fclose(fp);
}

template class surface<R8G8B8A8>;
