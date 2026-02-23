#include "GameRenderer.h"

namespace ktanks {

    GameRenderer::GameRenderer(AssetManager& a) : Renderer(a) {
        m_tank_atlas = &a.getTextureAtlas(AtlasID::Tanks);
        m_terrain_atlas = &a.getTextureAtlas(AtlasID::Terrain);
        m_block_atlas = &a.getTextureAtlas(AtlasID::Count); //TODO(load blocks)
    }

    GameRenderer::~GameRenderer() = default;

    void GameRenderer::drawTank(const Tank&) {
        //TODO(drawTank)
    }

    void GameRenderer::drawMap(const Map&) {
        //TODO(drawMap)
    }

}