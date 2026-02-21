#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "ktanks/graphics/Renderer.h"
#include "ktanks/window/Event.h"

namespace ktanks {

    class Tanks final {
    public:
        explicit Tanks(const AssetManager &asset_manager);
        ~Tanks();

        void onUpdate(float dt);
        void onDraw(Renderer&);
        void onEvent(const Event &);

    private:
        glm::uvec2 view{0};
        TextureAtlas tank;
    };

}

#endif //KTANKS_TANKS_H