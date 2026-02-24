#ifndef KTANKS_LEVEL_H
#define KTANKS_LEVEL_H

#include <glm/vec2.hpp>

#include "ktanks/core/data/BlockData.h"
#include "ktanks/models/LevelMap.h"
#include "ktanks/core/data/TerrainData.h"

namespace ktanks {

    class Level final {
    public:
        Level();
        explicit Level(const glm::uvec2& size);

        [[nodiscard]] glm::uvec2 getSize() const;
        [[nodiscard]] LevelMap<TerrainSprite> getTerrain() const;
        [[nodiscard]] LevelMap<BlockID> getBlocks() const;

    private:
        glm::uvec2 m_size;
        LevelMap<TerrainSprite> m_terrain;
        LevelMap<BlockID> m_blocks;
    };

}

#endif //KTANKS_LEVEL_H