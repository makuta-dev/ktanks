#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

#include "graphics/Shader.h"
#include "graphics/Texture.h"

namespace ktanks {

    class Event;

    class Tanks final {
    public:
        Tanks();
        ~Tanks();

        void onUpdate(float dt);
        void onDraw();
        void onEvent(const Event&);

    private:
        uint vao, vbo;
        Shader shader;
        Texture texture;
        glm::mat4 projection;
    };

}

#endif //KTANKS_TANKS_H