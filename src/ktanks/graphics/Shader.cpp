#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "glad/gl.h"

namespace ktanks {

    Shader::Shader() = default;
    Shader::~Shader() {
        if (m_program != 0) {
            glDeleteProgram(m_program);
        }
    }

    Shader::Shader(const uint32_t program) : m_program(program){}

    Shader::Shader(Shader&& other) noexcept : m_program(other.m_program) {
        other.m_program = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept {
        if (this != &other) {
            if (m_program != 0) {
                glDeleteProgram(m_program);
            }

            m_program = other.m_program;
            other.m_program = 0;
        }
        return *this;
    }

    Shader Shader::fromName(const std::string& path,const std::string& name) {
        const auto v_path = path + "/" + name + ".vert";
        const auto f_path = path + "/" + name + ".frag";
        return fromPath(v_path,f_path);
    }

    uint makeShader(const std::string& path, int type) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Failed to open shader file: " << path << std::endl;
            return 0;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string sourceStr = buffer.str();
        const char* sourceCStr = sourceStr.c_str();

        uint32_t shader = glCreateShader(type);
        glShaderSource(shader, 1, &sourceCStr, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            int maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

            std::cerr << "Shader Compilation Error (" << path << "):\n"
                      << errorLog.data() << std::endl;
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    uint makeProgram(uint32_t vertex, uint32_t fragment) {
        if (vertex == 0 || fragment == 0) return 0;

        const uint32_t program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);

        int isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE) {
            int maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            std::cerr << "Shader Linking Error:\n" << infoLog.data() << std::endl;

            glDeleteProgram(program);
            return 0;
        }

        glDetachShader(program, vertex);
        glDetachShader(program, fragment);
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return program;
    }

    Shader Shader::fromPath(const std::string& v_path,const std::string& f_path) {
        const auto vertex = makeShader(v_path, GL_VERTEX_SHADER);
        const auto fragment = makeShader(f_path, GL_FRAGMENT_SHADER);
        const auto program = makeProgram(vertex,fragment);
        return {program};
    }

}
