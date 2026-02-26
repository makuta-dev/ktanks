#include "Label.h"

#include <utility>

namespace ktanks {

    constexpr auto LABEL_PADDING = 16.f;

    Label::Label(std::string text, const bool centered) :  is_centered(centered), m_text(std::move(text)) {}

    void Label::performLayout() {
        if (m_parent && is_centered) {
            const auto parent_size = m_parent->getSize();
            m_position.x = parent_size.x / 2 - m_size.x / 2;
        }
    }

    void Label::onRender(Renderer &renderer) {
        if (m_size.x <= 0 && m_size.y <= 0) {
            m_size = renderer.measureText(m_text) + glm::vec2(LABEL_PADDING) * 2.f;
            invalidateLayout();
            return;
        }

        renderer.text(m_text,getAbsolutePosition() + glm::vec2{0,m_size.y / 2.f + LABEL_PADDING / 2.f},{1,1,1});
    }

}