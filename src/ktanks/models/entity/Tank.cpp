#include "Tank.h"

#include <glm/trigonometric.hpp>

namespace ktanks {

    constexpr auto move_speed = 30.f;
    constexpr auto rotate_speed = 0.5f;
    constexpr auto barrel_speed = 0.75f;

    Tank::Tank(const glm::vec2 &pos, TankColor) : m_pos(pos), m_vel(0.f){}

    void Tank::onUpdate(const float dt) {
        if (std::abs(m_vel.x) > 0 || std::abs(m_vel.y) > 0) {
            m_pos += m_vel * move_speed * dt;
        }
        m_vel *= 0.85f;
    }

    glm::vec2 unit(const float angle) {
        return {cosf(angle),sinf(angle)};
    }

    void Tank::move(const uint8_t c) {
        if (c & 1) {
            m_vel += unit(glm::radians(m_body_rotation + 90.f));
        }
        if (c & 1 << 1) {
            m_vel -= unit(glm::radians(m_body_rotation + 90.f));
        }
        if (c & 1 << 2) {
            m_body_rotation -= rotate_speed;
        }
        if (c & 1 << 3) {
            m_body_rotation += rotate_speed;
        }
        if (c & 1 << 4) {
            m_barrel_rotation -= barrel_speed;
            if (m_barrel_rotation < -45.f) m_barrel_rotation = -45.f;
        }
        if (c & 1 << 5) {
            m_barrel_rotation += barrel_speed;
            if (m_barrel_rotation > 45.f) m_barrel_rotation = 45.f;
        }
    }

    glm::vec2 Tank::getPosition() const {
        return m_pos;
    }
}
