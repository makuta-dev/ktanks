#ifndef KTANKS_UIRENDERER_H
#define KTANKS_UIRENDERER_H

#include "ktanks/renderer/Renderer.h"

namespace ktanks {

    class UIRenderer final : public Renderer{
    public:
        explicit UIRenderer(AssetManager&);
        ~UIRenderer();

        void setTextColor(const glm::vec3&);
        void text(const std::string& text, const glm::vec2& pos);

    private:
        glm::vec3 m_color{1.f};
        Font* m_font;
    };

}

#endif //KTANKS_UIRENDERER_H