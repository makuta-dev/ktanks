#include "Tank.h"

#include <cmath>
#include <glm/trigonometric.hpp>

#include "ktanks/core/Constants.h"
#include "ktanks/window/Window.h"

namespace ktanks {

    Tank::Tank(const TankColor c) : m_color(c) {

    }

    void Tank::onUpdate(const float dt) {
        if (Window::isPressed(SDL_SCANCODE_W)) {
            auto pos = getPos();

            pos.x += cosf(glm::radians(getBodyRotation())) * MOVE_SPEED * dt;
            pos.y += sinf(glm::radians(getBodyRotation())) * MOVE_SPEED * dt;

            setPos(pos);
        }
        if (Window::isPressed(SDL_SCANCODE_S)) {
            auto pos = getPos();

            pos.x -= cosf(glm::radians(getBodyRotation())) * MOVE_SPEED * dt;
            pos.y -= sinf(glm::radians(getBodyRotation())) * MOVE_SPEED * dt;

            setPos(pos);
        }

        if (Window::isPressed(SDL_SCANCODE_A)) m_body_rotation -= BODY_TURN_SPEED * dt;
        if (Window::isPressed(SDL_SCANCODE_D)) m_body_rotation += BODY_TURN_SPEED * dt;

        if (Window::isPressed(SDL_SCANCODE_LEFT))  m_barrel_rotation -= BARREL_TURN_SPEED * dt;
        if (Window::isPressed(SDL_SCANCODE_RIGHT)) m_barrel_rotation += BARREL_TURN_SPEED * dt;
    }

    TankColor Tank::getColor() const {
        return m_color;
    }

    float Tank::getBodyRotation() const {
        return m_body_rotation;
    }

    float Tank::getBarrelRotation() const {
        return m_barrel_rotation;
    }

}
