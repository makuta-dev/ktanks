#include "Map.h"

#include <random>
#include <spdlog/spdlog.h>

namespace ktanks {

    Map::Map(const glm::uvec2& size) : m_size(size),
        data(size.x * size.y, TerrainSprite::Sand1) {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dis(0.0, 1.0);

        for(int x = 0; x < size.x; x++) {
            for(int y = 0; y < size.y; y++) {
                if (dis(gen) < 0.33){
                    set({x,y},TerrainSprite::Grass2);
                }
                if (dis(gen) >= 0.33 && dis(gen) < 0.66) {
                    set({x,y},TerrainSprite::Grass2);
                }
            }
        }
    }

    TerrainSprite Map::get(const glm::uvec2 &pos) const {
        if (pos.x < m_size.x && pos.y < m_size.y) {
            return data[getIndex(pos)];
        }
        spdlog::warn("Cannot load sprite at [{},{}] - out of bounds", pos.x, pos.y);
        return TerrainSprite::Sand1;
    }

    void Map::set(const glm::uvec2 &pos, const TerrainSprite sprite) {
        if (pos.x < m_size.x && pos.y < m_size.y) {
            data[getIndex(pos)] = sprite;
            return;
        }
        spdlog::warn("Cannot put sprite in [{},{}] - out of bounds", pos.x, pos.y);
    }

    std::size_t Map::getIndex(const glm::uvec2 &pos) const {
        return pos.x * m_size.x + pos.y;
    }

    glm::uvec2 Map::getSize() const {
        return m_size;
    }

}
