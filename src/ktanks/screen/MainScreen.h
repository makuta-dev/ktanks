#ifndef KTANKS_MAINSCREEN_H
#define KTANKS_MAINSCREEN_H

#include "ktanks/core/IScreen.h"
#include "ktanks/core/IWidget.h"
#include "ktanks/renderer/UIRenderer.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class MainScreen final : public IScreen {
    public:
        explicit MainScreen(AssetManager&, ScreenManager*);
        ~MainScreen() override;

        void onInit() override;
        void onUpdate(float dt) override;
        void onDraw() override;
        void onEvent(const Event &) override;

    private:
        void onRender(UIRenderer&);

        UIRenderer m_renderer;
        std::unique_ptr<IWidget> m_center_widget;
    };

}

#endif //KTANKS_MAINSCREEN_H