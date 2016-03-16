project(lpng)

file(GLOB lpng_SOURCES *.c)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${ZLIB_INCLUDE_DIRS})

add_library(cgcv_libpng STATIC ${lpng_SOURCES})

target_link_libraries(cgcv_libpng ${ZLIB_LIBRARIES})

set(PNG_INCLUDE_DIRS "${SOURCE_DIR}" CACHE PATH "path to libpng headers")
set(PNG_LIBRARIES cgcv_libpng CACHE FILEPATH "path to libpng library")
