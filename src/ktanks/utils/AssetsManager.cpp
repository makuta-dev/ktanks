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

        auto v_path = m_root_path / "shaders" / (name + ".vert");
        auto f_path = m_root_path / "shaders" / (name + ".frag");

        spdlog::info("Vertex path  : {}", v_path.string());
        spdlog::info("Fragment path: {}", f_path.string());

        if (!std::filesystem::exists(v_path) || !std::filesystem::exists(f_path)) {
            spdlog::error("Failed to find shader files for: {}", name);
            return nullptr;
        }

        return std::make_shared<Shader>(v_path, f_path);
    }

    template<>
    std::shared_ptr<Texture> AssetsManager::load(const std::string& name) {
        const auto t_path = m_root_path / "textures" / (name + ".png");

        spdlog::info("Loading texture: {}", name);
        spdlog::info("Texture path : {}", t_path.string());

        if (!std::filesystem::exists(t_path)) {
            spdlog::error("Failed to find texture files for: {}", name);
            return nullptr;
        }

        return std::make_shared<Texture>(t_path);
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
