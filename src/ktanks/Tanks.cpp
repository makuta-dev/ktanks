#include "Tanks.h"

#include "glad/gl.h"
#include "window/Event.h"

namespace ktanks {

    constexpr auto tile_size = glm::vec2(32);

    Tanks::Tanks() {
        glClearColor(1.f, 1.0f, 1.0f, 1.f);
    }

    Tanks::~Tanks() = default;

    void Tanks::onUpdate(float dt) {

    }

    void Tanks::onDraw(Renderer& r) {
        glClear(GL_COLOR_BUFFER_BIT);

    }

    void Tanks::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
