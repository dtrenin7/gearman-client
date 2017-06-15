cmake_minimum_required(VERSION 3.2)
project(gearman-client)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/OutputPaths.cmake)

add_definitions("-Wall")

#suppress warnings
add_definitions("-Wno-switch")
add_definitions("-Wno-write-strings")
add_definitions("-Wno-return-type")

add_definitions("-std=c++11")
add_definitions("-DSYSLOG")

add_definitions("-static")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/custom_timer.cpp
    src/gearman_client.cpp
    )

set(LIBS ${LIBS} gearman pthread)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(gearman-client ${SOURCE_FILES} )
target_link_libraries(gearman-client ${LIBS})
