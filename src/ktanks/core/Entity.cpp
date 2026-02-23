#include "Entity.h"

namespace ktanks {

    Entity::Entity() : m_health(0), m_armor(0), m_velocity(0) {}

    Entity::Entity(const int health, const int armor)
        : m_health(health), m_armor(armor), m_velocity(0) {}

    int Entity::getHealth() const {
        return m_health;
    }

    int Entity::getArmor() const {
        return m_armor;
    }

    glm::vec2 Entity::getVelocity() const {
        return m_velocity;
    }

    void Entity::setHealth(const int h) {
        m_health = h;
    }

    void Entity::setArmor(const int a) {
        m_armor = a;
    }

    void Entity::setVelocity(const glm::vec2& v) {
        m_velocity = v;
    }

}