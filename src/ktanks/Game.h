#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "graphics/Camera.h"
#include "ktanks/window/Event.h"
#include "ktanks/renderer/Renderer.h"
#include "ktanks/renderer/GameRenderer.h"

namespace ktanks {

    class Game final {
    public:
        explicit Game(AssetManager&);
        ~Game();

        void onUpdate(float dt);
        void onDraw();
        void onEvent(const Event &);

    private:
        glm::uvec2 view{0};
        Tank m_player;
        Level m_level;
        Camera m_camera;
        GameRenderer m_game_renderer;
    };

}

#endif //KTANKS_TANKS_H