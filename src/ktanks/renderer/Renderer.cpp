#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "glad/gl.h"

namespace ktanks {

    Renderer::Renderer(AssetManager& asset_manager) {
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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Renderer::~Renderer() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);

        glDisable(GL_BLEND);
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
        setTexture(font.getTextureID(),true);
        m_color = color;
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

}
