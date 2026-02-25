#include "Image.h"

namespace ktanks {

    Image::Image(const Icon i, const glm::vec2& size) : m_icon(i), m_sprite(GuiSprites::button_rectangle_border) {
        setSize(size);
    }

    Image::Image(const GuiSprites s, const glm::vec2& size) : is_icon(false), m_icon(Icon::Home), m_sprite(s) {
        setSize(size);
    }

    Image::~Image() = default;

    void Image::onRender(UIRenderer &renderer) {
        if (is_icon) {
            renderer.icon(getAbsolutePosition(),getSize(),m_icon);
        } else {
            renderer.draw(getAbsolutePosition(),getSize(),m_sprite);
        }
    }


}