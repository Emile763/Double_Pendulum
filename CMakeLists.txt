cmake_minimum_required(VERSION 4.0.0)
project(Renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(third-party/SFML)

add_executable("DoublePendulumApp" 
    src/main.cpp
    src/DoublePendulum.cpp
    )
target_include_directories("DoublePendulumApp" PRIVATE include)
target_link_libraries("DoublePendulumApp" SFML::Graphics SFML::Window SFML::System)


