#ifndef KTANKS_UIRENDERER_H
#define KTANKS_UIRENDERER_H

#include "ktanks/core/data/GuiData.h"
#include "ktanks/renderer/Renderer.h"

namespace ktanks {

    class UIRenderer final : public Renderer {
    public:
        explicit UIRenderer(AssetManager&);
        ~UIRenderer();

        void text(const std::string& text, const glm::vec2& pos, const glm::vec3& col);
        void icon(const glm::vec2& pos, const glm::vec2& size, Icon icon);
        void draw(const glm::vec2& pos, const glm::vec2& size, GuiSprites sprite);
        void drawPatch(const glm::vec2& pos, const glm::vec2& size, GuiSprites sprite, float margin = 16.0f);

    private:
        Font* m_font;
        TextureAtlas* m_atlas;
    };

}

#endif //KTANKS_UIRENDERER_H