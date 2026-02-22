#ifndef KTANKS_TANKTYPE_H
#define KTANKS_TANKTYPE_H

#include <cstdint>

namespace ktanks {

    enum class TankColor : uint8_t {
        Red,
        Blue,
        Green,
        Black,
    };

    enum class TankSprites : uint8_t {
        Body,
        Barrel,
        Bullet1,
        Bullet2,
        Bullet3
    };

}

#endif //KTANKS_TANKTYPE_H