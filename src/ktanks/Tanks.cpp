#include "Tanks.h"

namespace ktanks {

    Tanks::Tanks(const AssetManager &asset_manager) {
        tank = asset_manager.getTankAtlas(TankType::Green);
        font = asset_manager.getFont("Kenney_Future",16);
    }

    Tanks::~Tanks() = default;

    void Tanks::onUpdate(const float dt) {
        lastFps += dt;
        if (lastFps > 0.25f) {
            const auto newFps = 1.0f / dt;
            fps = (fps + newFps) / 2.f;
            lastFps = 0.f;
        }
    }

    void Tanks::onDraw(Renderer& r) {
        r.drawText(std::format("{:3.2f}",fps),{0,16},{1,1,1},font);
    }

    void Tanks::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
