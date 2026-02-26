#include "Game.h"

#include "screen/MainScreen.h"
#include "screen/PlayScreen.h"
#include "screen/SetupScreen.h"

namespace ktanks {

    Game::Game() : m_renderer(m_assets){
        m_screen = std::make_unique<MainScreen>(this);
    }

    Game::~Game() = default;

    void Game::onInit() {
        m_screen->onInit();
    }

    void Game::onUpdate(const float dt) {
        m_screen->onUpdate(dt);
    }

    void Game::onDraw() {
        m_renderer.beginFrame();
        m_renderer.setViewMatrix(glm::mat4{1.f});
        m_screen->onDraw(m_renderer);
        m_renderer.endFrame();
    }

    void Game::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_view = glm::uvec2(e.onWResize.width, e.onWResize.height);
            m_renderer.resize(e.onWResize.width, e.onWResize.height);
        }
        m_screen->onEvent(e);
    }

    void Game::navigate(ScreenPtr id) {
        if (m_screen != id){
            m_screen = std::move(id);
            m_screen->onInit();
            m_screen->onEvent(
                Event{
                    .type = EventType::WindowResize,
                    .onWResize = WindowResizeEvent{
                        static_cast<int>(m_view.x),
                        static_cast<int>(m_view.y)
                    }
                }
            );
        }
    }

    glm::uvec2 Game::getViewport() {
        return m_view;
    }

}
