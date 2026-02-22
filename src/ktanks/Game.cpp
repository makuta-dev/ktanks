#include "Game.h"

#include "core/constants/TankData.h"
#include "core/constants/TerrainData.h"

namespace ktanks {

    Game::Game(AssetManager &asset_manager){
        atlas = &asset_manager.getTextureAtlas(AtlasID::Terrain);
    }

    Game::~Game() = default;

    void Game::onUpdate(const float dt) {

    }

    void Game::onDraw(Renderer& r) {
        r.setTexture(atlas->getTextureID());
        r.drawSprite({0,0},{512,512},{{0,0},{1,1}});

        const auto tile = static_cast<int>(TerrainSprite::GCrossingRound);

        if (const auto reg = atlas->at(tile)) {
            r.drawSprite({600,100},{128,128},*reg);
        }
    }

    void Game::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
