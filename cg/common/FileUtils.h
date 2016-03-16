#pragma once
namespace utils
{
  char* readFileToString(const char* filename, bool terminate = false);
  unsigned char* readFileToBytes(const char* filename);
};

