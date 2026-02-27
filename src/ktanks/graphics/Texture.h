#ifndef KTANKS_TEXTURE_H
#define KTANKS_TEXTURE_H

#include <string>
#include <glm/vec2.hpp>

namespace ktanks {

    class Texture {
    public:
        explicit Texture(const std::string& path);
        ~Texture();

        void bind(uint32_t slot = 0) const;

        [[nodiscard]] uint32_t getID() const { return m_id; }
        [[nodiscard]] glm::ivec2 getSize() const { return m_size; }

    private:
        uint32_t m_id;
        glm::ivec2 m_size;
    };

}

#endif //KTANKS_TEXTURE_H