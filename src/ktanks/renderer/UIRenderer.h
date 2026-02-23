#ifndef KTANKS_UIRENDERER_H
#define KTANKS_UIRENDERER_H

#include "ktanks/renderer/Renderer.h"

namespace ktanks {

    class UIRenderer final : public Renderer{
    public:
        explicit UIRenderer(AssetManager&);
        ~UIRenderer();
    };

}

#endif //KTANKS_UIRENDERER_H