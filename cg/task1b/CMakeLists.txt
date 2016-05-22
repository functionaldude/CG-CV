project(cgtask1b)

file(GLOB SOURCES ${SOURCE_WILDCARDS})

include_directories(
        ${cgcvcommon_INCLUDE_DIRS}
        ${cgcommon_INCLUDE_DIRS}
)

add_executable(cgtask1b
        ${SOURCES}
        )
target_link_libraries(cgtask1b
        cgcommon
        )

add_submit_target(cgtask1b)
