#ifndef KTANKS_TERRAINSPRITELIST_H
#define KTANKS_TERRAINSPRITELIST_H

#include <cstdint>

namespace ktanks {

    enum class TerrainSprite : uint8_t {
        Grass1,
        Grass2,
        GCornerLL,
        GCornerLR,
        GCornerUL,
        GCornerUR,
        GCrossing,
        GCrossingRound,
        GEast,
        GNorth,
        GSplitE,
        GSplitN,
        GSplitS,
        GSplitW,

        Sand1,
        Sand2,
        SCornerLL,
        SCornerLR,
        SCornerUL,
        SCornerUR,
        SCrossing,
        SCrossingRound,
        SEast,
        SNorth,
        SSplitE,
        SSplitN,
        SSplitS,
        SSplitW,

        RTransitionEDirt,
        RTransitionE,
        RTransitionNDirt,
        RTransitionN,
        RTransitionSDirt,
        RTransitionS,
        RTransitionWDirt,
        RTransitionW,

        TTransitionN,
        TTransitionS,
        TTransitionW,
        TTransitionE,
    };

}

#endif //KTANKS_TERRAINSPRITELIST_H