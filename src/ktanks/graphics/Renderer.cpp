#include "Renderer.h"

#include <glad/gl.h>
#include <glm/gtc/matrix_transform.hpp>

#include "ktanks/utils/Locator.h"

namespace ktanks {
    constexpr size_t MAX_QUADS = 1000;
    constexpr size_t MAX_VERTICES = MAX_QUADS * 4;
    constexpr size_t MAX_INDICES = MAX_QUADS * 6;

    Renderer::Renderer() {
        const float vertices[] = { 0,0,  1,0,  1,1,  0,1 };
        glCreateBuffers(1, &m_vbo_static);
        glNamedBufferStorage(m_vbo_static, sizeof(vertices), vertices, 0);

        glCreateBuffers(1, &m_vbo_instances);
        glNamedBufferStorage(m_vbo_instances, MAX_QUADS * sizeof(QuadInstance), nullptr, GL_DYNAMIC_STORAGE_BIT);

        glCreateVertexArrays(1, &m_vao);

        glVertexArrayVertexBuffer(m_vao, 0, m_vbo_static, 0, sizeof(glm::vec2));
        glEnableVertexArrayAttrib(m_vao, 0); // aCorner
        glVertexArrayAttribFormat(m_vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(m_vao, 0, 0);

        glVertexArrayVertexBuffer(m_vao, 1, m_vbo_instances, 0, sizeof(QuadInstance));
        glVertexArrayBindingDivisor(m_vao, 1, 1); // Crucial: Advance 1 per instance

        auto setupAttrib = [&](const int loc, const int count, const size_t offset, const bool isInt = false) {
            glEnableVertexArrayAttrib(m_vao, loc);
            if (isInt) glVertexArrayAttribIFormat(m_vao, loc, count, GL_INT, (GLuint)offset);
            else glVertexArrayAttribFormat(m_vao, loc, count, GL_FLOAT, GL_FALSE, (GLuint)offset);
            glVertexArrayAttribBinding(m_vao, loc, 1);
        };

        setupAttrib(1, 2, offsetof(QuadInstance, pos));
        setupAttrib(2, 2, offsetof(QuadInstance, size));
        setupAttrib(3, 4, offsetof(QuadInstance, color));
        setupAttrib(4, 1, offsetof(QuadInstance, thickness));
        setupAttrib(5, 1, offsetof(QuadInstance, radius));
        setupAttrib(6, 1, offsetof(QuadInstance, type), true);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Renderer::~Renderer() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo_static);
        glDeleteBuffers(1, &m_vbo_instances);
    }

    void Renderer::resize(const glm::ivec2& size) {
        m_projection = glm::ortho(0.0f, static_cast<float>(size.x), static_cast<float>(size.y), 0.0f, -1.0f, 1.0f);
        glViewport(0, 0, size.x, size.y);
    }

    void Renderer::beginDraw() {
        if (!m_shader) {
            m_shader = Locator::getAssets().getShader("vector");
        }
        m_instances.clear();
    }

    void Renderer::flush() {
        if (m_instances.empty()) return;

        glNamedBufferSubData(m_vbo_instances, 0, static_cast<GLsizeiptr>(m_instances.size() * sizeof(QuadInstance)), m_instances.data());

        m_shader->use();
        m_shader->setMat4("u_projection", m_projection);

        glBindVertexArray(m_vao);
        glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, (GLsizei)m_instances.size());

        m_instances.clear();
    }

    void Renderer::endDraw() { flush(); }

    void Renderer::pushQuad(const glm::vec2& p, const glm::vec2& s, const glm::vec4& c, const float w, const int type, const float r) {
        if (m_instances.size() >= MAX_QUADS) flush();
        m_instances.push_back({ p, s, c, w, r, type });
    }

    void Renderer::drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col, float w) {
        pushQuad(pos, size, col, w, 0);
    }

    void Renderer::drawCircle(const glm::vec2& pos, float radius, const glm::vec4& col, float w) {
        pushQuad(pos - radius, glm::vec2(radius * 2.0f), col, w, 1);
    }

    void Renderer::drawEllipse(const glm::vec2& pos, const glm::vec2& radius, const glm::vec4& col, float w) {
        pushQuad(pos - radius, radius * 2.0f, col, w, 1);
    }

    void Renderer::drawRoundedRect(const glm::vec2& pos, const glm::vec2& size, const float radius, const glm::vec4& col, const float w) {
        pushQuad(pos, size, col, w, 2, radius);
    }

}
