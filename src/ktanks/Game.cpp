#include "Game.h"

#include "core/data/TankData.h"

namespace ktanks {

    Game::Game(AssetManager &asset_manager){
        atlas = &asset_manager.getTextureAtlas(AtlasID::Tanks);
    }

    Game::~Game() = default;

    void Game::onUpdate(const float dt) {

    }

    void Game::onDraw(Renderer& r) {
        r.setTexture(atlas->getTextureID());
        r.drawSprite({0,0},{512,512},{{0,0},{1,1}});

        const auto color = static_cast<int>(TankColor::Blue);
        const auto part = static_cast<int>(TankSprites::Body);

        if (const auto reg = atlas->at(color*5 + part)) {
            r.drawSprite({600,100},{128,128},*reg);
        }
    }

    void Game::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
