#include "GameRenderer.h"

#include <glm/trigonometric.hpp>

namespace ktanks {

    GameRenderer::GameRenderer(AssetManager& a) : Renderer(a) {
        m_tank_atlas = &a.getTextureAtlas(AtlasID::Tanks);
        m_terrain_atlas = &a.getTextureAtlas(AtlasID::Terrain);
        m_block_atlas = &a.getTextureAtlas(AtlasID::Blocks);
    }

    GameRenderer::~GameRenderer() = default;

    void GameRenderer::drawTank(const Tank& t) {
        const auto color = static_cast<int>(t.getColor());
        setTexture(m_tank_atlas->getTextureID());
        if (const auto body_req = m_tank_atlas->at(color * 5 + static_cast<int>(TankSprites::Body))) {
            const auto body_rot = glm::radians(t.getBodyRotation() - 90.f);
            drawSprite(t.getPos(),body_req->size,body_rot,glm::vec2{0.5},*body_req);
            if (const auto barrel_req = m_tank_atlas->at(color * 5 + static_cast<int>(TankSprites::Barrel))) {
                const auto barrel_rot = body_rot + glm::radians(t.getBarrelRotation());
                drawSprite(t.getPos(),barrel_req->size,barrel_rot,glm::vec2{0.5, 0.1},*barrel_req);
            }
        }
    }

    void GameRenderer::drawLevel(const Level&) {
        //TODO(drawLevel)
    }

}
