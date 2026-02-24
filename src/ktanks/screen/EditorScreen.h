#ifndef KTANKS_EDITORSCREEN_H
#define KTANKS_EDITORSCREEN_H

#include "ktanks/core/IScreen.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class EditorScreen final : public IScreen {
    public:
        explicit EditorScreen(AssetManager&);
        ~EditorScreen() override;

        void onUpdate(float dt) override;
        void onDraw() override;
        void onEvent(const Event &) override;
    };

}

#endif //KTANKS_EDITORSCREEN_H