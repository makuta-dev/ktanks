#ifndef KTANKS_INPUT_H
#define KTANKS_INPUT_H

#include <SDL3/SDL_scancode.h>

#include "ktanks/core/IWidget.h"
#include "ktanks/utils/InputManager.h"

namespace ktanks {

    class Input final : public IWidget {
    public:
        using OnSubmitCallback = std::function<void(const std::string&)>;

        explicit Input(const std::string &placeholder, const OnSubmitCallback &onSubmit);

        bool onEvent(const Event& event) override;
        void onRender(Renderer& renderer) override;
        void onUpdate(const float dt) override;

        const std::string& getText() const;
        void setText(const std::string& text);

    private:
        std::string m_text;
        std::string m_placeholder;
        bool m_isFocused = false;
        float m_cursorBlinkTimer = 0.0f;
        OnSubmitCallback m_onSubmit;
    };

}

#endif //KTANKS_INPUT_H