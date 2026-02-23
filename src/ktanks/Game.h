#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "renderer/Renderer.h"
#include "ktanks/window/Event.h"

namespace ktanks {

    class Game final {
    public:
        explicit Game(AssetManager&);
        ~Game();

        void onUpdate(float dt);
        void onDraw(Renderer&);
        void onEvent(const Event &);

    private:
        glm::uvec2 view{0};
        TextureAtlas* atlas;
    };

}

#endif //KTANKS_TANKS_H