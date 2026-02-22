#ifndef KTANKS_MAP_H
#define KTANKS_MAP_H

#include "ktanks/graphics/Renderer.h"
#include "ktanks/graphics/sprite_data/TerrainSprites.h"

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