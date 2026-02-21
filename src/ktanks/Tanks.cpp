#include "Tanks.h"

#include "glad/gl.h"

namespace ktanks {

    constexpr auto tile_size = glm::vec2(32);

    Tanks::Tanks(const AssetManager &asset_manager) {
        glClearColor(0.f, 0.0f, 0.0f, 1.f);
        tank = asset_manager.getTankAtlas(TankType::Green);
    }

    Tanks::~Tanks() = default;

    void Tanks::onUpdate(float dt) {

    }

    void Tanks::onDraw(Renderer& r) {
        r.setTexture(tank.getTextureID());
        r.drawSprite({0,0},{128,128},{{0,0},{1,1}});
    }

    void Tanks::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
