#include "PlayScreen.h"

#include "ktanks/core/Constants.h"
#include "ktanks/window/Event.h"

namespace ktanks {

    PlayScreen::PlayScreen(AssetManager& a, ScreenManager* m) : IScreen(m), m_player(TankColor::Green), m_level({16,16}), m_game_renderer(a) {
        m_player.setPos(TILE_SIZE);
    }

    PlayScreen::~PlayScreen() = default;

    void PlayScreen::onUpdate(const float dt) {
        m_player.onUpdate(dt);
        m_camera.update(m_player.getPos(),view, glm::vec2(m_level.getSize()) * TILE_SIZE, dt);
    }

    void PlayScreen::onDraw() {
        m_game_renderer.beginFrame();
        m_game_renderer.drawLevel(m_level);
        m_game_renderer.setViewMatrix(m_camera.getViewMatrix());
        m_game_renderer.drawTank(m_player);
        m_game_renderer.endFrame();
    }

    void PlayScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
            m_game_renderer.resize(e.onWResize.width, e.onWResize.height);
        }
    }

}
