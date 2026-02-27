#ifndef KTANKS_RENDERER_H
#define KTANKS_RENDERER_H

#include <memory>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

#include "Shader.h"

namespace ktanks {

    struct Vertex {
        glm::vec2 pos;
        glm::vec2 uv;
        glm::vec4 color;
        glm::vec2 size;
        float thickness;
        int type;
    };

    class Renderer final {
    public:
        Renderer();
        ~Renderer();

        void resize(const glm::ivec2& size);

        void beginDraw();
        void flush();
        void endDraw();

        void drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, float w = 0.f);
        void drawCircle(const glm::vec2& pos, float radius, const glm::vec4& color, float w = 0.f);
        void drawEllipse(const glm::vec2& pos, const glm::vec2& radius, const glm::vec4& color, float w = 0.f);

    private:
        void pushQuad(const glm::vec2& p, const glm::vec2& s, const glm::vec4& c, float w, int type);

        uint32_t m_vao{0}, m_vbo{0}, m_ibo{0};
        std::vector<Vertex> m_vertexBatch;
        std::vector<uint32_t> m_indexBatch;
        std::shared_ptr<Shader> m_shader;
        glm::mat4 m_projection{1.f};
    };

}

#endif //KTANKS_RENDERER_H