#ifndef KTANKS_TILEPALETTE_H
#define KTANKS_TILEPALETTE_H

#include "ktanks/core/IWidget.h"

namespace ktanks {

    class TilePalette final : public IWidget{
    public:
        TilePalette(int width, float tile_size);

        void performLayout() override;
        void onRender(Renderer &renderer) override;

    private:
        float m_tile_size;
    };

}

#endif //KTANKS_TILEPALETTE_H