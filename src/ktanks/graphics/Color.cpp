#include "Color.h"

namespace ktanks {

    float ft(const uint8_t a) {
        return static_cast<float>(a) / 255.0f;
    }

    Color::Color() = default;

    Color::Color(const float r, const float g, const float b, const float a)
        : r(r), g(g), b(b), a(a) {}

    Color::Color(const glm::vec4& v)
        : r(v.r), g(v.g), b(v.b), a(v.a) {}

    Color::Color(const glm::vec3& v, const float alpha)
        : r(v.r), g(v.g), b(v.b), a(alpha) {}

    Color::Color(const uint8_t r8, const uint8_t g8, const uint8_t b8, const uint8_t a8)
        : r(ft(r8)), g(ft(g8)), b(ft(b8)), a(ft(a8)) {}

}