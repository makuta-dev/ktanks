#include "Game.h"

#include "screen/MainScreen.h"

namespace ktanks {

    Game::Game() {
        m_screen = std::make_unique<MainScreen>(m_assets, this);
    }
    Game::~Game() = default;

    void Game::onInit() {
        m_screen->onInit();
    }

    void Game::onUpdate(const float dt) {
        m_screen->onUpdate(dt);
    }

    void Game::onDraw() {
        m_screen->onDraw();
    }

    void Game::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
        m_screen->onEvent(e);
    }

    void Game::navigate(ScreenPtr& s) {
        m_screen = std::move(s);
    }

    glm::uvec2 Game::getViewport() {
        return m_view;
    }

}
