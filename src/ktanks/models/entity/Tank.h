#ifndef KTANKS_TANK_H
#define KTANKS_TANK_H

#include <glm/vec2.hpp>

#include "ktanks/core/constants/TankData.h"

namespace ktanks {

    class Tank final {
    public:
        Tank(const glm::vec2& pos, TankColor);

        void onUpdate(float dt);
        void move(uint8_t);

        [[nodiscard]] glm::vec2 getPosition() const;

    private:
        glm::vec2 m_pos;
        glm::vec2 m_vel;
        float m_body_rotation{0.f};
        float m_barrel_rotation{0.f};
    };

}

#endif //KTANKS_TANK_H