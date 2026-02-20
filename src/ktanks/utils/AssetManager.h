#ifndef KTANKS_ASSETMANAGER_H
#define KTANKS_ASSETMANAGER_H

#include <string>

#include "ktanks/graphics/Font.h"
#include "ktanks/graphics/Shader.h"
#include "ktanks/graphics/Texture.h"

namespace ktanks {

    class AssetManager final {
    public:
        explicit AssetManager(std::string  assets_root = ASSETS_ROOT);

        Shader getShader(const std::string& name) const;
        Texture getTexture(const std::string& name);
        Font getFont(const std::string& name);

    private:
        std::string m_root;
    };

}


#endif //KTANKS_ASSETMANAGER_H