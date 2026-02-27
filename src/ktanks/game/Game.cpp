#include "Game.h"

#include <SDL3/SDL_timer.h>
#include <spdlog/spdlog.h>

#include "glad/gl.h"
#include "ktanks/graphics/Color.h"
#include "ktanks/utils/Locator.h"

namespace ktanks {

    Game::Game() {
        m_window = std::make_shared<Window>("kTanks");
    }

    Game::~Game() = default;

    void Game::run() {
        Locator::serve(&m_assets);
        Color a;
        const uint64_t freq = SDL_GetPerformanceFrequency();
        uint64_t last = SDL_GetPerformanceCounter();

        onInit();
        while (m_window->isRunning()) {
            Event e{};
            while (popEvent(e)) {
                onEvent(e);
                if (e.type == EventType::WindowClose) {
                    m_window->close();
                }
            }

            const uint64_t now = SDL_GetPerformanceCounter();
            const float deltaTime = static_cast<float>(now - last) / static_cast<float>(freq);
            onUpdate(deltaTime);
            last = now;

            glClear(GL_COLOR_BUFFER_BIT);
            onDraw();
            m_window->swapBuffers();
        }
    }

    void Game::onInit() {

    }

    void Game::onUpdate(const float dt) {
        spdlog::info("Update dt: {}", dt);
    }

    void Game::onDraw() {

    }

    void Game::onEvent(const Event& e) {

    }

}
