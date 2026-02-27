#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "glad/gl.h"

namespace ktanks {

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        auto loadSource = [](const std::string& path) {
            std::ifstream file(path);
            std::stringstream ss;
            ss << file.rdbuf();
            return ss.str();
        };

        const std::string vSource = loadSource(vertexPath);
        const std::string fSource = loadSource(fragmentPath);

        const uint32_t vs = compileShader(GL_VERTEX_SHADER, vSource);
        const uint32_t fs = compileShader(GL_FRAGMENT_SHADER, fSource);

        m_id = glCreateProgram();
        glAttachShader(m_id, vs);
        glAttachShader(m_id, fs);
        glLinkProgram(m_id);

        int success;
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
            std::cerr << "Shader Linking Failed:\n" << infoLog << std::endl;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    Shader::~Shader() {
        glDeleteProgram(m_id);
    }

    void Shader::use() const { glUseProgram(m_id); }

    uint32_t Shader::compileShader(const uint32_t type, const std::string& source) {
        const uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int success;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "Shader Compilation Failed (" << (type == GL_VERTEX_SHADER ? "Vert" : "Frag") << "):\n" << infoLog << std::endl;
        }
        return id;
    }

    int Shader::getUniformLocation(const std::string& name) {
        if (m_locationCache.contains(name))
            return m_locationCache[name];

        const int location = glGetUniformLocation(m_id, name.c_str());
        m_locationCache[name] = location;
        return location;
    }

    void Shader::setInt(const std::string& name, const int value) {
        glProgramUniform1i(m_id, getUniformLocation(name), value);
    }

    void Shader::setFloat(const std::string& name, const float value) {
        glProgramUniform1f(m_id, getUniformLocation(name), value);
    }

    void Shader::setVec2(const std::string& name, const glm::vec2& value) {
        glProgramUniform2fv(m_id, getUniformLocation(name), 1, &value[0]);
    }

    void Shader::setVec4(const std::string& name, const glm::vec4& value) {
        glProgramUniform4fv(m_id, getUniformLocation(name), 1, &value[0]);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& value) {
        glProgramUniformMatrix4fv(m_id, getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
    }

}
