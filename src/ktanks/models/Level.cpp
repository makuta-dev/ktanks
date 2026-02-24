#include "Level.h"

namespace ktanks {

    Level::Level() : Level({1,1}) {}
    Level::Level(const glm::uvec2& size) : m_size{size}, m_terrain(size), m_blocks(size * 4u) {}

    glm::uvec2 Level::getSize() const {
        return m_size;
    }

    LevelMap<TerrainSprite> Level::getTerrain() const {
        return m_terrain;
    }

    LevelMap<BlockID> Level::getBlocks() const {
        return m_blocks;
    }

}