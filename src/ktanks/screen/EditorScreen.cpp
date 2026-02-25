#include "EditorScreen.h"

#include <SDL3/SDL_scancode.h>

namespace ktanks {

    EditorScreen::EditorScreen(ScreenManager* m) : IScreen(m) {}
    EditorScreen::~EditorScreen() = default;

    void EditorScreen::onUpdate(float dt) {

    }

    void EditorScreen::onDraw(Renderer&) {

    }

    void EditorScreen::onEvent(const Event& e) {
        if (e.type == EventType::Key) {
            if (e.onKey.pressed && e.onKey.key == SDL_SCANCODE_ESCAPE) {
                getManager().navigate(ScreenID::Main);
            }
        }
    }

}
