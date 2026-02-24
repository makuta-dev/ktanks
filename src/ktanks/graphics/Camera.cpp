#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

#include "ktanks/core/Constants.h"

namespace ktanks {

    glm::mat4 Camera::getViewMatrix() const {
        auto view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(-offset, 0.0f));
        return view;
    }

    void Camera::update(const glm::vec2& center, const glm::vec2& view,const glm::uvec2& mapSize, const float dt) {
        glm::vec2 target = center - view / 2.f;
        const glm::vec2 maxOffset = glm::vec2(mapSize) - view;
        target.x = glm::clamp(target.x, 0.f, maxOffset.x);
        target.y = glm::clamp(target.y, 0.f, maxOffset.y);
        offset = glm::mix(offset, target, CAMERA_SPEED * dt);
    }

}
