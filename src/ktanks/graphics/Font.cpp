#include "Font.h"

#include <spdlog/spdlog.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H

#include "glad/gl.h"

namespace ktanks {

    Font::Font(const std::string& path, const int size) : m_height(size) {
        m_height = size;

        FT_Library ft;
        if (const auto code = FT_Init_FreeType(&ft); code) {
            spdlog::error("Cannot init Freetype Library: {}", FT_Error_String(code));
            return;
        }

        constexpr uint32_t padding = 8;
        FT_Property_Set(ft, "sdf", "spread", &padding);

        FT_Face face;
        if (const auto code = FT_New_Face(ft, path.c_str(), 0, &face); code) {
            spdlog::error("Cannot load font file {}: ", path, FT_Error_String(code));
            FT_Done_FreeType(ft);
            return;
        }

        m_ascender = static_cast<int>(face->size->metrics.ascender >> 6);
        m_descender = static_cast<int>(face->size->metrics.descender >> 6);

        constexpr auto atlas_size = glm::uvec2(1024);
        auto tex = 0u;
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            static_cast<GLsizei>(atlas_size.x),
            static_cast<GLsizei>(atlas_size.y),
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            nullptr
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        FT_Set_Pixel_Sizes(face, 0, size);
        glm::uvec2 cursor{padding};
        uint32_t maxHeightInRow = 0;

        for (unsigned char c = 32; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                continue;
            }
            FT_Render_Glyph(face->glyph, FT_RENDER_MODE_SDF);

            FT_Bitmap& bitmap = face->glyph->bitmap;
            uint32_t w = bitmap.width;
            uint32_t h = bitmap.rows;

            if (cursor.x + w + padding > atlas_size.x) {
                cursor.x = 0;
                cursor.y += maxHeightInRow + padding;
                maxHeightInRow = h;
            }

            glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                static_cast<GLint>(cursor.x),
                static_cast<GLint>(cursor.y),
                static_cast<GLint>(w),
                static_cast<GLint>(h),
                GL_RED,
                GL_UNSIGNED_BYTE,
                 bitmap.buffer
            );

            Region region{};

            region.a.x = static_cast<float>(cursor.x) / static_cast<float>(atlas_size.x);
            region.a.y = static_cast<float>(cursor.y) / static_cast<float>(atlas_size.y);

            region.b.x = static_cast<float>(cursor.x + w) / static_cast<float>(atlas_size.x);
            region.b.y = static_cast<float>(cursor.y + h) / static_cast<float>(atlas_size.y);

            m_glyphs[c] = Glyph{
                .uv = region,
                .size = { static_cast<int>(w), static_cast<int>(h) },
                .bearing = { face->glyph->bitmap_left, face->glyph->bitmap_top },
                .advance = static_cast<uint32_t>(face->glyph->advance.x >> 6)
            };

            cursor.x += w + padding;
            maxHeightInRow = std::max(maxHeightInRow, h);
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        m_texture = Texture(tex,atlas_size);
    }

    Font::~Font() {
        m_glyphs.clear();
    }

    Font::Font(Font&& other) noexcept : m_height(other.m_height),
        m_texture(std::move(other.m_texture)), m_glyphs(std::move(other.m_glyphs)) {}

    Font& Font::operator=(Font&& other) noexcept {
        if (this != &other) {
            m_height = other.m_height;
            m_texture = std::move(other.m_texture);
            m_glyphs = std::move(other.m_glyphs);

            other.m_glyphs.clear();
            other.m_height = -1;
        }
        return *this;
    }

    std::optional<Glyph> Font::get(const int code) const {
        if (m_glyphs.contains(code)) {
            return m_glyphs.at(code);
        }
        return std::nullopt;
    }

    uint32_t Font::getTextureID() const {
        return m_texture.getID();
    }

    int Font::getHeight() const {
        return m_height;
    }

    int Font::getAscender() const {
        return m_ascender;
    }

    int Font::getDescender() const {
        return m_descender;
    }

    glm::vec2 Font::measureText(const std::string &text) const {
        glm::vec2 totalSize{0.0f, static_cast<float>(m_height)};
        float currentLineWidth = 0.0f;

        for (const auto& c : text) {
            if (c == '\n') {
                totalSize.x = std::max(totalSize.x, currentLineWidth);
                totalSize.y += static_cast<float>(m_height);
                currentLineWidth = 0.0f;
                continue;
            }

            if (const auto glyphOpt = get(c)) {
                currentLineWidth += static_cast<float>(glyphOpt->advance);
            }
        }

        totalSize.x = std::max(totalSize.x, currentLineWidth);
        return totalSize;
    }
}
