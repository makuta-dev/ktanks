#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include <memory>

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
        void onDraw();
        void onEvent(const Event &);

        std::shared_ptr<Window> m_window;
    };

}

#endif //KTANKS_TANKS_H