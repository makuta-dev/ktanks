#ifndef KTANKS_SCROLLCONTAINER_H
#define KTANKS_SCROLLCONTAINER_H

#include "ktanks/core/IWidget.h"

namespace ktanks {

    class ScrollContainer final : public IWidget {
    public:
        ScrollContainer();

        void performLayout() override;
        void onRender(Renderer &renderer) override;
        bool onEvent(const Event &event) override;

    private:
        float m_scrollOffset = 0.0f;
        float m_contentHeight = 0.0f;
    };

}

#endif //KTANKS_SCROLLCONTAINER_H