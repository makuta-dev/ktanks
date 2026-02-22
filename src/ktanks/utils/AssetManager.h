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

    enum class TextureID : uint16_t {
        Count
    };

    enum class AtlasID : uint16_t {
        Terrain,
        Tanks,
        Count
    };

    class AssetManager final {
    public:
        explicit AssetManager(std::string assets_root = ASSETS_ROOT);

        Shader& getShader(ShaderID);
        Texture& getTexture(TextureID);
        TextureAtlas& getTextureAtlas(AtlasID);
        Font& getFont();

    private:
        std::string m_root;

        std::array<std::unique_ptr<Shader>,
            static_cast<size_t>(ShaderID::Count)> m_shaders{};

        std::array<std::unique_ptr<Texture>,
            static_cast<size_t>(TextureID::Count)> m_textures{};

        std::array<std::unique_ptr<TextureAtlas>,
            static_cast<size_t>(AtlasID::Count)> m_atlases{};

        std::unique_ptr<Font> m_font{nullptr};
    };

}

#endif //KTANKS_ASSETMANAGER_H