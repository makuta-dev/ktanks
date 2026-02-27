#ifndef KTANKS_SHADER_H
#define KTANKS_SHADER_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace ktanks {

    class Shader final {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void use() const;
        uint32_t id() const { return m_id; }

        // Uniform Helpers (OpenGL 4.6 style - No glUseProgram required for these)
        void setInt(const std::string& name, int value);
        void setFloat(const std::string& name, float value);
        void setVec2(const std::string& name, const glm::vec2& value);
        void setVec4(const std::string& name, const glm::vec4& value);
        void setMat4(const std::string& name, const glm::mat4& value);

    private:
        uint32_t m_id;
        std::unordered_map<std::string, int> m_locationCache;

        int getUniformLocation(const std::string& name);

        static uint32_t compileShader(uint32_t type, const std::string& source);
    };

}

#endif //KTANKS_SHADER_H