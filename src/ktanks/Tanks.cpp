#include "Tanks.h"

#include "glad/gl.h"
#include "utils/AssetManager.h"

namespace ktanks {

    constexpr auto tile_size = glm::vec2(32);

    Tanks::Tanks() : map(glm::uvec2{32}) {
        glClearColor(0.f, 0.0f, 0.0f, 1.f);
        tank = AssetManager().getTankAtlas(TankType::Black);
    }

    Tanks::~Tanks() = default;

    void Tanks::onUpdate(float dt) {

    }

    void Tanks::onDraw(Renderer& r) {
        map.draw(r,tile_size);
        r.drawTexture({0,0},{128,128},tank.getTextureID());
    }

    void Tanks::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
