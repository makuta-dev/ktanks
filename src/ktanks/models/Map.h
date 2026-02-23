#ifndef KTANKS_MAP_H
#define KTANKS_MAP_H

#include <vector>

#include <glm/vec2.hpp>

#include "ktanks/core/data/TerrainData.h"

namespace ktanks {

    class Map final {
    public:
        explicit Map(const glm::uvec2 &size = {64,48});

        [[nodiscard]] TerrainSprite get(const glm::uvec2 &pos) const;
        void set(const glm::uvec2 &pos,TerrainSprite);

        [[nodiscard]] glm::uvec2 getSize() const;

    private:
        [[nodiscard]] std::size_t getIndex(const glm::uvec2 &pos) const;

        glm::uvec2 m_size;
        std::vector<TerrainSprite> data;
    };

}

#endif //KTANKS_MAP_H