#include "EditorScreen.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_scancode.h>
#include <spdlog/spdlog.h>

#include "ktanks/core/Constants.h"
#include "ktanks/screen/MainScreen.h"

namespace ktanks {

    EditorScreen::EditorScreen(const glm::uvec2& level_size, ScreenManager* m) : IScreen(m),
        m_terrain_layer(level_size, TerrainSprite::Grass1), m_blocks_layer(level_size * 4u) {
    }

    EditorScreen::~EditorScreen() = default;

    void EditorScreen::onInit() {

    }

    void EditorScreen::onUpdate(const float dt) {

    }

    void EditorScreen::onDraw(Renderer& r) {
        r.setViewMatrix(m_view_mat);
        r.drawTerrain(m_terrain_layer);
        //r.drawBlocks(m_blocks_layer);

        const auto w = screenToWorld();
        const auto i = glm::uvec2(glm::floor(w / TILE_SIZE));
        if (i.x < m_terrain_layer.getSize().x && i.y < m_terrain_layer.getSize().y) {
            r.icon(glm::vec2(i) * TILE_SIZE,TILE_SIZE,Icon::Crosshair);
        }
    }

    void EditorScreen::onEvent(const Event& e) {
        switch (e.type) {
            case EventType::MouseButton: {
                if (e.onMButton.button == SDL_BUTTON_LEFT) {
                    if (e.onMButton.pressed) {
                        paintTileAtMouse();
                    }
                }
                break;
            }

            case EventType::MouseMove: {
                m_mouse = glm::vec2{e.onMMove.x, e.onMMove.y};
                break;
            }

            case EventType::MouseWheel: {
                const float old_zoom = m_zoom;
                m_zoom = glm::clamp(m_zoom + (e.onMWheel.dy * ZOOM_STEP), ZOOM_MIN, ZOOM_MAX);

                if (m_zoom != old_zoom) {
                    const glm::vec2 mouseWorldBeforeZoom = (m_mouse - m_offset) / old_zoom;
                    m_offset = m_mouse - (mouseWorldBeforeZoom * m_zoom);
                    updateMatrix();
                }
                break;
            }

            case EventType::WindowResize:
                m_view = glm::uvec2(e.onWResize.width, e.onWResize.height);
                break;

            case EventType::Key:
                if (e.onKey.pressed && e.onKey.key == SDL_SCANCODE_ESCAPE) {
                    getManager().navigate(std::make_unique<MainScreen>(&getManager()));
                }
                break;

            default: break;
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

    void EditorScreen::paintTileAtMouse() {
        const auto w = screenToWorld();
        const auto i = glm::floor(w / TILE_SIZE);
        m_terrain_layer.set(i, TerrainSprite::Sand2);
    }

}
