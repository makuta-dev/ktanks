#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

#include "ktanks/core/Constants.h"

namespace ktanks {

    glm::mat4 Camera::getViewMatrix() const {
        auto view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(-offset, 0.0f));
        return view;
    }

    void Camera::update(const glm::vec2& center, const glm::vec2& view, const float dt) {
        const glm::vec2 target = center - view / 2.f;
        offset = glm::mix(offset, target, CAMERA_SPEED * dt);
    }

}
