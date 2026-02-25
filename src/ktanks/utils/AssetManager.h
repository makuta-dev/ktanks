#ifndef KTANKS_ASSETMANAGER_H
#define KTANKS_ASSETMANAGER_H

#include <memory>

#include "ktanks/graphics/Font.h"
#include "ktanks/graphics/Shader.h"
#include "ktanks/graphics/Texture.h"
#include "ktanks/graphics/TextureAtlas.h"

namespace ktanks {

    enum class ShaderID : uint8_t {
        Default,
        Count
    };

    enum class AtlasID : uint16_t {
        Terrain,
        Tanks,
        Blocks,
        GUI,
        Count
    };

    enum class FontID : uint16_t {
        Regular,
        Narrow,
        Count
    };

    class AssetManager final {
    public:
        explicit AssetManager(std::string assets_root = ASSETS_ROOT);

        Shader& getShader(ShaderID);
        TextureAtlas& getTextureAtlas(AtlasID);
        Font& getFont(FontID);

    private:
        std::string m_root;

        std::array<std::unique_ptr<Shader>,
            static_cast<size_t>(ShaderID::Count)> m_shaders{};

        std::array<std::unique_ptr<TextureAtlas>,
            static_cast<size_t>(AtlasID::Count)> m_atlases{};

        std::array<std::unique_ptr<Font>,
            static_cast<size_t>(FontID::Count)> m_fonts{};
    };

}

#endif //KTANKS_ASSETMANAGER_H