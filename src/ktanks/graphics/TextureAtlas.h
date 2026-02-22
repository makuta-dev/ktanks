#ifndef KTANKS_TEXTUREATLAS_H
#define KTANKS_TEXTUREATLAS_H

#include <vector>

#include "ktanks/graphics/Texture.h"

namespace ktanks {

    struct Region {
        glm::vec2 a;
        glm::vec2 b;
        glm::uvec2 size;
    };

    class TextureAtlas {
    public:
        explicit TextureAtlas(const glm::uvec2& size = {512,512});
        ~TextureAtlas() = default;

        TextureAtlas(TextureAtlas&& other) noexcept;
        TextureAtlas& operator=(TextureAtlas&& other) noexcept;

        std::size_t insert(const glm::uvec2& pos, const glm::uvec2& size, const void* data);

        [[nodiscard]] std::optional<Region> at(std::size_t x) const;
        [[nodiscard]] uint32_t getTextureID() const;

    private:
        Texture m_texture;
        std::vector<Region> m_regions;
    };

}

#endif //KTANKS_TEXTUREATLAS_H