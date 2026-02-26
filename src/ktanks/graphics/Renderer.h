#ifndef KTANKS_RENDERER_H
#define KTANKS_RENDERER_H

#include <cstdint>

#include "ktanks/core/data/GuiData.h"
#include "ktanks/graphics/Vertex.h"
#include "ktanks/models/entity/Tank.h"
#include "ktanks/models/Level.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class Renderer {
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
        void drawSprite(const glm::vec2& pos, const glm::vec2& size, const Region&, float margin);
        void drawText(const std::string& text, const glm::vec2& pos, const glm::vec3& color, const Font& font);

        void drawTank(const Tank&);
        void drawLevel(const Level&);
        void drawTerrain(const LevelMap<TerrainSprite>&);
        void drawBlocks(const LevelMap<BlockID>&);

        void text(const std::string& text, const glm::vec2& pos, const glm::vec3& col);
        void textCentered(const std::string& text, const glm::vec2& pos, const glm::vec3& col);

        void icon(const glm::vec2& pos, const glm::vec2& size, Icon icon);
        void draw(const glm::vec2& pos, const glm::vec2& size, GuiSprites sprite);
        void drawPatch(const glm::vec2& pos, const glm::vec2& size, GuiSprites sprite, float margin = 16.0f);
        void drawPatchI(const glm::vec2& pos, const glm::vec2& size, Icon icon, float margin = 8.0f);

        [[nodiscard]] glm::vec2 measureText(const std::string& text) const;

    private:
        void flush();

        bool m_is_text{false};
        uint32_t m_vao{0};
        uint32_t m_vbo{0};
        uint32_t m_ebo{0};
        uint32_t m_texture{0};
        Shader* m_shader;
        glm::vec3 m_color{1.f};
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        glm::mat4 m_projection{1.f};
        glm::mat4 m_view{1.f};
        AssetManager& m_assets;
    };

}

#endif //KTANKS_RENDERER_H