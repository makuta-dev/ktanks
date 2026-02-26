#include "EditorScreen.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_scancode.h>
#include <spdlog/spdlog.h>

#include "MainScreen.h"
#include "ktanks/core/Constants.h"

namespace ktanks {

    EditorScreen::EditorScreen(const glm::uvec2& level_size, ScreenManager* m) : IScreen(m),
        m_terrain_layer(level_size, TerrainSprite::Grass1), m_blocks_layer(level_size * 4u) {
    }

    EditorScreen::~EditorScreen() = default;

    void EditorScreen::onUpdate(float dt) {

    }

    void EditorScreen::onDraw(Renderer& r) {
        r.setViewMatrix(m_view_mat);
        r.drawTerrain(m_terrain_layer);
        //r.drawBlocks(m_blocks_layer);

        const auto w = screenToWorld();
        const auto i = glm::floor(w / TILE_SIZE);
        r.icon(i * TILE_SIZE,TILE_SIZE,Icon::Crosshair);
    }

    void EditorScreen::onEvent(const Event& e) {
        if (e.type == EventType::Key) {
            if (e.onKey.pressed && e.onKey.key == SDL_SCANCODE_ESCAPE) {
                m_view_mat = glm::mat4(1.0f);
                getManager().navigate(std::make_unique<MainScreen>(&getManager()));
            }
        }
        if (e.type == EventType::WindowResize) {
            m_view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
        if (e.type == EventType::MouseMove) {
            m_last_mouse = m_mouse;
            m_mouse = glm::vec2{e.onMMove.x, e.onMMove.y};
            if (m_is_move) {
                const auto delta = m_mouse - m_last_mouse;
                m_offset += delta;
                updateMatrix();
            }
        }
        if (e.type == EventType::MouseButton) {
            m_is_move = e.onMButton.pressed && e.onMButton.button == SDL_BUTTON_RIGHT;
        }
        if (e.type == EventType::MouseWheel) {
            const auto old_zoom = m_zoom;
            m_zoom += e.onMWheel.dy * ZOOM_STEP;
            m_zoom = glm::clamp(m_zoom, ZOOM_MIN, ZOOM_MAX);

            const glm::vec2 mouseWorldBeforeZoom = (m_mouse - m_offset) / old_zoom;
            m_offset = m_mouse - (mouseWorldBeforeZoom * m_zoom);

            updateMatrix();
        }
    }

    void EditorScreen::updateMatrix() {
        m_view_mat = glm::mat4(1.0f);
        m_view_mat = glm::translate(m_view_mat, glm::vec3(m_offset, 0.0f));
        m_view_mat = glm::scale(m_view_mat, glm::vec3(m_zoom, m_zoom, 1.0f));
    }

    glm::vec2 EditorScreen::screenToWorld() const {
        return (m_mouse - m_offset) / m_zoom;
    }
}
