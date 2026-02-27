#include "Renderer.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ktanks/utils/Locator.h"

namespace ktanks {

    constexpr size_t MAX_QUADS = 1000;
    constexpr size_t MAX_VERTICES = MAX_QUADS * 4;
    constexpr size_t MAX_INDICES = MAX_QUADS * 6;


    Renderer::Renderer() {
        glCreateVertexArrays(1, &m_vao);
        glCreateBuffers(1, &m_vbo);
        glCreateBuffers(1, &m_ibo);

        glNamedBufferStorage(m_vbo, MAX_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_STORAGE_BIT);
        glNamedBufferStorage(m_ibo, MAX_INDICES * sizeof(uint32_t), nullptr, GL_DYNAMIC_STORAGE_BIT);

        glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(Vertex));
        glVertexArrayElementBuffer(m_vao, m_ibo);

        glEnableVertexArrayAttrib(m_vao, 0);
        glEnableVertexArrayAttrib(m_vao, 1);
        glEnableVertexArrayAttrib(m_vao, 2);
        glEnableVertexArrayAttrib(m_vao, 3);
        glEnableVertexArrayAttrib(m_vao, 4);
        glEnableVertexArrayAttrib(m_vao, 5);

        glVertexArrayAttribFormat(m_vao, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));
        glVertexArrayAttribFormat(m_vao, 1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv));
        glVertexArrayAttribFormat(m_vao, 2, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, color));
        glVertexArrayAttribFormat(m_vao, 3, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, size));
        glVertexArrayAttribFormat(m_vao, 4, 1, GL_FLOAT, GL_FALSE, offsetof(Vertex, thickness));
        glVertexArrayAttribIFormat(m_vao, 5, 1, GL_INT, offsetof(Vertex, type));

        for (int i = 0; i < 6; i++) glVertexArrayAttribBinding(m_vao, i, 0);

        std::vector<uint32_t> indices(MAX_INDICES);
        uint32_t offset = 0;
        for (size_t i = 0; i < MAX_INDICES; i += 6) {
            indices[i + 0] = offset + 0; indices[i + 1] = offset + 1; indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2; indices[i + 4] = offset + 3; indices[i + 5] = offset + 0;
            offset += 4;
        }
        glNamedBufferSubData(m_ibo, 0, static_cast<GLsizeiptr>(indices.size() * sizeof(uint32_t)), indices.data());

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Renderer::~Renderer() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ibo);
    }

    void Renderer::resize(const glm::ivec2& size) {
        m_projection = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f, -1.0f, 1.0f);
    }

    void Renderer::beginDraw() {
        if (!m_shader) {
            m_shader = Locator::getAssets().getShader("vector");
        }
        m_vertexBatch.clear();
    }

    void Renderer::flush() {
        if (m_vertexBatch.empty()) return;

        m_shader->use();
        m_shader->setMat4("u_projection", m_projection);

        glNamedBufferSubData(m_vbo, 0, static_cast<GLsizeiptr>(m_vertexBatch.size() * sizeof(Vertex)), m_vertexBatch.data());

        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_vertexBatch.size() / 4 * 6), GL_UNSIGNED_INT, nullptr);

        m_vertexBatch.clear();
    }

    void Renderer::endDraw(){ flush(); }

    void Renderer::drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, const float w) {
        pushQuad(pos, size, color, w, 0);
    }

    void Renderer::drawCircle(const glm::vec2& pos, const float radius, const glm::vec4& color, const float w) {
        pushQuad(pos - radius, glm::vec2(radius * 2.0f), color, w, 1);
    }

    void Renderer::drawEllipse(const glm::vec2& pos, const glm::vec2& radius, const glm::vec4& color, const float w) {
        pushQuad(pos - radius, radius * 2.0f, color, w, 1);
    }

    void Renderer::pushQuad(const glm::vec2& p, const glm::vec2& s, const glm::vec4& c, float w, int type) {
        if (m_vertexBatch.size() + 4 >= MAX_VERTICES) flush();

        m_vertexBatch.push_back({ {p.x,     p.y},     {-1, -1}, c,s, w, type });
        m_vertexBatch.push_back({ {p.x + s.x, p.y},     { 1, -1}, c,s, w, type });
        m_vertexBatch.push_back({ {p.x + s.x, p.y + s.y}, { 1,  1}, c,s, w, type });
        m_vertexBatch.push_back({ {p.x,     p.y + s.y}, {-1,  1}, c,s, w, type });
    }

}
