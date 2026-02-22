#include "TextureAtlas.h"

#include "glad/gl.h"

namespace ktanks {

    TextureAtlas::TextureAtlas(const int len, const glm::uvec2& size)
        : m_texture(size), m_regions(len,{{0,0},{1,1}}) {}

    TextureAtlas::TextureAtlas(TextureAtlas&& other) noexcept
        : m_texture(std::move(other.m_texture)), m_regions(std::move(other.m_regions)) {}

    TextureAtlas& TextureAtlas::operator=(TextureAtlas&& other) noexcept {
        if (this != &other) {
            m_texture = std::move(other.m_texture);
            m_regions = std::move(other.m_regions);
        }
        return *this;
    }

    std::size_t TextureAtlas::insert(const glm::uvec2& pos, const glm::uvec2& size, const void* data) {
        const int id = static_cast<int>(m_regions.size()) - 1;
        insert(id,pos,size,data);
        return id;
    }

    void TextureAtlas::reserve(const int i) {
        m_regions.reserve(i);
    }

    bool TextureAtlas::insert(const int id, const glm::uvec2& pos, const glm::uvec2& size, const void* data) {
        if (pos.x + size.x > m_texture.getWidth() ||
            pos.y + size.y > m_texture.getHeight() ||
            id >= m_regions.capacity())
        {
            return false;
        }
        m_texture.bind();

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            static_cast<GLint>(pos.x),
            static_cast<GLint>(pos.y),
            static_cast<GLint>(size.x),
            static_cast<GLint>(size.y),
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data
        );

        m_texture.unbind();

        const auto fw = static_cast<float>(m_texture.getWidth());
        const auto fh = static_cast<float>(m_texture.getHeight());

        const float texel_x = 0.5f / fw;
        const float texel_y = 0.5f / fh;

        Region reg{};
        reg.a = glm::vec2(
            static_cast<float>(pos.x) / fw + texel_x,
            static_cast<float>(pos.y) / fh + texel_y
        );
        reg.b = glm::vec2(
            static_cast<float>(pos.x + size.x) / fw - texel_x,
            static_cast<float>(pos.y + size.y) / fh - texel_y
        );

        reg.size = size;

        m_regions[id] = reg;
        return true;
    }


    std::optional<Region> TextureAtlas::at(const std::size_t x) const {
        if (x < m_regions.size()) {
            return m_regions[x];
        }
        return std::nullopt;
    }

    uint32_t TextureAtlas::getTextureID() const {
        return m_texture.getID();
    }

}
