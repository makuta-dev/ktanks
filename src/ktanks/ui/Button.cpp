#include "Button.h"

#include <utility>
#include <SDL3/SDL_mouse.h>

namespace ktanks {

    Button::Button(std::string  label, ClickCallback callback)
        : m_label(std::move(label)), m_onClick(std::move(callback)) {
        m_size = {240.0f, 60.0f};
    }

    void Button::onUpdate(const float dt) {
        IWidget::onUpdate(dt);
    }

    void Button::onRender(Renderer& renderer) {
        GuiSprites sprite;
        if (m_isPressed) {
            sprite = GuiSprites::button_rectangle_gradient;
        } else if (m_isHovered) {
            sprite = GuiSprites::button_rectangle_flat;
        } else {
            sprite = GuiSprites::check_square_grey;
        }

        const glm::vec2 absPos = getAbsolutePosition();
        renderer.drawPatch(absPos, m_size, sprite);

        IWidget::onRender(renderer);

        const glm::vec2 textPos = absPos + (m_size * 0.5f);
        renderer.textCentered(m_label, textPos, {0.0f, 0.0f, 0.0f});
    }

    bool Button::onEvent(const Event& event) {
        if (event.type == EventType::MouseMove) {
            m_isHovered = isPointInside({event.onMMove.x, event.onMMove.y});
        }

        if (event.type == EventType::MouseButton && m_isHovered) {
            if (event.onMButton.pressed && event.onMButton.button == SDL_BUTTON_LEFT) {
                m_isPressed = true;
            }else{
                if (m_onClick) m_onClick();
                m_isPressed = false;
            }
            return true;
        }

        return false;
    }

}
