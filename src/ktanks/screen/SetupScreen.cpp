#include "SetupScreen.h"

#include <algorithm>
#include <SDL3/SDL_scancode.h>

#include "EditorScreen.h"
#include "MainScreen.h"
#include "ktanks/ui/Button.h"
#include "ktanks/ui/Input.h"
#include "ktanks/ui/Label.h"
#include "ktanks/ui/List.h"

namespace ktanks {

    bool isNumbers(const std::string& text){
        return std::ranges::all_of(text, [](auto c){return std::isdigit(c);});
    }

    SetupScreen::SetupScreen(ScreenManager *manager) : IScreen(manager),
        m_background({32,32}, TerrainSprite::Grass2) {}

    void SetupScreen::onInit() {
        m_widget = std::make_unique<List>(Orientation::Vertical);

        m_widget->addChild(std::make_unique<Label>("Set level size"));
        m_widget->addChild(std::make_unique<Input>("Width:", [this](const auto& text) {
            if (isNumbers(text)) {
                m_world_size.x = std::stoi(text);
            }
        }));
        m_widget->addChild(std::make_unique<Input>("Height:",[this](const auto& text) {
            if (isNumbers(text)) {
                m_world_size.y = std::stoi(text);
            }
        }));
        m_widget->addChild(std::make_unique<Button>("Next",[this] {
            getManager().navigate(std::make_unique<EditorScreen>(m_world_size, &getManager()));
        }));

        m_widget->invalidateLayout();
        m_widget->setPosition(getManager().getViewport() / 2u - glm::uvec2(m_widget->getSize()) / 2u);
    }

    void SetupScreen::onUpdate(const float dt) {
        m_widget->onUpdate(dt);
    }

    void SetupScreen::onDraw(Renderer& r) {
        r.drawTerrain(m_background);
        m_widget->onRender(r);
    }

    void SetupScreen::onEvent(const Event& e) {
        m_widget->onChildEvent(e);
        if (e.type == EventType::WindowResize) {
            m_widget->invalidateLayout();
            m_widget->setPosition(getManager().getViewport() / 2u - glm::uvec2(m_widget->getSize()) / 2u);
        }
        if (e.type == EventType::Key) {
            if (e.onKey.pressed && e.onKey.key == SDL_SCANCODE_ESCAPE) {
                getManager().navigate(std::make_unique<MainScreen>(&getManager()));
            }
        }
    }

}
