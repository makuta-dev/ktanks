#include "AssetsManager.h"

#include <utility>
#include <spdlog/spdlog.h>

namespace ktanks {

    AssetsManager::AssetsManager(std::filesystem::path root_path) : m_root_path(std::move(root_path)) {}

    std::shared_ptr<Shader> AssetsManager::getShader(const std::string& name) {
        return loadFromCache(m_shaders,name);
    }

    std::shared_ptr<Texture> AssetsManager::getTexture(const std::string& name) {
        return loadFromCache(m_textures,name);
    }

    std::shared_ptr<Atlas> AssetsManager::getAtlas(const std::string& name) {
        return loadFromCache(m_atlases,name);
    }

    std::shared_ptr<Font> AssetsManager::getFont(const std::string& name) {
        return loadFromCache(m_fonts,name);
    }

    template<>
    std::shared_ptr<Shader> AssetsManager::load(const std::string& name) {
        spdlog::info("Loading shader: {}", name);
        //TODO(loading shaders)
        return {};
    }

    template<>
    std::shared_ptr<Texture> AssetsManager::load(const std::string& name) {
        spdlog::info("Loading texture: {}", name);
        //TODO(loading textures)
        return {};
    }

    template<>
    std::shared_ptr<Font> AssetsManager::load(const std::string& name) {
        spdlog::info("Loading font: {}", name);
        //TODO(loading fonts)
        return {};
    }

    template<>
    std::shared_ptr<Atlas> AssetsManager::load(const std::string& name) {
        spdlog::info("Loading atlas: {}", name);
        //TODO(loading atlases)
        return {};
    }

}
