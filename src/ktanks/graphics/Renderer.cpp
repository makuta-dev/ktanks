#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "glad/gl.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    Renderer::Renderer() {
        const auto assetManager = AssetManager();

        m_terrain_atlas = assetManager.getTerrainAtlas();
        m_shader = assetManager.getShader("simple");

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, pos)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, uv)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 15000 * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);

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

    void Renderer::flush() {
        if (m_indices.empty()) return;

        m_shader.use();
        m_shader.setMat4("proj", m_projection);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_terrain_atlas.getTextureID());

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(m_vertices.size() * sizeof(Vertex)), m_vertices.data());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(m_indices.size() * sizeof(uint32_t)), m_indices.data());

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, nullptr);

        glBindVertexArray(0);
    }

    void Renderer::drawTerrain(const glm::vec2& pos, const glm::vec2& size, TerrainSprite sprite) {
        auto regionOpt = m_terrain_atlas.at(static_cast<std::size_t>(sprite));
        if (!regionOpt) return;

        const auto [a, b] = *regionOpt;
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

}
