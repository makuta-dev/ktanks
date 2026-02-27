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

        src/ktanks/base/IScreen.cpp
        src/ktanks/base/IScreen.h
        src/ktanks/base/IWidget.cpp
        src/ktanks/base/IWidget.h

        src/ktanks/game/models/entity/Tank.cpp
        src/ktanks/game/models/entity/Tank.h
        src/ktanks/game/models/entity/Tree.cpp
        src/ktanks/game/models/entity/Tree.h
        src/ktanks/game/models/entity/Wall.cpp
        src/ktanks/game/models/entity/Wall.h
        src/ktanks/game/models/entity/Sandbag.cpp
        src/ktanks/game/models/entity/Sandbag.h
        src/ktanks/game/models/Level.cpp
        src/ktanks/game/models/Level.h
        src/ktanks/game/models/LevelLayer.cpp
        src/ktanks/game/models/LevelLayer.h

        src/ktanks/game/screen/MainScreen.cpp
        src/ktanks/game/screen/MainScreen.h
        src/ktanks/game/screen/PlayScreen.cpp
        src/ktanks/game/screen/PlayScreen.h
        src/ktanks/game/screen/EditorScreen.cpp
        src/ktanks/game/screen/EditorScreen.h
        src/ktanks/game/screen/SettingsScreen.cpp
        src/ktanks/game/screen/SettingsScreen.h

        src/ktanks/game/Game.cpp
        src/ktanks/game/Game.h

        src/ktanks/graphics/Shader.cpp
        src/ktanks/graphics/Shader.h
        src/ktanks/graphics/Texture.cpp
        src/ktanks/graphics/Texture.h
        src/ktanks/graphics/Renderer.cpp
        src/ktanks/graphics/Renderer.h
        src/ktanks/graphics/Font.cpp
        src/ktanks/graphics/Font.h
        src/ktanks/graphics/Atlas.cpp
        src/ktanks/graphics/Atlas.h
        src/ktanks/graphics/Color.cpp
        src/ktanks/graphics/Color.h

        src/ktanks/ui/Button.cpp
        src/ktanks/ui/Button.h
        src/ktanks/ui/Label.cpp
        src/ktanks/ui/Label.h
        src/ktanks/ui/layout/BoxLayout.cpp
        src/ktanks/ui/layout/BoxLayout.h
        src/ktanks/ui/layout/ScrollLayout.cpp
        src/ktanks/ui/layout/ScrollLayout.h

        src/ktanks/utils/Log.cpp
        src/ktanks/utils/Log.h

        src/ktanks/window/Event.h
        src/ktanks/window/Window.cpp
        src/ktanks/window/Window.h

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
