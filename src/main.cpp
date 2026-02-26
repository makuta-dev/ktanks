#include <chrono>
#include <SDL3/SDL_keyboard.h>

#include "ktanks/window/Window.h"
#include "ktanks/Game.h"

#include "glad/gl.h"
#include "ktanks/utils/InputManager.h"

using hclock = std::chrono::steady_clock;

int main() {
    auto window = ktanks::Window("kTanks");
    const auto size = window.getSize();
    auto tanks = ktanks::Game();
    {
        tanks.onEvent({
            .type = ktanks::EventType::WindowResize,
            .onWResize = {
                .width = size.x,
                .height = size.y
            }
        });
    }
    auto last = hclock::now();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.f, 0.0f, 0.0f, 1.f);
    tanks.onInit();
    while (window.isRunning()) {
        if (ktanks::InputManager::needInput()) {
            SDL_StartTextInput(window.getSDLWindow());
        } else {
            SDL_StopTextInput(window.getSDLWindow());
        }

        const auto now = hclock::now();
        const auto dt = std::chrono::duration<float>(now - last).count();
        tanks.onUpdate(dt);
        last = now;

        ktanks::Event e{};
        while (ktanks::popEvent(e)) {
            tanks.onEvent(e);
            if (e.type == ktanks::EventType::WindowClose) {
                window.close();
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        tanks.onDraw();
        window.swapBuffers();
    }
    return 0;
}
