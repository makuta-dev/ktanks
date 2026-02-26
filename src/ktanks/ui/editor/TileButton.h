#ifndef KTANKS_TILEBUTTON_H
#define KTANKS_TILEBUTTON_H

#include "ktanks/core/IWidget.h"

namespace ktanks {

    class TileButton final : public IWidget {
    public:
        TileButton(TerrainSprite id, const glm::vec2& size = glm::vec2{64.f});

        void onRender(Renderer &renderer) override;
        bool onEvent(const Event &event) override;

    private:
        TerrainSprite m_id;
    };

}

#endif //KTANKS_TILEBUTTON_H