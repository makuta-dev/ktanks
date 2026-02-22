#ifndef KTANKS_CAMERA_H
#define KTANKS_CAMERA_H

#include <glm/mat4x4.hpp>

namespace ktanks {

    class Camera final {
    public:
        Camera() = default;

        [[nodiscard]] glm::mat4 getViewMatrix() const;
        void update(const glm::vec2& center, const glm::vec2& view, float dt);

    private:
        glm::vec2 offset{0};
    };

}

#endif //KTANKS_CAMERA_H