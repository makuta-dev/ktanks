cmake_minimum_required(VERSION 4.1)
project(ktanks)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

add_executable(ktanks

        src/ktanks/window/Window.cpp
        src/ktanks/window/Window.h

        src/ktanks/Tanks.cpp
        src/ktanks/Tanks.h

        src/main.cpp
        src/ktanks/window/Event.h
)

target_include_directories(ktanks PRIVATE src)
target_link_libraries(ktanks PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glm::glm
        spdlog::spdlog
)

target_include_directories(ktanks PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glm::glm
        spdlog::spdlog
)