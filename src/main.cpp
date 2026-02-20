#include <chrono>

#include "ktanks/window/Window.h"
#include "ktanks/Tanks.h"

using hclock = std::chrono::steady_clock;

int main() {
    auto window = ktanks::Window("kTanks");
    auto tanks = ktanks::Tanks();
    auto last = hclock::now();
    while (window.isRunning()) {
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

        tanks.onDraw();
        window.swapBuffers();
    }
    return 0;
}
