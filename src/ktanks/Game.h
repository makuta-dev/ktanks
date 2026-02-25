#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "core/IScreen.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class Game final : public ScreenManager {
    public:
        Game();
        ~Game() override;

        void onInit();
        void onUpdate(float dt);
        void onDraw();
        void onEvent(const Event &);

        void navigate(ScreenID) override;
        glm::uvec2 getViewport() override;

    private:
        glm::uvec2 m_view{};
        AssetManager m_assets;
        std::unique_ptr<IScreen> m_screen;
    };

}

#endif //KTANKS_TANKS_H