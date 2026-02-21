#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "ktanks/data/Map.h"
#include "ktanks/entity/Player.h"
#include "ktanks/graphics/Renderer.h"
#include "ktanks/window/Event.h"

namespace ktanks {

    class Tanks final {
    public:
        Tanks();
        ~Tanks();

        void onUpdate(float dt);
        void onDraw(Renderer&);
        void onEvent(const Event &);

    private:
        glm::uvec2 view{0};
        Player player;
        Map map;
        TextureAtlas tank;
    };

}

#endif //KTANKS_TANKS_H