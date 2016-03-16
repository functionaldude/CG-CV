#pragma once

#if defined _MSC_VER
#include <direct.h>
#elif defined __GNUC__
#include <sys/types.h>
#include <sys/stat.h>
#endif

namespace utils
{
  void mkDir(const char* dir)
  {
#if defined _MSC_VER
    _mkdir(dir);
#elif defined __GNUC__
    mkdir(dir, 0777);
#endif
  }
}
