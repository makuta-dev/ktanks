#ifndef KTANKS_BLOCKDATA_H
#define KTANKS_BLOCKDATA_H

namespace ktanks {

    constexpr auto BLOCK_TYPES = 27;

    enum class BlockColor : int {
        Marble,
        Rock,
        Sand,
        Stone
    };

    using BlockID = int;

}

#endif //KTANKS_BLOCKDATA_H