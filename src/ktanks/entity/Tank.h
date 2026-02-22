#ifndef KTANKS_TANK_H
#define KTANKS_TANK_H

#include "ktanks/graphics/Renderer.h"
#include "ktanks/graphics/TextureAtlas.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class Tank final {
    public:
        Tank(const glm::vec2& pos,const AssetManager&, TankType);

        void onUpdate(float dt);
        void onDraw(Renderer& r);

        void move(uint8_t);

        [[nodiscard]] glm::vec2 getPosition() const;

    private:
        glm::vec2 m_pos;
        glm::vec2 m_vel;
        float m_body_rotation{0.f};
        float m_barrel_rotation{0.f};
        TextureAtlas m_atlas;
    };

}

#endif //KTANKS_TANK_H