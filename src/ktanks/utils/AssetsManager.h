#ifndef KTANKS_ASSETSMANAGER_H
#define KTANKS_ASSETSMANAGER_H

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>

#include "ktanks/graphics/Atlas.h"
#include "ktanks/graphics/Font.h"
#include "ktanks/graphics/Shader.h"
#include "ktanks/graphics/Texture.h"

namespace ktanks {

    class AssetsManager final {
    public:
        explicit AssetsManager(std::filesystem::path  root_path = ASSETS_ROOT);

        std::shared_ptr<Shader> getShader(const std::string& name);
        std::shared_ptr<Texture> getTexture(const std::string& name);
        std::shared_ptr<Atlas> getAtlas(const std::string& name);
        std::shared_ptr<Font> getFont(const std::string& name);

    private:
        template<typename T>
        using CacheStorage = std::unordered_map<std::string, std::shared_ptr<T>>;

        template<typename T>
        std::shared_ptr<T> load(const std::string& name);

        template<typename T>
        std::shared_ptr<T> loadFromCache(
            std::unordered_map<std::string, std::shared_ptr<T>>& cache,
            const std::string& name
        ) {
            if (!cache.contains(name)) {
                cache[name] = load<T>(name);
            }
            return cache[name];
        }

        std::filesystem::path m_root_path;

        CacheStorage<Shader> m_shaders;
        CacheStorage<Texture> m_textures;
        CacheStorage<Atlas> m_atlases;
        CacheStorage<Font> m_fonts;
    };

}

#endif //KTANKS_ASSETSMANAGER_H