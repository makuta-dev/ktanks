#ifndef KTANKS_TEXTURE_H
#define KTANKS_TEXTURE_H

#include <string>
#include <iostream>

#include <glm/vec2.hpp>

namespace ktanks {

    class Texture final {
    public:
        Texture();
        explicit Texture(const glm::uvec2& size);
        Texture(uint32_t id, const glm::uvec2 &size);
        ~Texture();

        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        void bind(uint32_t slot = 0) const;
        void unbind() const;

        [[nodiscard]] glm::uvec2 getSize() const;
        [[nodiscard]] uint32_t getWidth() const;
        [[nodiscard]] uint32_t getHeight() const;
        [[nodiscard]] uint32_t getID() const;

        static Texture loadFile(const std::string& path);

    private:
        uint32_t m_id = 0;
        glm::uvec2 m_size{0};
    };

}

#endif //KTANKS_TEXTURE_H