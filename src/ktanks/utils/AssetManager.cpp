#include "AssetManager.h"

#include <utility>

namespace ktanks {

    AssetManager::AssetManager(std::string assets_root) : m_root(std::move(assets_root)) {}

    Shader AssetManager::getShader(const std::string& name) const {
        return Shader::fromName(m_root + "/shaders", name);
    }

    Texture AssetManager::getTexture(const std::string& name) {
        return Texture::loadFile(m_root + "/textures/" + name + ".png");
    }

    Font AssetManager::getFont(const std::string& name) {
        //TODO(implement getFont(const std::string&))
        return {};
    }

}