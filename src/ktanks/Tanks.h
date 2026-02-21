#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "ktanks/graphics/Renderer.h"

namespace ktanks {

    class Event;

    class Tanks final {
    public:
        Tanks();
        ~Tanks();

        void onUpdate(float dt);
        void onDraw(Renderer&);
        void onEvent(const Event&);

    private:
        glm::uvec2 view{0};
    };

}

#endif //KTANKS_TANKS_H