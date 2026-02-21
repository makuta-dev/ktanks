#ifndef KTANKS_TERRAINSPRITELIST_H
#define KTANKS_TERRAINSPRITELIST_H

namespace ktanks {

    enum class TerrainSprite {
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

        RTransitionE,
        RTransitionEDirt,
        RTransitionN,
        RTransitionNDirt,
        RTransitionS,
        RTransitionSDirt,
        RTransitionW,
        RTransitionWDirt,

        TTransitionN,
        TTransitionS,
        TTransitionW,
        TTransitionE,
    };

}

#endif //KTANKS_TERRAINSPRITELIST_H