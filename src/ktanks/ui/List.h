#ifndef KTANKS_LIST_H
#define KTANKS_LIST_H

#include "ktanks/core/IWidget.h"

namespace ktanks {

    enum class Orientation { Vertical, Horizontal };

    class List : public IWidget {
    public:
        explicit List(Orientation dir);

        void setSpacing(const float spacing) { m_spacing = spacing; invalidateLayout(); }
        void setPadding(const float padding) { m_padding = padding; invalidateLayout(); }

        void performLayout() override;
        void onRender(UIRenderer& renderer) override;

    private:
        Orientation m_orientation;
        float m_spacing = 5.0f;
        float m_padding = 5.0f;
    };
}

#endif //KTANKS_LIST_H