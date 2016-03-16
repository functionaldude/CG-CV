project(cgcommon)

add_subdirectory_if_exists("ObjProcessor")

set(HEADERS
  cgmath.h
  vector.h
  matrix.h
  color.h
  surface.h
  formats.h
  Triangle.h
  Material.h
  FileUtils.h
  Scene.h
  Ray.h
  Camera.h
  Intersection.h
  Light.h
  BVHTree.h
  BVHTreeNode.h
  BoundingBox.h
  Serialization.h
  mkdir.h
  )

set(SOURCES
  surface.cpp
  Triangle.cpp
  Material.cpp
  FileUtils.cpp
  Scene.cpp
  Ray.cpp
  Camera.cpp
  Intersection.cpp
  Light.cpp
  BVHTree.cpp
  BVHTreeNode.cpp
  BoundingBox.cpp
  main.cpp
  )

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" "${ZLIB_INCLUDE_DIRS}" "${PNG_INCLUDE_DIRS}" "${cgcvcommon_INCLUDE_DIRS}")

include_directories(${INCLUDE_DIRS})
  
add_library(cgcommon STATIC ${HEADERS} ${SOURCES})

target_link_libraries(cgcommon ${ZLIB_LIBRARIES} ${PNG_LIBRARIES})

if (BUILD_CG2)
  if (APPLE)
    find_path(GLFW_INCLUDE_DIR DOC "GLFW include directory"
              NAMES glfw.h PATH_SUFFIXES gl 
              PATHS C:/glfw-2.7.2/include C:/glfw/include /usr/include/ /usr/local/include/ /usr/include/GL /usr/local/include/GL/)
    find_library(GLFW_LIBRARIES DOC "GLFW libraries"
                 NAMES GLFW glfw GLFW.lib
                 PATHS /usr/local/lib /usr/lib/)
  else()
    add_subdirectory_if_exists(glfw-2.7.2)
  endif()
endif ()

set(cgcommon_INCLUDE_DIRS ${INCLUDE_DIRS} CACHE INTERNAL "cg common include directories")
