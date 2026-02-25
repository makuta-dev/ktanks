#include "PlayScreen.h"

#include <SDL3/SDL_scancode.h>

#include "ktanks/core/Constants.h"
#include "ktanks/window/Event.h"

namespace ktanks {

    PlayScreen::PlayScreen(ScreenManager* m) : IScreen(m), m_player(TankColor::Green), m_level({16,16}) {
        m_player.setPos(TILE_SIZE);
    }

    PlayScreen::~PlayScreen() = default;

    void PlayScreen::onUpdate(const float dt) {
        m_player.onUpdate(dt);
        m_camera.update(m_player.getPos(),view, glm::vec2(m_level.getSize()) * TILE_SIZE, dt);
    }

    void PlayScreen::onDraw(Renderer& r) {
        r.drawLevel(m_level);
        r.setViewMatrix(m_camera.getViewMatrix());
        r.drawTank(m_player);
    }

    void PlayScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
        if (e.type == EventType::Key) {
            if (e.onKey.pressed && e.onKey.key == SDL_SCANCODE_ESCAPE) {
                getManager().navigate(ScreenID::Main);
            }
        }
    }

}
