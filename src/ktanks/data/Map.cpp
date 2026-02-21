#include "Map.h"

#include <random>
#include <spdlog/spdlog.h>

namespace ktanks {

    Map::Map(const glm::uvec2& size) : m_size(size),
        data(size.x * size.y, TerrainSprite::Sand1) {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        for(int x = 0; x < size.x; x++) {
            for(int y = 0; y < size.y; y++) {
                if (dis(gen) < 0.45){
                    set({x,y},TerrainSprite::Sand2);
                }
            }
        }

    }

    void Map::draw(Renderer &r, const glm::vec2& sprite_size) const {
        auto pos = glm::uvec2(0);
        for (const auto& sprite : data) {
            r.drawTerrain(glm::vec2(pos) * sprite_size,sprite_size, sprite);
            pos.x++;
            if (pos.x >= m_size.x) {
                pos.x = 0;
                pos.y++;
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

    Map Map::load(const std::string &path) {
        spdlog::warn("loading maps is not implemented yet");
        //TODO(implement loading maps from files)
        return Map({0,0});
    }

}
