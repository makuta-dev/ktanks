#include "Texture.h"

#include <cstdio>
#include <vector>

#include <spng.h>
#include <spdlog/spdlog.h>

#include "glad/gl.h"

namespace ktanks {

    Texture::Texture(const std::string& path) : m_id(0), m_size(0) {
        FILE* f = fopen(path.c_str(), "rb");
        if (!f) {
            spdlog::error("Failed to open image: {}", path);
            return;
        }

        spng_ctx* ctx = spng_ctx_new(0);
        spng_set_png_file(ctx, f);

        spng_ihdr ihdr{};
        spng_get_ihdr(ctx, &ihdr);
        m_size = { ihdr.width, ihdr.height };

        size_t out_size;
        spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size);

        std::vector<unsigned char> data(out_size);
        if (spng_decode_image(ctx, data.data(), out_size, SPNG_FMT_RGBA8, SPNG_DECODE_TRNS)) {
            spdlog::error("Failed to decode PNG: {}", path);
            spng_ctx_free(ctx);
            fclose(f);
            return;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glTextureStorage2D(m_id, 1, GL_RGBA8, m_size.x, m_size.y);
        glTextureSubImage2D(m_id, 0, 0, 0, m_size.x, m_size.y, GL_RGBA, GL_UNSIGNED_BYTE, data.data());

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        spng_ctx_free(ctx);
        fclose(f);
        spdlog::info("Loaded texture: {} ({}x{})", path, m_size.x, m_size.y);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &m_id);
    }

    void Texture::bind(const uint32_t slot) const {
        glBindTextureUnit(slot, m_id);
    }

}
