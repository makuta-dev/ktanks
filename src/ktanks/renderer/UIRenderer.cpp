#include "UIRenderer.h"

namespace ktanks {

    UIRenderer::UIRenderer(AssetManager& a) : Renderer(a) {
        m_font = &a.getFont(FontID::Regular);
        m_atlas = &a.getTextureAtlas(AtlasID::GUI);
    }

    UIRenderer::~UIRenderer() = default;

    void UIRenderer::text(const std::string& text, const glm::vec2& pos, const glm::vec3& col) {
        drawText(text, pos, col, *m_font);
    }

    void UIRenderer::icon(const glm::vec2& pos, const glm::vec2& size, Icon icon) {
        setTexture(m_atlas->getTextureID());
        if (const auto icon_reg = m_atlas->at(static_cast<int>(icon))) {
            drawSprite(pos,size,*icon_reg);
        }
    }

    void UIRenderer::draw(const glm::vec2& pos, const glm::vec2& size, GuiSprites sprite) {
        setTexture(m_atlas->getTextureID());
        if (const auto sprite_reg = m_atlas->at(static_cast<int>(sprite))) {
            drawSprite(pos,size,*sprite_reg);
        }
    }

    void UIRenderer::drawPatch(const glm::vec2& pos, const glm::vec2& size, GuiSprites sprite, const float margin) {
        const auto sprite_reg = m_atlas->at(static_cast<int>(sprite));
        if (!sprite_reg) return;

        setTexture(m_atlas->getTextureID());

        float x_sizes[3] = { margin, size.x - 2.0f * margin, margin };
        float y_sizes[3] = { margin, size.y - 2.0f * margin, margin };

        glm::vec2 uv_total = sprite_reg->b - sprite_reg->a;
        glm::vec2 uv_margin = (uv_total / glm::vec2(sprite_reg->size)) * margin;

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
                slice.size = { (unsigned int)margin, (unsigned int)margin };

                glm::vec2 segmentPos = {
                    pos.x + (i > 0 ? x_sizes[0] : 0) + (i > 1 ? x_sizes[1] : 0),
                    pos.y + (j > 0 ? y_sizes[0] : 0) + (j > 1 ? y_sizes[1] : 0)
                };

                drawSprite(segmentPos, { x_sizes[i], y_sizes[j] }, slice);
            }
        }
    }

}