#include "Game.h"

#include "core/Constants.h"
#include "core/data/TankData.h"

namespace ktanks {

    Game::Game(AssetManager &asset_manager) : m_player(TankColor::Green), m_level({16,16}), m_game_renderer(asset_manager) {
        m_player.setPos(TILE_SIZE);
    }

    Game::~Game() = default;

    void Game::onUpdate(const float dt) {
        m_player.onUpdate(dt);
        m_camera.update(m_player.getPos(),view, glm::vec2(m_level.getSize()) * TILE_SIZE ,dt);
    }

    void Game::onDraw() {
        m_game_renderer.beginFrame();
        m_game_renderer.drawLevel(m_level);
        m_game_renderer.setViewMatrix(m_camera.getViewMatrix());
        m_game_renderer.drawTank(m_player);
        m_game_renderer.endFrame();
    }

    void Game::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
            m_game_renderer.resize(e.onWResize.width, e.onWResize.height);
        }
    }

}
