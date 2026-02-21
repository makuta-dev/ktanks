#ifndef KTANKS_FONT_H
#define KTANKS_FONT_H

#include <unordered_map>

#include "ktanks/graphics/TextureAtlas.h"

namespace ktanks {

    struct Glyph final {
        Region uv;
        glm::ivec2 size;
        glm::ivec2 bearing;
        uint32_t advance;
    };

    class Font final{
    public:
        Font() = default;
        explicit Font(const std::string& path, int size = 16);
        ~Font();

        Font(Font&& other) noexcept;
        Font& operator=(Font&& other) noexcept;

        [[nodiscard]] std::optional<Glyph> get(int code) const;
        [[nodiscard]] uint32_t getTextureID() const;
        [[nodiscard]] int getSize() const;

    private:
        int m_height{-1};
        Texture m_texture;
        std::unordered_map<int, Glyph> m_glyphs;
    };

}

#endif //KTANKS_FONT_H