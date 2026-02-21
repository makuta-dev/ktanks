#ifndef KTANKS_MAP_H
#define KTANKS_MAP_H

#include "ktanks/graphics/Renderer.h"

namespace ktanks {

    class Map final {
    public:
        explicit Map(const glm::uvec2 &size = {64,48});

        void draw(Renderer &r, const glm::vec2& sprite_size) const;

        [[nodiscard]] TerrainSprite get(const glm::uvec2 &pos) const;
        void set(const glm::uvec2 &pos,TerrainSprite);

        static Map load(const std::string &path);

    private:
        std::size_t getIndex(const glm::uvec2 &pos) const;

        glm::uvec2 m_size;
        std::vector<TerrainSprite> data;
    };

}

#endif //KTANKS_MAP_H