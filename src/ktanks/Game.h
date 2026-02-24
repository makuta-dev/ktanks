#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "ktanks/utils/AssetManager.h"
#include "ktanks/window/Event.h"

namespace ktanks {

    class Game final {
    public:
        explicit Game(AssetManager&);
        ~Game();

        void onUpdate(float dt);
        void onDraw();
        void onEvent(const Event &);
    };

}

#endif //KTANKS_TANKS_H