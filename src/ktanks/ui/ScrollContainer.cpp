#include "ScrollContainer.h"

#include <glm/ext/matrix_transform.hpp>

namespace ktanks {

    ScrollContainer::ScrollContainer() = default;

    void ScrollContainer::performLayout() {
        float currentY = -m_scrollOffset;
        m_contentHeight = 0;

        for (const auto& child : m_children) {
            child->setSize({m_size.x, child->getSize().y});

            child->performLayout();

            child->setPosition({0, currentY});
            currentY += child->getSize().y;
            m_contentHeight = std::max(m_contentHeight, currentY + m_scrollOffset);
        }

    }

    void ScrollContainer::onRender(Renderer &renderer) {
        renderer.drawPatch(getAbsolutePosition(),getSize(),GuiSprites::input_square);
        IWidget::onRender(renderer);
    }

    bool ScrollContainer::onEvent(const Event &event) {
        if (event.type == EventType::MouseWheel && m_isHovered) {
            m_scrollOffset -= event.onMWheel.dy * 20.0f;
            const float maxScroll = std::max(0.0f, m_contentHeight - m_size.y);
            m_scrollOffset = std::clamp(m_scrollOffset, 0.0f, maxScroll);
            setPosition({m_scrollOffset,0});
            return true;
        }

        return false;
    }

}
