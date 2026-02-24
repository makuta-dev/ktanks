#ifndef KTANKS_TANK_H
#define KTANKS_TANK_H

#include "ktanks/core/Entity.h"
#include "ktanks/core/data/TankData.h"

namespace ktanks {

    class Tank final : public Entity {
    public:
        explicit Tank(TankColor);

        void onUpdate(float dt);
        void move(uint8_t);

    private:
        TankColor m_color;
        float m_body_rotation{0.f};
        float m_barrel_rotation{0.f};
    };

}

#endif //KTANKS_TANK_H