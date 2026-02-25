#ifndef KTANKS_BUTTON_H
#define KTANKS_BUTTON_H

#include <functional>
#include <string>

#include "ktanks/core/IWidget.h"

namespace ktanks {

    class Button : public IWidget {
    public:
        using ClickCallback = std::function<void()>;

        Button(std::string label, ClickCallback callback);

        void onUpdate(float dt) override;
        void onRender(UIRenderer& renderer) override;
        bool onEvent(const Event& event) override;

    protected:
        bool m_isPressed = false;
        std::string m_label;
        ClickCallback m_onClick;
    };

}

#endif //KTANKS_BUTTON_H