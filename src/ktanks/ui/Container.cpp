#include "Container.h"

namespace ktanks {

    Container::Container() = default;

    void Container::onRender(Renderer &renderer) {
        renderer.drawPatch(getAbsolutePosition(), getSize(), GuiSprites::button_rectangle_depth_flat, 32.0);
        IWidget::onRender(renderer);
    }

    void Container::performLayout() {
        if (!m_children.empty()) {
            const auto& child = m_children.front();
            child->performLayout();
            const glm::vec2 childSize = child->getSize();
            const glm::vec2 centeredPos = (m_size * 0.5f) - (childSize * 0.5f);
            child->setPosition(centeredPos);
            setSize(childSize + 48.f);
        }
    }

}