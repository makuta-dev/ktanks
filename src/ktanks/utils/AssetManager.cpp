#include "AssetManager.h"

#include <utility>
#include <spdlog/spdlog.h>

#include "spng.h"

namespace ktanks {

    struct ImageData {
        std::vector<unsigned char> data;
        glm::uvec2 size;
    };

    ImageData loadImage(const std::string& path) {
        ImageData idata{};
        FILE* f = fopen(path.c_str(), "rb");
        if (!f) {
            spdlog::error("Can't open image file: {}", path);
            return {};
        }

        spng_ctx* ctx = spng_ctx_new(0);
        spng_set_png_file(ctx, f);

        size_t out_size;
        spng_decoded_image_size(ctx, SPNG_FMT_RGBA8, &out_size);
        idata.data = std::vector<unsigned char>(out_size);
        spng_decode_image(ctx, idata.data.data(), out_size, SPNG_FMT_RGBA8,SPNG_DECODE_TRNS);

        spng_ihdr ihdr{};
        spng_get_ihdr(ctx, &ihdr);

        idata.size.x = ihdr.width;
        idata.size.y = ihdr.height;

        spng_ctx_free(ctx);
        fclose(f);
        return idata;
    }

    AssetManager::AssetManager(std::string assets_root) : m_root(std::move(assets_root)) {}

    Shader AssetManager::getShader(const std::string& name) const {
        return Shader::fromName(m_root + "/shaders", name);
    }

    Texture AssetManager::getTexture(const std::string& name) const {
        return Texture::loadFile(m_root + "/textures/" + name + ".png");
    }

    Font AssetManager::getFont(const std::string& name, const int size) const {
        return Font(m_root + "/fonts/" + name + ".ttf", size);
    }

    TextureAtlas AssetManager::getTerrainAtlas() const {
        constexpr auto atlas_size = glm::uvec2(1024);
        TextureAtlas atlas(atlas_size);

        auto pos = glm::uvec2(0);

        auto insert = [this, &pos, &atlas](const std::string& name) {
            constexpr auto sprite_size = glm::uvec2(128);
            const auto path = m_root + "/textures/terrain/" + name;
            const auto [pixels, size] = loadImage(path);

            atlas.insert(pos, size, pixels.data());

            pos.x += sprite_size.x;
            if (pos.x >= atlas_size.x) {
                pos.x = 0;
                pos.y += sprite_size.y;
            }
        };

        insert("tileGrass1.png");
        insert("tileGrass2.png");
        insert("tileGrass_roadCornerLL.png");
        insert("tileGrass_roadCornerLR.png");
        insert("tileGrass_roadCornerUL.png");
        insert("tileGrass_roadCornerUR.png");
        insert("tileGrass_roadCrossing.png");
        insert("tileGrass_roadCrossingRound.png");
        insert("tileGrass_roadEast.png");
        insert("tileGrass_roadNorth.png");
        insert("tileGrass_roadSplitE.png");
        insert("tileGrass_roadSplitN.png");
        insert("tileGrass_roadSplitS.png");
        insert("tileGrass_roadSplitW.png");

        insert("tileSand1.png");
        insert("tileSand2.png");
        insert("tileSand_roadCornerLL.png");
        insert("tileSand_roadCornerLR.png");
        insert("tileSand_roadCornerUL.png");
        insert("tileSand_roadCornerUR.png");
        insert("tileSand_roadCrossing.png");
        insert("tileSand_roadCrossingRound.png");
        insert("tileSand_roadEast.png");
        insert("tileSand_roadNorth.png");
        insert("tileSand_roadSplitE.png");
        insert("tileSand_roadSplitN.png");
        insert("tileSand_roadSplitS.png");
        insert("tileSand_roadSplitW.png");

        insert("tileGrass_roadTransitionE_dirt.png");
        insert("tileGrass_roadTransitionE.png");
        insert("tileGrass_roadTransitionN_dirt.png");
        insert("tileGrass_roadTransitionN.png");
        insert("tileGrass_roadTransitionS_dirt.png");
        insert("tileGrass_roadTransitionS.png");
        insert("tileGrass_roadTransitionW_dirt.png");
        insert("tileGrass_roadTransitionW.png");

        insert("tileGrass_transitionN.png");
        insert("tileGrass_transitionS.png");
        insert("tileGrass_transitionW.png");
        insert("tileGrass_transitionE.png");

        return atlas;
    }

    std::vector<std::string> generatePaths(const std::string& root, TankType t) {
        std::string name;
        switch (t) {
            case TankType::Red:
                name = "Red";
                break;
            case TankType::Blue:
                name = "Blue";
                break;
            case TankType::Green:
                name = "Green";
                break;
            case TankType::Black:
                name = "Dark";
                break;
            default: {
                spdlog::error("Tank type {} not supported", static_cast<int>(t));
                return {};
            }
        }

        auto paths = std::vector<std::string>();
        paths.emplace_back(root + "/textures/tankBody_" + name +"_outline.png");
        paths.emplace_back(root + "/textures/tank" + name +"_barrel2_outline.png");
        paths.emplace_back(root + "/textures/bullet" + name +"1_outline.png");
        paths.emplace_back(root + "/textures/bullet" + name +"2_outline.png");
        paths.emplace_back(root + "/textures/bullet" + name +"3_outline.png");
        return paths;
    }

    TextureAtlas AssetManager::getTankAtlas(const TankType t) const {
        constexpr auto atlas_size = glm::uvec2(128);
        TextureAtlas atlas(atlas_size);

        auto pos = glm::uvec2(0);
        uint32_t currentLineHeight = 0;

        auto insert = [&](const std::string& path) {
            const auto [pixels, size] = loadImage(path);

            if (pos.x + size.x > atlas_size.x) {
                pos.x = 0;
                pos.y += currentLineHeight + 1;
                currentLineHeight = 0;
            }

            if (pos.y + size.y > atlas_size.y) {
                spdlog::error("Atlas full! Cannot insert {}", path);
                return;
            }

            atlas.insert(pos, size, pixels.data());

            if (size.y > currentLineHeight) {
                currentLineHeight = size.y;
            }

            pos.x += size.x + 1;
        };

        for (const auto& path : generatePaths(m_root,t)) {
            insert(path);
        }

        return atlas;
    }

}
