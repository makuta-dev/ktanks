#include "TilePalette.h"

#include "TileButton.h"

namespace ktanks {

    TilePalette::TilePalette(const int width, const float tile_size) : m_tile_size(tile_size){
        m_size.x = width;
    }

    void TilePalette::performLayout() {
        float currentX = 0;
        float currentY = 0;
        constexpr float padding = 4.0f;

        for (const auto& child : m_children) {
            child->setSize({m_tile_size, m_tile_size});

            if (currentX + m_tile_size + padding > m_size.x && currentX > 0) {
                currentX = 0;
                currentY += m_tile_size + padding;
            }

            child->setPosition({currentX + padding, currentY + padding});
            currentX += m_tile_size + padding;
        }

        m_size.y = currentY + m_tile_size + (padding * 2.0f);
    }

    void TilePalette::onRender(Renderer &renderer) {
        IWidget::onRender(renderer);
    }

}
