#ifndef KTANKS_COLOR_H
#define KTANKS_COLOR_H

#include <cstdint>
#include <glm/glm.hpp>

namespace ktanks {

    class Color final {
    public:
        Color();
        Color(float r, float g, float b, float a = 1.0f);
        explicit Color(const glm::vec4& v);
        explicit Color(const glm::vec3& v, float alpha = 1.0f);
        Color(uint8_t r8, uint8_t g8,uint8_t b8, uint8_t a8 = 255);

        [[nodiscard]] explicit constexpr operator glm::vec4() const noexcept {
            return { r, g, b, a };
        }

        [[nodiscard]] explicit constexpr operator glm::vec3() const noexcept {
            return { r, g, b };
        }

        float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
    };

}

#endif //KTANKS_COLOR_H