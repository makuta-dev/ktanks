#include "Tanks.h"

#include <glm/trigonometric.hpp>
#include <glm/ext/scalar_constants.hpp>

#include "graphics/sprite_data/TankSprites.h"

namespace ktanks {

    const auto tank_size = glm::uvec2{64};
    const auto barrel_size = glm::uvec2{16,32};

    Tanks::Tanks(const AssetManager &asset_manager) {
        font = asset_manager.getFont("Kenney_Future",16);
        tank = asset_manager.getTankAtlas(TankType::Black);
    }

    Tanks::~Tanks() = default;

    void Tanks::onUpdate(const float dt) {
        lastFps += dt;
        if (lastFps > 0.25f) {
            const auto newFps = 1.0f / dt;
            fps = (fps + newFps) / 2.f;
            lastFps = 0.f;
        }
        angle += 180.f * dt;
        angle2 += 45.f * dt;
    }

    void Tanks::onDraw(Renderer& r) {
        r.drawText(std::format("{:3.2f}",fps),{0,16},{1,1,1},font);

        if(const auto reg = tank.at(static_cast<int>(TankSprites::Body))) {
            r.setTexture(tank.getTextureID());
            r.drawSprite(view / 2u, tank_size, glm::radians<float>(angle),glm::vec2(0.5),*reg);
            if(const auto reg2 = tank.at(static_cast<int>(TankSprites::Barrel))){
                r.drawSprite(view / 2u, barrel_size, glm::radians<float>(-angle2),glm::vec2(0.5,0.0),*reg2);
            }
        }
    }

    void Tanks::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
