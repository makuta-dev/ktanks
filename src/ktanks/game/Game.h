#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "ktanks/window/Event.h"

namespace ktanks {

    class Game final  {
    public:
        Game();
        ~Game();

        void onInit();
        void onUpdate(float dt);
        void onDraw();
        void onEvent(const Event &);
    };

}

#endif //KTANKS_TANKS_H