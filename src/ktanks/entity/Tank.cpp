#include "Tank.h"

#include <glm/trigonometric.hpp>

#include "ktanks/graphics/sprite_data/TankSprites.h"

namespace ktanks {

    constexpr auto move_speed = 30.f;
    constexpr auto rotate_speed = 0.5f;
    constexpr auto barrel_speed = 0.75f;

    Tank::Tank(const glm::vec2& pos,const AssetManager& manager, const TankType type)
        : m_pos(pos), m_vel(0.f){
        m_atlas = manager.getTankAtlas(type);
    }

    void Tank::onUpdate(const float dt) {
        if (std::abs(m_vel.x) > 0 || std::abs(m_vel.y) > 0) {
            m_pos += m_vel * move_speed * dt;
        }
        m_vel *= 0.85f;
    }

    void Tank::onDraw(Renderer& r) {
        if(const auto reg = m_atlas.at(static_cast<int>(TankSprites::Body))) {
            r.setTexture(m_atlas.getTextureID());
            r.drawSprite(m_pos, glm::vec2(reg->size), glm::radians<float>(m_body_rotation),glm::vec2(0.5),*reg);
            if(const auto reg2 = m_atlas.at(static_cast<int>(TankSprites::Barrel))){
                r.drawSprite(m_pos, glm::vec2(reg2->size), glm::radians<float>(m_body_rotation + m_barrel_rotation),glm::vec2(0.5,0.0),*reg2);
            }
        }
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
