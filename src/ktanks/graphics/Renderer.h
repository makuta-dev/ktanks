#ifndef KTANKS_RENDERER_H
#define KTANKS_RENDERER_H

#include <cstdint>

#include "ktanks/graphics/Vertex.h"

#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class Renderer final {
    public:
        explicit Renderer(AssetManager&);
        ~Renderer();

        void resize(int w, int h);

        void beginFrame();
        void endFrame();

        void setViewMatrix(const glm::mat4 &view);
        void setTexture(uint32_t texture_id, bool is_text = false);

        void drawSprite(const glm::vec2& pos, const glm::vec2& size, float angle, const glm::vec2& center,const Region&);
        void drawSprite(const glm::vec2& pos, const glm::vec2& size, const Region&);
        void drawText(const std::string& text, const glm::vec2& pos, const glm::vec3& color, const Font& font);

    private:
        void flush();

        uint32_t m_vao{0};
        uint32_t m_vbo{0};
        uint32_t m_ebo{0};
        uint32_t m_texture{0};
        Shader* m_shader;
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        glm::mat4 m_projection{1.f};
        glm::mat4 m_view{1.f};
    };

}

#endif //KTANKS_RENDERER_H