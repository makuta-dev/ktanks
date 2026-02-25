#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "ktanks/utils/AssetManager.h"
#include "ktanks/window/Event.h"
#include "ktanks/renderer/Renderer.h"

namespace ktanks {

    class Game final {
    public:
        Game();
        ~Game();

        void onUpdate(float dt);
        void onDraw();
        void onEvent(const Event &);

    private:
        AssetManager m_assets;
        Renderer m_renderer;
        TextureAtlas* m_gui;
        Font* m_font;
        Font* m_font2;
    };

}

#endif //KTANKS_TANKS_H