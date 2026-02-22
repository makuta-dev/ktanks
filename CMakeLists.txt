cmake_minimum_required(VERSION 4.1)
project(kTanks)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets/")

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)
find_package(Freetype REQUIRED)

add_subdirectory(libs/glad)
add_subdirectory(libs/libspng)

add_executable(kTanks
        src/ktanks/core/constants/TankData.h
        src/ktanks/core/constants/TerrainData.h

        src/ktanks/core/IObject.h
        src/ktanks/core/IEntity.h

        src/ktanks/graphics/Camera.cpp
        src/ktanks/graphics/Camera.h
        src/ktanks/graphics/Font.cpp
        src/ktanks/graphics/Font.h
        src/ktanks/graphics/Renderer.cpp
        src/ktanks/graphics/Renderer.h
        src/ktanks/graphics/Shader.cpp
        src/ktanks/graphics/Shader.h
        src/ktanks/graphics/Texture.cpp
        src/ktanks/graphics/Texture.h
        src/ktanks/graphics/TextureAtlas.cpp
        src/ktanks/graphics/TextureAtlas.h
        src/ktanks/graphics/Vertex.h

        src/ktanks/models/entity/Tank.cpp
        src/ktanks/models/entity/Tank.h
        src/ktanks/models/Map.cpp
        src/ktanks/models/Map.h

        src/ktanks/utils/AssetManager.cpp
        src/ktanks/utils/AssetManager.h

        src/ktanks/window/Event.h
        src/ktanks/window/Window.cpp
        src/ktanks/window/Window.h

        src/ktanks/Game.cpp
        src/ktanks/Game.h

        src/main.cpp
)

target_include_directories(kTanks PRIVATE src)
target_link_libraries(kTanks PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glm::glm
        spdlog::spdlog
        Freetype::Freetype

        glad
        spng
)

target_include_directories(kTanks PRIVATE
        SDL3::SDL3
        OpenGL::GL
        glm::glm
        spdlog::spdlog
        Freetype::Freetype

        libs/glad/include
        libs/libspng/spng
)

target_compile_definitions(kTanks PRIVATE ASSETS_ROOT="${ASSETS_PATH}")
