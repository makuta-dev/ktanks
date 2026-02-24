#ifndef KTANKS_LEVELMAP_H
#define KTANKS_LEVELMAP_H

#include <vector>
#include <glm/vec2.hpp>

namespace ktanks {

    template<typename T>
    class LevelMap final {
    public:
        LevelMap() : LevelMap({1,1}){}

        explicit LevelMap(const glm::uvec2& size) : m_size(size), m_data(size.x * size.y,static_cast<T>(0)){}

        T get(const glm::uvec2& pos) const {
            if (pos.x < m_size.x || pos.y < m_size.y) {
                return m_data[pos.y * m_size.x + pos.x];
            }
            return static_cast<T>(0);
        }

        void set(const glm::uvec2& pos, T value) {
            if (pos.x < m_size.x || pos.y < m_size.y) {
                m_data[pos.y * m_size.x + pos.x] = value;
            }
        }

    private:
        glm::uvec2 m_size;
        std::vector<T> m_data;
    };

}

#endif //KTANKS_LEVELMAP_H