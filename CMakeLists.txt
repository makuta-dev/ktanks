cmake_minimum_required(VERSION 4.1)
project(kTanks)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets/")

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(libs/glad)
add_subdirectory(libs/libspng)

add_executable(kTanks
        src/ktanks/graphics/Font.cpp
        src/ktanks/graphics/Font.h
        src/ktanks/graphics/Shader.cpp
        src/ktanks/graphics/Shader.h
        src/ktanks/graphics/Texture.cpp
        src/ktanks/graphics/Texture.h
        src/ktanks/graphics/Vertex.cpp
        src/ktanks/graphics/Vertex.h

        src/ktanks/utils/AssetManager.cpp
        src/ktanks/utils/AssetManager.h

        src/ktanks/window/Event.h
        src/ktanks/window/Window.cpp
        src/ktanks/window/Window.h

        src/ktanks/Tanks.cpp
        src/ktanks/Tanks.h

        src/main.cpp
        src/ktanks/data/TerrainSpriteList.h
)

target_include_directories(kTanks PRIVATE src)
target_link_libraries(kTanks PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glm::glm
        spdlog::spdlog
        glad
        spng
)

target_include_directories(kTanks PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glm::glm
        spdlog::spdlog

        libs/glad/include
        libs/libspng/spng
)

target_compile_definitions(kTanks PRIVATE ASSETS_ROOT="${ASSETS_PATH}")
