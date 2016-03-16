project(zlib)

file(GLOB zlib_SOURCES *.c)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(cgcv_zlib STATIC ${zlib_SOURCES})

set(ZLIB_INCLUDE_DIRS "${SOURCE_DIR}" CACHE PATH "path to zlib headers")
set(ZLIB_LIBRARIES cgcv_zlib CACHE FILEPATH "path to zlib library")
