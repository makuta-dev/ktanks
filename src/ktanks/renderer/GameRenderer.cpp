#include "GameRenderer.h"

#include <glm/trigonometric.hpp>
#include <spdlog/spdlog.h>

#include "ktanks/core/Constants.h"

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

    void GameRenderer::drawLevel(const Level& l) {
        drawTerrain(l.getTerrain());
        drawBlocks(l.getBlocks());
    }

    void GameRenderer::drawTerrain(const LevelMap<TerrainSprite>& data) {
        setTexture(m_terrain_atlas->getTextureID());
        for (int y = 0; y < data.getSize().y; y++) {
            for (int x = 0; x < data.getSize().x; x++) {
                const auto pos = glm::uvec2(x,y);
                const auto tile = static_cast<int>(data.get(pos));
                if (const auto tile_req = m_terrain_atlas->at(tile)) {
                    drawSprite(glm::vec2(pos) * TILE_SIZE,TILE_SIZE,*tile_req);
                }
            }
        }
    }

    void GameRenderer::drawBlocks(const LevelMap<BlockID>& data) {
        setTexture(m_block_atlas->getTextureID());
        for (int y = 0; y < data.getSize().y; y++) {
            for (int x = 0; x < data.getSize().x; x++) {
                const auto pos = glm::uvec2(x,y);
                const auto tile = static_cast<int>(data.get(pos));
                if (const auto tile_req = m_block_atlas->at(tile)) {
                    drawSprite(glm::vec2(pos) * BLOCK_SIZE,BLOCK_SIZE,*tile_req);
                }
            }
        }
    }


}
