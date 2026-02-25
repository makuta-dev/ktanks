#include "Label.h"

#include <utility>

namespace ktanks {

    Label::Label(std::string text) : m_text(std::move(text)) {}

    void Label::onRender(Renderer &renderer) {
        if (m_size.x <= 0 && m_size.y <= 0) {
            m_size = renderer.measureText(m_text);
            invalidateLayout();
            return;
        }

        renderer.text(m_text,getAbsolutePosition() + glm::vec2{0,m_size.y},{1,1,1});
    }

}