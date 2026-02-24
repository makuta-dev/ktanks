#ifndef KTANKS_GAMERENDERER_H
#define KTANKS_GAMERENDERER_H

#include "ktanks/models/Level.h"
#include "ktanks/models/entity/Tank.h"
#include "ktanks/renderer/Renderer.h"
#include "ktanks/utils/AssetManager.h"

namespace ktanks {

    class GameRenderer final : public Renderer {
    public:
        explicit GameRenderer(AssetManager&);
        ~GameRenderer();

        void drawTank(const Tank&);
        void drawLevel(const Level&);

    private:
        void drawTerrain(const LevelMap<TerrainSprite>&);
        void drawBlocks(const LevelMap<BlockID>&);

        TextureAtlas* m_tank_atlas;
        TextureAtlas* m_block_atlas;
        TextureAtlas* m_terrain_atlas;
    };

}

#endif //KTANKS_GAMERENDERER_H