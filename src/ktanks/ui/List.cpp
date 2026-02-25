#include "List.h"

namespace ktanks {

    List::List(const Orientation dir) : m_orientation(dir) {}

    void List::performLayout() {
        for (auto& child : m_children) {
            child->performLayout();
        }

        glm::vec2 cursor{ m_padding };

        for (auto& child : m_children) {
            child->setPosition(cursor);

            if (m_orientation == Orientation::Vertical) {
                cursor.y += child->getSize().y + m_spacing;

                if (child->getSize().x + (m_padding * 2.0f) > m_size.x) {
                    m_size.x = child->getSize().x + (m_padding * 2.0f);
                }
            } else {
                cursor.x += child->getSize().x + m_spacing;

                if (child->getSize().y + (m_padding * 2.0f) > m_size.y) {
                    m_size.y = child->getSize().y + (m_padding * 2.0f);
                }
            }
        }

        if (m_orientation == Orientation::Vertical) {
            m_size.y = cursor.y - m_spacing + m_padding;
        } else {
            m_size.x = cursor.x - m_spacing + m_padding;
        }
    }

    void List::onRender(Renderer& renderer) {
        if (!m_isActive) return;

        IWidget::onRender(renderer);
    }

}