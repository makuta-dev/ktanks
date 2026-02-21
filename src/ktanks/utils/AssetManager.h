#ifndef KTANKS_ASSETMANAGER_H
#define KTANKS_ASSETMANAGER_H

#include <string>

#include "ktanks/core/TankType.h"

#include "ktanks/graphics/Font.h"
#include "ktanks/graphics/Shader.h"
#include "ktanks/graphics/Texture.h"
#include "ktanks/graphics/TextureAtlas.h"

namespace ktanks {

    class AssetManager final {
    public:
        explicit AssetManager(std::string  assets_root = ASSETS_ROOT);

        [[nodiscard]] Shader getShader(const std::string& name) const;
        [[nodiscard]] Texture getTexture(const std::string& name) const;
        Font getFont(const std::string& name);

        [[nodiscard]] TextureAtlas getTerrainAtlas() const;
        [[nodiscard]] TextureAtlas getTankAtlas(TankType) const;

    private:
        std::string m_root;
    };

}


#endif //KTANKS_ASSETMANAGER_H