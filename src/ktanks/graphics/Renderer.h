#ifndef KTANKS_RENDERER_H
#define KTANKS_RENDERER_H

#include <memory>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

#include "Shader.h"

namespace ktanks {

    struct QuadInstance {
        glm::vec2 pos;
        glm::vec2 size;
        glm::vec4 color;
        float thickness;
        float radius;
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

        void drawRect(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& col, float w = 0.0f);
        void drawCircle(const glm::vec2& pos, float radius, const glm::vec4& col, float w = 0.0f);
        void drawEllipse(const glm::vec2& pos, const glm::vec2& radius, const glm::vec4& col, float w = 0.0f);
        void drawRoundedRect(const glm::vec2& pos, const glm::vec2& size, float radius, const glm::vec4& col, float w = 0.0f);

    private:
        void pushQuad(const glm::vec2& p, const glm::vec2& s, const glm::vec4& c, float w, int type, float r = 0.0f);

        uint32_t m_vao{0}, m_vbo_static{0}, m_vbo_instances{0};
        glm::mat4 m_projection{1.f};
        std::shared_ptr<Shader> m_shader;
        std::vector<QuadInstance> m_instances;
    };

}

#endif //KTANKS_RENDERER_H