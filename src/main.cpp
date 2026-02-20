#include <SDL3/SDL_events.h>

#include "ktanks/window/Window.h"

int main() {
    auto window = ktanks::Window("kTanks");
    while (window.isRunning()) {

        SDL_Event event{};
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                window.close();
            }
        }

        window.swapBuffers();
    }
    return 0;
}
