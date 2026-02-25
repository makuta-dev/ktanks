#ifndef KTANKS_IMAGE_H
#define KTANKS_IMAGE_H

#include "ktanks/core/IWidget.h"

namespace ktanks {

    class Image final : public IWidget{
    public:
        explicit Image(Icon, const glm::vec2& size = glm::vec2{24});
        explicit Image(GuiSprites, const glm::vec2& size);
        ~Image() override;

        void onRender(UIRenderer &renderer) override;
    private:
        bool is_icon{true};
        Icon m_icon;
        GuiSprites m_sprite;
    };

}

#endif //KTANKS_IMAGE_H