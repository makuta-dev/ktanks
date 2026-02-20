#ifndef KTANKS_SHADER_H
#define KTANKS_SHADER_H
#include <cstdint>
#include <string>

namespace ktanks {

    class Shader final {
    public:
        Shader();
        Shader(uint32_t program);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        static Shader fromName(const std::string& path,const std::string& name);
        static Shader fromPath(const std::string& v_path,const std::string& f_path);

    private:
        uint32_t m_program{0};
    };


}

#endif //KTANKS_SHADER_H