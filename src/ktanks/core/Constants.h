#ifndef KTANKS_CONSTANTS_H
#define KTANKS_CONSTANTS_H

#include <glm/vec2.hpp>

namespace ktanks {

    constexpr auto TILE_SIZE = glm::vec2{128};
    constexpr auto BLOCK_SIZE = TILE_SIZE / 4.f;

    constexpr auto MOVE_SPEED = 200.f;
    constexpr auto BODY_TURN_SPEED = 120.f;
    constexpr auto BARREL_TURN_SPEED = 180.f;

    constexpr float CAMERA_SPEED = 3.75f;

}

#endif //KTANKS_CONSTANTS_H