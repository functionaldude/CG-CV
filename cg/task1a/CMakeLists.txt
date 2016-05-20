project(cgtask1a)

file(GLOB SOURCES ${SOURCE_WILDCARDS})

include_directories(
  ${cgcvcommon_INCLUDE_DIRS}
  ${cgcommon_INCLUDE_DIRS}
)

add_executable(cgtask1a
  ${SOURCES}
)
target_link_libraries(cgtask1a
  cgcommon
)

add_submit_target(cgtask1a)
