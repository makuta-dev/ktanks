#include "TileButton.h"

#include <SDL3/SDL_mouse.h>

namespace ktanks {

    TileButton::TileButton(const TerrainSprite id, const glm::vec2& size) : m_id(id) {
        setSize(size);
    }

    void TileButton::onRender(Renderer &renderer) {
        renderer.drawTile(getAbsolutePosition(), m_size, m_id);
    }

    bool TileButton::onEvent(const Event &event) {
        if (event.type == EventType::MouseButton &&
            event.onMButton.pressed &&
            event.onMButton.button == SDL_BUTTON_LEFT) {
            if (m_isHovered) {
                return true;
            }
        }
        return false;
    }

}
