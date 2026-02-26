#include "Input.h"

#include <SDL3/SDL_mouse.h>

namespace ktanks {

    Input::Input(const std::string &placeholder, const OnSubmitCallback &onSubmit)
        : m_placeholder(placeholder), m_onSubmit(onSubmit) {
        setSize({240,60});
    }

    bool Input::onEvent(const Event& event) {
        if (event.type == EventType::MouseMove) {
            m_isHovered = isPointInside(glm::vec2{event.onMMove.x, event.onMMove.y});
            if (!m_isHovered && m_isFocused) {
                m_isFocused = false;
            }
            if (!m_isHovered) {
                if (m_onSubmit && !m_text.empty()) m_onSubmit(m_text);
            }
            return m_isHovered;
        }

        if (m_isHovered && event.type == EventType::MouseButton) {
            if(event.onMButton.pressed){
                m_isFocused = event.onMButton.button == SDL_BUTTON_LEFT;
            }
            if (m_isFocused) {
                InputManager::enableInput();
            }else {
                InputManager::disableInput();
            }
            return m_isFocused;
        }

        if (!m_isFocused) return false;

        if (event.type == EventType::Text) {
            m_text += static_cast<std::string>(event.onText.text);
            return true;
        }

        if (event.type == EventType::Key) {
            if (event.onKey.key == SDL_SCANCODE_BACKSPACE && !m_text.empty()) {
                m_text.pop_back();
                return true;
            }
            if (event.onKey.key == SDL_SCANCODE_RETURN && !m_text.empty()) {
                if (m_onSubmit && !m_text.empty()) m_onSubmit(m_text);
                m_isFocused = false;
                return true;
            }
        }

        return false;
    }

    void Input::onRender(Renderer& renderer) {
        const std::string displayText = m_text.empty() ? m_placeholder : m_text;
        const auto textColor = m_text.empty() ? glm::vec3(0.6f) : glm::vec3(0.f);

        const auto text_size = renderer.measureText(displayText);
        const auto text_offset = glm::vec2{15.f , getSize().y / 2 + text_size.y / 2};

        renderer.drawPatch(getAbsolutePosition(), getSize(), m_isFocused ? GuiSprites::input_square : GuiSprites::input_outline_square, 32);
        renderer.text(displayText,getAbsolutePosition() + text_offset, textColor);

        if (m_isFocused && static_cast<int>(m_cursorBlinkTimer) % 2 == 0 && !m_text.empty()) {
            const auto m_text_size = renderer.measureText(m_text);
            renderer.text("|",
                getAbsolutePosition() + text_offset + glm::vec2{m_text_size.x, 0},
                glm::vec3{0.f}
            );
        }
    }

    void Input::onUpdate(const float dt) {
        if (m_isFocused) {
            m_cursorBlinkTimer += dt * 2.0f;
        }
        IWidget::onUpdate(dt);
    }

    const std::string& Input::getText() const {
        return m_text;
    }

    void Input::setText(const std::string& text) {
        m_text = text;
    }

}
