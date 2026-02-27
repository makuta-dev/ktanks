#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include <memory>

#include "ktanks/graphics/Renderer.h"
#include "ktanks/utils/AssetsManager.h"
#include "ktanks/window/Event.h"
#include "ktanks/window/Window.h"

namespace ktanks {

    class Game final  {
    public:
        Game();
        ~Game();

        void run();

    private:
        void onInit();
        void onUpdate(float dt);
        void onDraw(Renderer& r);
        void onEvent(const Event &);

        AssetsManager m_assets;
        std::shared_ptr<Window> m_window;
        std::unique_ptr<Renderer> m_renderer;
    };

}

#endif //KTANKS_TANKS_H