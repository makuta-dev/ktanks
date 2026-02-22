#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "data/Map.h"
#include "entity/Tank.h"
#include "graphics/Camera.h"
#include "ktanks/graphics/Renderer.h"
#include "ktanks/window/Event.h"

namespace ktanks {

    class Game final {
    public:
        explicit Game(const AssetManager &asset_manager);
        ~Game();

        void onUpdate(float dt);
        void onDraw(Renderer&);
        void onEvent(const Event &);

    private:
        float lastFps = 0.0f;
        float fps{0.f};

        Font font;
        glm::uvec2 view{0};
        Tank tank;
        Map map;
        TextureAtlas terrain_atlas;
        Camera camera;
    };

}

#endif //KTANKS_TANKS_H