#ifndef KTANKS_LEVELMAP_H
#define KTANKS_LEVELMAP_H

#include <vector>
#include <glm/vec2.hpp>

namespace ktanks {

    template<typename T>
    class LevelMap final {
    public:
        explicit LevelMap(const glm::uvec2& size, const T& init = T{})
            : m_size(size), m_data(size.x * size.y, init) {}

        [[nodiscard]] bool isInBounds(const glm::uvec2& pos) const {
            return pos.x < m_size.x && pos.y < m_size.y;
        }

        const T& get(const glm::uvec2& pos) const {
            assert(isInBounds(pos) && "Out of bounds map access!");
            return m_data[pos.y * m_size.x + pos.x];
        }

        void set(const glm::uvec2& pos, const T& value) {
            if (isInBounds(pos)) {
                m_data[pos.y * m_size.x + pos.x] = value;
            }
        }

        [[nodiscard]] glm::uvec2 getSize() const { return m_size; }

    private:
        glm::uvec2 m_size;
        std::vector<T> m_data;
    };

}

#endif //KTANKS_LEVELMAP_H