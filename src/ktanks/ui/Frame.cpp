#include "Frame.h"

namespace ktanks {

    Frame::Frame() = default;
    Frame::~Frame() = default;

    void Frame::onRender(UIRenderer &ui_renderer) {
        ui_renderer.drawPatch(getPosition(), getSize(), GuiSprites::input_square);
    }
}
