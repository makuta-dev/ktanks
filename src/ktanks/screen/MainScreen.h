#ifndef KTANKS_MAINSCREEN_H
#define KTANKS_MAINSCREEN_H

#include "ktanks/core/IScreen.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class MainScreen final : public IScreen {
    public:
        explicit MainScreen(AssetManager&);
        ~MainScreen() override;

        void onUpdate(float dt) override;
        void onDraw() override;
        void onEvent(const Event &) override;
    };

}

#endif //KTANKS_MAINSCREEN_H