#ifndef KTANKS_IWIDGET_H
#define KTANKS_IWIDGET_H

#include <glm/vec2.hpp>
#include <ranges>

#include "ktanks/graphics/Renderer.h"
#include "ktanks/window/Event.h"

namespace ktanks {

    class IWidget {
    public:
        IWidget() = default;
        virtual ~IWidget() = default;

        virtual void onUpdate(const float dt) {
            for (const auto& child : m_children)
                child->onUpdate(dt);
        }

        virtual void onRender(Renderer& renderer){
            for (const auto& child : m_children)
                child->onRender(renderer);
        }

        virtual bool onChildEvent(const Event& event) {
            if (!m_isActive) return false;

            for (const auto& it : std::ranges::reverse_view(m_children)) {
                if (it->onChildEvent(event)) {
                    return true;
                }
            }

            return onEvent(event);
        }

        virtual bool onEvent(const Event& event) { return false; }

        virtual void performLayout() {
            for (const auto& child : m_children) {
                child->performLayout();
            }
        }

        void setPosition(const glm::vec2& pos) { m_position = pos; }
        void setSize(const glm::vec2& size)     { m_size = size; }

        [[nodiscard]] const glm::vec2& getPosition() const { return m_position; }
        [[nodiscard]] const glm::vec2& getSize()     const { return m_size; }

        [[nodiscard]] bool isPointInside(const glm::vec2& point) const {
            return point.x >= getAbsolutePosition().x && point.x <= getAbsolutePosition().x + m_size.x &&
                   point.y >= getAbsolutePosition().y && point.y <= getAbsolutePosition().y + m_size.y;
        }

        [[nodiscard]] glm::vec2 getAbsolutePosition() const {
            if (m_parent) {
                return m_parent->getAbsolutePosition() + glm::vec2{m_position};
            }
            return m_position;
        }

        void addChild(std::unique_ptr<IWidget> child) {
            child->m_parent = this;
            m_children.push_back(std::move(child));
            invalidateLayout();
        }

        void invalidateLayout() {
            if (m_parent) m_parent->invalidateLayout();
            performLayout();
        }

    protected:
        bool m_isActive = true;
        bool m_isHovered = false;
        IWidget* m_parent = nullptr;
        glm::vec2 m_position{0.0f};
        glm::vec2 m_size{0.0f};
        std::vector<std::unique_ptr<IWidget>> m_children;
    };

}

#endif //KTANKS_IWIDGET_H