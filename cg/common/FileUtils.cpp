#include "FileUtils.h"
#include <fstream>
#include <iostream>
#include <algorithm>

char* utils::readFileToString(const char* filename, bool terminate)
{
  // Open file stream.
  std::ifstream fs(filename, std::ios::binary);
  if (!fs.is_open())
  {
    std::cerr << "Failed to open file '" << filename << "'." << std::endl;
    return 0;
  }

  // Get size of file.
  fs.seekg(0, std::ios::end);
  std::size_t size = static_cast<size_t>(fs.tellg());
  fs.seekg(0, std::ios::beg);

  // Allocate buffer for the file.
  char* data = new char[size + (terminate ? 1 : 0)];

  // Read the file.
  fs.read(data, size);

  if (terminate) 
    data[size] = 0;

  // TODO: Add error handling.

  return data;
}

unsigned char * utils::readFileToBytes(const char * filename)
{
  // Open file stream.
  std::ifstream fs(filename, std::ios::binary);
  if (!fs.is_open())
  {
    std::cerr << "Failed to open file '" << filename << "'." << std::endl;
    return 0;
  }

  // Get size of file.
  fs.seekg(0, std::ios::end);
  std::size_t size = static_cast<size_t>(fs.tellg());
  fs.seekg(0, std::ios::beg);

  // Allocate buffer for the file.
  unsigned char* data = new unsigned char[size + 1];
  std::fill(data, data + size + 1, 0);

  // Read the file.
  fs.read(reinterpret_cast<char*>(data), size);
  // TODO: Add error handling.

  return data;
}
