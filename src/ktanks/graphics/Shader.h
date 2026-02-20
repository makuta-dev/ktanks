#ifndef KTANKS_SHADER_H
#define KTANKS_SHADER_H

#include <cstdint>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

namespace ktanks {

    class Shader final {
    public:
        explicit Shader(uint32_t program);

        Shader();
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        void setInt(const std::string& name, int value);
        void setFloat(const std::string& name, float value);
        void setVec2(const std::string& name, const glm::vec2& value);
        void setVec3(const std::string& name, const glm::vec3& value);
        void setVec4(const std::string& name, const glm::vec4& value);
        void setMat3(const std::string& name, const glm::mat3& value);
        void setMat4(const std::string& name, const glm::mat4& value);

        static Shader fromName(const std::string& path,const std::string& name);
        static Shader fromPath(const std::string& v_path,const std::string& f_path);

    private:
        int getUniform(const std::string& name);

        uint32_t m_program{0};
        std::unordered_map<std::string,int> uniforms;
    };


}

#endif //KTANKS_SHADER_H