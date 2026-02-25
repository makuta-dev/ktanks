#include "UIRenderer.h"

namespace ktanks {

    UIRenderer::UIRenderer(AssetManager& a) : Renderer(a) {
        m_font = &a.getFont(FontID::Regular);
    }

    UIRenderer::~UIRenderer() = default;

    void UIRenderer::setTextColor(const glm::vec3& c) {
        m_color = c;
    }

    void UIRenderer::text(const std::string& text, const glm::vec2& pos) {
        drawText(text, pos, m_color, *m_font);
    }

}