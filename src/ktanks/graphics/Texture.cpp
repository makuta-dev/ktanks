#include "Texture.h"

#include <vector>

#include "spng.h"
#include "glad/gl.h"

namespace ktanks {

    Texture::Texture() = default;

    Texture::Texture(const glm::uvec2& size) : m_size(size) {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            static_cast<GLsizei>(m_size.x),
            static_cast<GLsizei>(m_size.y),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            nullptr
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::Texture(const uint32_t id, const glm::uvec2 &size) : m_id(id), m_size(size) {}

    Texture::~Texture() { if (m_id) glDeleteTextures(1, &m_id); }

    Texture::Texture(Texture&& other) noexcept : m_id(other.m_id), m_size(other.m_size) {
        other.m_id = 0;
    }

    Texture& Texture::operator=(Texture&& other) noexcept {
        if (this != &other) {
            if (m_id) glDeleteTextures(1, &m_id);
            m_id = other.m_id; m_size = other.m_size;
            other.m_id = 0;
        }
        return *this;
    }

    void Texture::bind(const uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::unbind() const {
        if (m_id){
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    Texture Texture::loadFile(const std::string& path) {
        FILE* f = fopen(path.c_str(), "rb");
        if (!f) return {};

        spng_ctx* ctx = spng_ctx_new(0);
        spng_set_png_file(ctx, f);

        size_t out_size;
        spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size);
        std::vector<unsigned char> data(out_size);
        spng_decode_image(ctx, data.data(), out_size, SPNG_FMT_RGBA8,SPNG_DECODE_TRNS);

        spng_ihdr ihdr{};
        spng_get_ihdr(ctx, &ihdr);

        Texture tex;
        tex.m_size.x = ihdr.width;
        tex.m_size.y = ihdr.height;

        glGenTextures(1, &tex.m_id);
        glBindTexture(GL_TEXTURE_2D, tex.m_id);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA8,
            static_cast<GLsizei>(tex.m_size.x),
            static_cast<GLsizei>(tex.m_size.y),
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            data.data()
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        spng_ctx_free(ctx);
        fclose(f);
        return tex;
    }

    glm::uvec2 Texture::getSize() const {
        return m_size;
    }

    uint32_t Texture::getWidth() const {
        return getSize().x;
    }

    uint32_t Texture::getHeight() const {
        return getSize().y;
    }

    uint32_t Texture::getID() const {
        return m_id;
    }

}
