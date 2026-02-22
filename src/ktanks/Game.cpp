#include "Game.h"

#include <SDL3/SDL_scancode.h>

#include "window/Window.h"


namespace ktanks {

    Game::Game(const AssetManager &asset_manager) : tank(glm::vec2{100}, asset_manager,TankType::Black), map(glm::vec2{32,32}){
        font = asset_manager.getFont("Kenney_Future",16);
        terrain_atlas = asset_manager.getTerrainAtlas();
    }

    Game::~Game() = default;

    void Game::onUpdate(const float dt) {
        lastFps += dt;
        if (lastFps > 0.25f) {
            const auto newFps = 1.0f / dt;
            fps = (fps + newFps) / 2.f;
            lastFps = 0.f;
        }

        uint8_t key = 0;

        if (Window::isPressed(SDL_SCANCODE_W)) key |= 1 << 0;
        if (Window::isPressed(SDL_SCANCODE_S)) key |= 1 << 1;
        if (Window::isPressed(SDL_SCANCODE_A)) key |= 1 << 2;
        if (Window::isPressed(SDL_SCANCODE_D)) key |= 1 << 3;
        if (Window::isPressed(SDL_SCANCODE_LEFT)) key |= 1 << 4;
        if (Window::isPressed(SDL_SCANCODE_RIGHT)) key |= 1 << 5;

        tank.move(key);
        tank.onUpdate(dt);

        camera.update(tank.getPosition(),view,dt);
    }

    void Game::onDraw(Renderer& r) {
        r.setViewMatrix(camera.getViewMatrix());
        constexpr auto tile_size = glm::vec2(128);
        const auto size = map.getSize();
        r.setTexture(terrain_atlas.getTextureID());
        for (int y = 0; y < size.y; y++) {
            for (int x = 0; x < size.x; x++) {
                const auto pos = glm::uvec2{x, y};
                const auto tile = map.get(pos);
                if (const auto reg = terrain_atlas.at(static_cast<int>(tile))) {
                    r.drawSprite(glm::vec2(pos) * tile_size,tile_size,*reg);
                }
            }
        }
        tank.onDraw(r);

        r.setViewMatrix(glm::mat4{1.f});
        r.drawText(std::format("{:3.2f}",fps),{0,16},{1,1,1},font);
    }

    void Game::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            view = glm::uvec2(e.onWResize.width, e.onWResize.height);
        }
    }

}
