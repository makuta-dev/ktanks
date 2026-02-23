#ifndef KTANKS_ENTITY_H
#define KTANKS_ENTITY_H

#include <array>

#include "Object.h"

namespace ktanks {

    class Entity : public Object {
    public:
        Entity();
        Entity(int health, int armor);

        int getHealth() const;
        int getArmor() const;
        glm::vec2 getVelocity() const;

        void setHealth(int);
        void setArmor(int);
        void setVelocity(const glm::vec2&);

    private:
        int m_health;
        int m_armor;
        glm::vec2 m_velocity;
    };

}

#endif //KTANKS_ENTITY_H