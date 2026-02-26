#include "EditorScreen.h"

#include <SDL3/SDL_scancode.h>
#include <spdlog/spdlog.h>

#include "MainScreen.h"

namespace ktanks {

    EditorScreen::EditorScreen(const glm::uvec2& level_size, ScreenManager* m) : IScreen(m),
        m_terrain_layer(level_size, TerrainSprite::Grass1), m_blocks_layer(level_size * 4u) {
        spdlog::info("level_size = {},{}", level_size.x, level_size.y);
    }

    EditorScreen::~EditorScreen() = default;

    void EditorScreen::onUpdate(float dt) {

    }

    void EditorScreen::onDraw(Renderer& r) {
        r.setViewMatrix(m_view_mat);
        r.drawTerrain(m_terrain_layer);
        //r.drawBlocks(m_blocks_layer);
    }

    void EditorScreen::onEvent(const Event& e) {
        if (e.type == EventType::Key) {
            if (e.onKey.pressed && e.onKey.key == SDL_SCANCODE_ESCAPE) {
                getManager().navigate(std::make_unique<MainScreen>(&getManager()));
            }
        }
        if (e.type == EventType::WindowResize) {
            m_view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
