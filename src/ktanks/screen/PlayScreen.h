#ifndef KTANKS_PLAYSCREEN_H
#define KTANKS_PLAYSCREEN_H

#include "ktanks/core/IScreen.h"
#include "ktanks/graphics/Camera.h"
#include "ktanks/models/Level.h"
#include "ktanks/models/entity/Tank.h"
#include "ktanks/renderer/GameRenderer.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class PlayScreen final : public IScreen{
    public:
        explicit PlayScreen(AssetManager&);
        ~PlayScreen() override;

        void onUpdate(float dt) override;
        void onDraw() override;
        void onEvent(const Event &) override;

    private:
        glm::uvec2 view{0};
        Tank m_player;
        Level m_level;
        Camera m_camera;
        GameRenderer m_game_renderer;
    };

}

#endif //KTANKS_PLAYSCREEN_H