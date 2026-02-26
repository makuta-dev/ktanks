#ifndef KTANKS_SETUPSCREEN_H
#define KTANKS_SETUPSCREEN_H

#include "ktanks/core/IScreen.h"
#include "ktanks/core/IWidget.h"

namespace ktanks {

    class SetupScreen final : public IScreen{
    public:
        explicit SetupScreen(ScreenManager *manager);

        void onInit() override;
        void onUpdate(float dt) override;
        void onDraw(Renderer &) override;
        void onEvent(const Event &) override;

    private:
        glm::uvec2 m_world_size{0};
        std::unique_ptr<IWidget> m_widget;
        LevelMap<TerrainSprite> m_background;
    };

}

#endif //KTANKS_SETUPSCREEN_H