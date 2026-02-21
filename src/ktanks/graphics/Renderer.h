#ifndef KTANKS_RENDERER_H
#define KTANKS_RENDERER_H

#include <cstdint>

#include "ktanks/data/TerrainSpriteList.h"

#include "ktanks/graphics/Shader.h"
#include "ktanks/graphics/TextureAtlas.h"
#include "ktanks/graphics/Vertex.h"

namespace ktanks {

    class Renderer final {
    public:
        Renderer();
        ~Renderer();

        void resize(int w, int h);

        void beginFrame();
        void endFrame();

        void drawTerrain(const glm::vec2& pos, const glm::vec2& size, TerrainSprite);

    private:
        void flush();

        uint32_t m_vao{0};
        uint32_t m_vbo{0};
        uint32_t m_ebo{0};
        uint32_t m_texture{0};
        Shader m_shader;
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        glm::mat4 m_projection{1.f};
        TextureAtlas m_terrain_atlas;
    };

}

#endif //KTANKS_RENDERER_H