#include <SDL3/SDL_opengl.h>
#include <spdlog/spdlog.h>

#include "ktanks/window/Window.h"

int main() {
    auto window = ktanks::Window("kTanks");
    while (window.isRunning()) {
        ktanks::Event e{};
        while (ktanks::popEvent(e)) {
            if (e.type == ktanks::EventType::WindowClose) {
                window.close();
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1,1,1,1);

        window.swapBuffers();
    }
    return 0;
}
