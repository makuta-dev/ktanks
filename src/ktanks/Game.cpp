#include "Game.h"

namespace ktanks {

    Game::Game() : m_renderer(m_assets) {
        m_gui = &m_assets.getTextureAtlas(AtlasID::GUI);
        m_font = &m_assets.getFont(FontID::Bold);
        m_font2 = &m_assets.getFont(FontID::Regular);
    }

    Game::~Game() = default;

    void Game::onUpdate(const float dt) {

    }

    void Game::onDraw() {
        m_renderer.beginFrame();
        m_renderer.setTexture(m_gui->getTextureID());
        m_renderer.drawSprite({0,0}, {512,512},{{0,0},{1,1}});

        m_renderer.drawText("Hello, World",{600,100},{1,1,1},*m_font);
        m_renderer.drawText("Hello, World",{600,116},{1,1,1},*m_font2);
        m_renderer.endFrame();
    }

    void Game::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_renderer.resize(e.onWResize.width, e.onWResize.height);
        }
    }

}
