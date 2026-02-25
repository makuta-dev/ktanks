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

}