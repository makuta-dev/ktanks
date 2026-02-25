#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "glad/gl.h"
#include "ktanks/core/Constants.h"

namespace ktanks {

    Renderer::Renderer(AssetManager& asset_manager) : m_assets(asset_manager) {
        m_shader = &asset_manager.getShader(ShaderID::Default);

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, 4096 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, pos)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, uv)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 16384 * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

        glBindVertexArray(0);
    }

    Renderer::~Renderer() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    void Renderer::resize(const int w, const int h) {
        const auto fw = static_cast<float>(w);
        const auto fh = static_cast<float>(h);
        m_projection = glm::ortho<float>(0.f, fw, fh, 0.f);
        glViewport(0, 0, w, h);
    }

    void Renderer::beginFrame() {
        m_vertices.clear();
        m_indices.clear();
    }

    void Renderer::endFrame() {
        flush();
    }

    void Renderer::setViewMatrix(const glm::mat4 &view) {
        if (m_view != view) {
            flush();
        }
        m_view = view;
    }

    void Renderer::flush() {
        if (m_indices.empty()) return;

        m_shader->use();
        m_shader->setMat4("proj", m_projection);
        m_shader->setMat4("view", m_view);
        m_shader->setInt("is_text", m_is_text);
        m_shader->setVec3("text_col", m_color);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(m_vertices.size() * sizeof(Vertex)), m_vertices.data());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(m_indices.size() * sizeof(uint32_t)), m_indices.data());

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);

        beginFrame();
    }

    void Renderer::setTexture(const uint32_t texture_id, const bool is_text) {
        if (m_texture != texture_id || m_is_text != is_text) {
            flush();
        }
        m_texture = texture_id;
        m_is_text = is_text;
    }

    void Renderer::drawSprite(const glm::vec2& pos, const glm::vec2& size, const Region& region) {
        const auto [a, b, _] = region;
        const auto offset = static_cast<uint32_t>(m_vertices.size());

        m_vertices.push_back({{pos.x, pos.y},               {a.x, a.y}});
        m_vertices.push_back({{pos.x + size.x, pos.y},      {b.x, a.y}});
        m_vertices.push_back({{pos.x + size.x, pos.y + size.y}, {b.x, b.y}});
        m_vertices.push_back({{pos.x, pos.y + size.y},      {a.x, b.y}});

        m_indices.push_back(offset + 0);
        m_indices.push_back(offset + 1);
        m_indices.push_back(offset + 2);
        m_indices.push_back(offset + 2);
        m_indices.push_back(offset + 3);
        m_indices.push_back(offset + 0);
    }

    void Renderer::drawSprite(const glm::vec2& pos, const glm::vec2& size, const float angle, const glm::vec2& center, const Region& region) {
        const auto [a, b, _] = region;
        const auto offset = static_cast<uint32_t>(m_vertices.size());

        const auto origin = size * center;
        const float s = std::sin(angle);
        const float c = std::cos(angle);

        const glm::vec2 corners[4] = {
            { 0.0f,   0.0f },
            { size.x, 0.0f },
            { size.x, size.y },
            { 0.0f,   size.y }
        };

        const glm::vec2 uv[4] = {
            {a.x, a.y}, {b.x, a.y}, {b.x, b.y}, {a.x, b.y}
        };

        for (int i = 0; i < 4; i++) {
            const float x = corners[i].x - origin.x;
            const float y = corners[i].y - origin.y;

            const float x_new = x * c - y * s;
            const float y_new = x * s + y * c;

            m_vertices.push_back({
                { x_new + pos.x + center.x, y_new + pos.y + center.y },
                uv[i]
            });
        }

        m_indices.push_back(offset + 0);
        m_indices.push_back(offset + 1);
        m_indices.push_back(offset + 2);
        m_indices.push_back(offset + 2);
        m_indices.push_back(offset + 3);
        m_indices.push_back(offset + 0);
    }

    void Renderer::drawText(const std::string& text, const glm::vec2& pos, const glm::vec3& color, const Font& font) {
        if (m_color != color) {
            flush();
            m_color = color;
        }

        setTexture(font.getTextureID(),true);
        auto p = pos;
        for (const auto& c : text) {
            if (const auto glyph = font.get(c)) {
                auto ps = p;
                ps.x += static_cast<float>(glyph->bearing.x);
                ps.y -= static_cast<float>(glyph->bearing.y);

                drawSprite(ps,glyph->size,glyph->uv);

                p.x += static_cast<float>(glyph->advance);
            }
        }
    }

    void Renderer::drawTank(const Tank& t) {
        const auto m_tank_atlas = &m_assets.getTextureAtlas(AtlasID::Tanks);
        const auto color = static_cast<int>(t.getColor());
        setTexture(m_tank_atlas->getTextureID());
        if (const auto body_req = m_tank_atlas->at(color * 5 + static_cast<int>(TankSprites::Body))) {
            const auto body_rot = glm::radians(t.getBodyRotation() - 90.f);
            drawSprite(t.getPos(),body_req->size,body_rot,glm::vec2{0.5},*body_req);
            if (const auto barrel_req = m_tank_atlas->at(color * 5 + static_cast<int>(TankSprites::Barrel))) {
                const auto barrel_rot = body_rot + glm::radians(t.getBarrelRotation());
                drawSprite(t.getPos(),barrel_req->size,barrel_rot,glm::vec2{0.5, 0.1},*barrel_req);
            }
        }
    }

    void Renderer::drawLevel(const Level& l) {
        drawTerrain(l.getTerrain());
        drawBlocks(l.getBlocks());
    }

    void Renderer::drawTerrain(const LevelMap<TerrainSprite>& data) {
        const auto m_terrain_atlas = &m_assets.getTextureAtlas(AtlasID::Terrain);
        setTexture(m_terrain_atlas->getTextureID());
        for (int y = 0; y < data.getSize().y; y++) {
            for (int x = 0; x < data.getSize().x; x++) {
                const auto pos = glm::uvec2(x,y);
                const auto tile = static_cast<int>(data.get(pos));
                if (const auto tile_req = m_terrain_atlas->at(tile)) {
                    drawSprite(glm::vec2(pos) * TILE_SIZE,TILE_SIZE,*tile_req);
                }
            }
        }
    }

    void Renderer::drawBlocks(const LevelMap<BlockID>& data) {
        const auto m_block_atlas = &m_assets.getTextureAtlas(AtlasID::Blocks);
        setTexture(m_block_atlas->getTextureID());
        for (int y = 0; y < data.getSize().y; y++) {
            for (int x = 0; x < data.getSize().x; x++) {
                const auto pos = glm::uvec2(x,y);
                const auto tile = static_cast<int>(data.get(pos));
                if (const auto tile_req = m_block_atlas->at(tile)) {
                    drawSprite(glm::vec2(pos) * BLOCK_SIZE,BLOCK_SIZE,*tile_req);
                }
            }
        }
    }

    void Renderer::text(const std::string& text, const glm::vec2& pos, const glm::vec3& col) {
        const auto m_font = &m_assets.getFont(FontID::Regular);
        drawText(text, pos, col, *m_font);
    }

    void Renderer::textCentered(const std::string& text, const glm::vec2& pos, const glm::vec3& col) {
        const auto m_font = &m_assets.getFont(FontID::Regular);
        const auto size = m_font->measureText(text);
        drawText(text, pos - size / 2.f, col, *m_font);
    }

    void Renderer::icon(const glm::vec2& pos, const glm::vec2& size, Icon icon) {
        const auto m_atlas = &m_assets.getTextureAtlas(AtlasID::GUI);
        setTexture(m_atlas->getTextureID());
        if (const auto icon_reg = m_atlas->at(static_cast<int>(icon))) {
            drawSprite(pos,size,*icon_reg);
        }
    }

    void Renderer::draw(const glm::vec2& pos, const glm::vec2& size, GuiSprites sprite) {
        const auto m_atlas = &m_assets.getTextureAtlas(AtlasID::GUI);
        setTexture(m_atlas->getTextureID());
        if (const auto sprite_reg = m_atlas->at(static_cast<int>(sprite))) {
            drawSprite(pos,size,*sprite_reg);
        }
    }

    void Renderer::drawPatch(const glm::vec2& pos, const glm::vec2& size, GuiSprites sprite, const float margin) {
        const auto m_atlas = &m_assets.getTextureAtlas(AtlasID::GUI);
        const auto sprite_reg = m_atlas->at(static_cast<int>(sprite));
        if (!sprite_reg) return;

        setTexture(m_atlas->getTextureID());

        float x_sizes[3] = { margin, size.x - 2.0f * margin, margin };
        float y_sizes[3] = { margin, size.y - 2.0f * margin, margin };

        const glm::vec2 uv_total = sprite_reg->b - sprite_reg->a;
        const glm::vec2 uv_margin = uv_total / glm::vec2(sprite_reg->size) * margin;

        float x_uvs[4] = {
            sprite_reg->a.x,
            sprite_reg->a.x + uv_margin.x,
            sprite_reg->b.x - uv_margin.x,
            sprite_reg->b.x
        };

        float y_uvs[4] = {
            sprite_reg->a.y,
            sprite_reg->a.y + uv_margin.y,
            sprite_reg->b.y - uv_margin.y,
            sprite_reg->b.y
        };

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (x_sizes[i] <= 0.0f || y_sizes[j] <= 0.0f) continue;

                Region slice{};
                slice.a = { x_uvs[i],     y_uvs[j] };
                slice.b = { x_uvs[i + 1], y_uvs[j + 1] };
                slice.size = { static_cast<unsigned int>(margin), static_cast<unsigned int>(margin) };

                glm::vec2 segmentPos = {
                    pos.x + (i > 0 ? x_sizes[0] : 0) + (i > 1 ? x_sizes[1] : 0),
                    pos.y + (j > 0 ? y_sizes[0] : 0) + (j > 1 ? y_sizes[1] : 0)
                };

                drawSprite(segmentPos, { x_sizes[i], y_sizes[j] }, slice);
            }
        }
    }

    glm::vec2 Renderer::measureText(const std::string& text) const {
        const auto m_font = &m_assets.getFont(FontID::Regular);
        return m_font->measureText(text);
    }

}
