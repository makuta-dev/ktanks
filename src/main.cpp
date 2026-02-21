#include <chrono>

#include "ktanks/graphics/Renderer.h"
#include "ktanks/window/Window.h"
#include "ktanks/Tanks.h"

#include "glad/gl.h"

using hclock = std::chrono::steady_clock;

int main() {
    auto window = ktanks::Window("kTanks");
    const auto size = window.getSize();
    auto asset_manager = ktanks::AssetManager();
    auto tanks = ktanks::Tanks(asset_manager);
    auto renderer = ktanks::Renderer(asset_manager);
    {
        renderer.resize(size.x, size.y);
        tanks.onEvent({
            .type = ktanks::EventType::WindowResize,
            .onWResize = {
                .width = size.x,
                .height = size.y
            }
        });
    }
    auto last = hclock::now();

    glClearColor(0.f, 0.0f, 0.0f, 1.f);

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
            if (e.type == ktanks::EventType::WindowResize) {
                renderer.resize(e.onWResize.width, e.onWResize.height);
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.beginFrame();
        tanks.onDraw(renderer);
        renderer.endFrame();

        window.swapBuffers();
    }
    return 0;
}
