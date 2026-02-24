#include "Level.h"

namespace ktanks {

    Level::Level() : Level({1,1}) {}
    Level::Level(const glm::uvec2& size) : m_size{size},
        m_terrain(size,TerrainSprite::Grass1), m_blocks(size * 4u, -1 ) {


        for(int y = 0; y < m_blocks.getSize().y; y++) {
            for(int x = 0; x < m_blocks.getSize().x; x++) {
                if ((x == 0 || x == m_blocks.getSize().x - 1 ||  y == 0 || y == m_blocks.getSize().y - 1)) {
                    m_blocks.set(glm::uvec2{x, y}, 1); // Set edge tile (e.g., Wall)
                }
            }
        }

    }

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