#include "Tanks.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <spdlog/spdlog.h>

#include "glad/gl.h"
#include "utils/AssetManager.h"
#include "window/Event.h"

namespace ktanks {

    Tanks::Tanks() {
        auto assetsManager = AssetManager();
        shader = assetsManager.getShader("simple");
        texture = assetsManager.getTexture("ui/star");
        projection = glm::mat4(1.f);
        vao = vbo = 0;

        constexpr float vertices[] = {
            0.0f,  128.f, 0.0f,     0.0f, 1.0f, // Top Right
            128.f, 128.f, 0.0f,     1.0f, 1.0f, // Bottom Right
            128.f,  0.0f, 0.0f,     1.0f, 0.0f, // Bottom Left

            0.0f,  128.f, 0.0f,     0.0f, 1.0f, // Top Right
            128.f,  0.0f, 0.0f,     1.0f, 0.0f, // Bottom Left
            0.0f,  0.0f,  0.0f,     0.0f, 0.0f, // Top Left
        };

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glClearColor(0.2f, 0.2f, 0.2f, 1.f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Tanks::~Tanks() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    void Tanks::onUpdate(float dt) {
        spdlog::info("dt = {}",dt);
    }

    void Tanks::onDraw() {
        glClear(GL_COLOR_BUFFER_BIT);

        texture.bind();

        shader.use();
        shader.setMat4("proj", projection);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void Tanks::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            const auto w = e.onWResize.width;
            const auto h = e.onWResize.height;
            projection = glm::ortho<float>(0.f, w, h, 0.f);
            glViewport(0, 0, w, h);
        }
    }

}
