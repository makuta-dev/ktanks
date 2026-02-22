#include "AssetManager.h"

#include <algorithm>
#include <filesystem>
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

    std::vector<std::string> getPaths(const std::string& root, const AtlasID id) {
        auto data = std::vector<std::string>();
        if (id == AtlasID::Terrain) {
            data.push_back(root + "/textures/terrain/tileGrass1.png");
            data.push_back(root + "/textures/terrain/tileGrass2.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadCornerLL.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadCornerLR.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadCornerUL.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadCornerUR.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadCrossing.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadCrossingRound.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadEast.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadNorth.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadSplitE.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadSplitN.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadSplitS.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadSplitW.png");
            data.push_back(root + "/textures/terrain/tileSand1.png");
            data.push_back(root + "/textures/terrain/tileSand2.png");
            data.push_back(root + "/textures/terrain/tileSand_roadCornerLL.png");
            data.push_back(root + "/textures/terrain/tileSand_roadCornerLR.png");
            data.push_back(root + "/textures/terrain/tileSand_roadCornerUL.png");
            data.push_back(root + "/textures/terrain/tileSand_roadCornerUR.png");
            data.push_back(root + "/textures/terrain/tileSand_roadCrossing.png");
            data.push_back(root + "/textures/terrain/tileSand_roadCrossingRound.png");
            data.push_back(root + "/textures/terrain/tileSand_roadEast.png");
            data.push_back(root + "/textures/terrain/tileSand_roadNorth.png");
            data.push_back(root + "/textures/terrain/tileSand_roadSplitE.png");
            data.push_back(root + "/textures/terrain/tileSand_roadSplitN.png");
            data.push_back(root + "/textures/terrain/tileSand_roadSplitS.png");
            data.push_back(root + "/textures/terrain/tileSand_roadSplitW.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadTransitionE_dirt.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadTransitionE.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadTransitionN_dirt.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadTransitionN.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadTransitionS_dirt.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadTransitionS.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadTransitionW_dirt.png");
            data.push_back(root + "/textures/terrain/tileGrass_roadTransitionW.png");
            data.push_back(root + "/textures/terrain/tileGrass_transitionN.png");
            data.push_back(root + "/textures/terrain/tileGrass_transitionS.png");
            data.push_back(root + "/textures/terrain/tileGrass_transitionW.png");
            data.push_back(root + "/textures/terrain/tileGrass_transitionE.png");
        }
        if (id == AtlasID::Tanks) {
            for(const auto& color : {"Red","Blue","Green","Dark"}) {
                data.push_back(root + "/textures/tankBody_" + color +"_outline.png");
                data.push_back(root + "/textures/tank" + color +"_barrel2_outline.png");
                data.push_back(root + "/textures/bullet" + color +"1_outline.png");
                data.push_back(root + "/textures/bullet" + color +"2_outline.png");
                data.push_back(root + "/textures/bullet" + color +"3_outline.png");
            }
        }
        return data;
    }

    struct PackedImage {
        int id;
        ImageData image;
        glm::uvec2 position{};
    };

    struct Node {
        uint32_t x;
        uint32_t y;
        uint32_t width;
    };

    TextureAtlas newAtlasFor(const std::string& root, const AtlasID id) {
        const auto atlas_size = id == AtlasID::Terrain ? glm::uvec2(1024) : glm::uvec2(256);
        const auto paths = getPaths(root,id);
        std::vector<PackedImage> images;

        for (int i = 0; i < paths.size(); i++) {
            images.push_back({
                i,
                loadImage(paths[i]),
                {}
            });
        }

        if (images.empty())
            return TextureAtlas(0,atlas_size);

        std::ranges::sort(images, [](const auto& a, const auto& b) {
            return a.image.size.y > b.image.size.y;
        });

        std::vector<Node> skyline;
        skyline.push_back({0, 0, atlas_size.x});

        auto fit = [&](const long index,
                const uint32_t w,
                const uint32_t h,
                uint32_t& outY) -> bool {

            if (const uint32_t x = skyline[index].x; x + w > atlas_size.x)
                return false;

            uint32_t widthLeft = w;
            uint32_t y = skyline[index].y;
            size_t i = index;

            while (widthLeft > 0) {
                y = std::max(y, skyline[i].y);

                if (y + h > atlas_size.y)
                    return false;

                if (skyline[i].width >= widthLeft)
                    break;

                widthLeft -= skyline[i].width;
                ++i;

                if (i >= skyline.size())
                    return false;
            }

            outY = y;
            return true;
        };

        auto addLevel = [&](const long index,
                     const uint32_t x,
                     const uint32_t y,
                     const uint32_t w,
                     const uint32_t h) {

            const Node newNode{ x, y + h, w };

            skyline.insert(skyline.begin() + index, newNode);

            long i = index + 1;

            while (i < skyline.size()) {

                const uint32_t prevRight =
                    skyline[i - 1].x + skyline[i - 1].width;

                if (skyline[i].x < prevRight) {

                    const uint32_t overlap = prevRight - skyline[i].x;

                    skyline[i].x += overlap;

                    if (skyline[i].width <= overlap) {
                        skyline[i].width = 0;
                        skyline.erase(skyline.begin() + i);
                        continue;
                    }

                    skyline[i].width -= overlap;
                }
                else break;

                ++i;
            }
        };

        for (auto& img : images) {
            uint32_t bestY = UINT32_MAX;
            long bestIndex = 0;
            bool found = false;

            for (long i = 0; i < skyline.size(); ++i) {
                if (uint32_t y; fit(i, img.image.size.x, img.image.size.y, y)) {
                    if (y < bestY) {
                        bestY = y;
                        bestIndex = i;
                        found = true;
                    }
                }
            }

            if (!found) {
                throw std::runtime_error("Atlas too small");
            }

            img.position = {skyline[bestIndex].x, bestY};

            addLevel(bestIndex,
                     img.position.x,
                     img.position.y,
                     img.image.size.x,
                     img.image.size.y);
        }

        TextureAtlas atlas{static_cast<int>(images.size()),atlas_size};

        for (const auto&[tid, image, position] : images) {
            atlas.insert(
                tid,
                position,
                image.size,
                image.data.data()
            );
        }

        return atlas;
    }

    std::string getNameBy(const ShaderID id) {
        if (id == ShaderID::Default) {
            return "simple";
        }
        return "";
    }

    std::string getNameBy(TextureID) {
        return "";
    }

    AssetManager::AssetManager(std::string assets_root) : m_root(std::move(assets_root)){}

    Shader& AssetManager::getShader(const ShaderID id) {
        const auto index = static_cast<size_t>(id);

        if (!m_shaders[index]) {
            m_shaders[index] = std::make_unique<Shader>(
                std::move(Shader::fromName(m_root + "/shaders", getNameBy(id)))
            );
        }

        return *m_shaders[index];
    }

    Texture& AssetManager::getTexture(const TextureID id) {
        const auto index = static_cast<size_t>(id);

        if (!m_textures[index]) {
            m_textures[index] = std::make_unique<Texture>(
                std::move(Texture::loadFile(m_root + "/textures/" + getNameBy(id) + ".png"))
            );
        }

        return *m_textures[index];
    }

    TextureAtlas& AssetManager::getTextureAtlas(AtlasID id) {
        const auto index = static_cast<size_t>(id);

        if (!m_atlases[index]) {
            m_atlases[index] = std::make_unique<TextureAtlas>(
                std::move(newAtlasFor(m_root,id))
            );
        }

        return *m_atlases[index];
    }

    Font& AssetManager::getFont() {
        if (!m_font) {
            m_font = std::make_unique<Font>(m_root + "fonts/Kenney_Future.ttf", 32);
        }
        return *m_font;
    }
}
