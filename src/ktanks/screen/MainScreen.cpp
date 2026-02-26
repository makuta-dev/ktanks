#include "MainScreen.h"

#include "SetupScreen.h"
#include "ktanks/screen/PlayScreen.h"
#include "ktanks/ui/Button.h"
#include "ktanks/ui/List.h"
#include "ktanks/window/Window.h"

namespace ktanks {

    MainScreen::MainScreen(ScreenManager* m) : IScreen(m) , m_background({32,32}, TerrainSprite::Sand1){
        m_center_widget = std::make_unique<List>(Orientation::Vertical);
    }

    MainScreen::~MainScreen() = default;

    void MainScreen::onInit() {
        m_center_widget->addChild(std::make_unique<Button>("Play", [this]{ getManager().navigate(std::make_unique<PlayScreen>(&getManager())); }));
        m_center_widget->addChild(std::make_unique<Button>("Level Editor", [this]{ getManager().navigate(std::make_unique<SetupScreen>(&getManager())); }));
        m_center_widget->addChild(std::make_unique<Button>("Exit", []{ closeEvent(); }));

        m_center_widget->invalidateLayout();
        m_center_widget->setPosition(glm::vec2(getManager().getViewport()) / 2.f - m_center_widget->getSize() / 2.f);
    }

    void MainScreen::onUpdate(const float dt) {
        m_center_widget->onUpdate(dt);
    }

    void MainScreen::onDraw(Renderer& r) {
        r.drawTerrain(m_background);
        m_center_widget->onRender(r);
    }

    void MainScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_center_widget->invalidateLayout();
            m_center_widget->setPosition(glm::vec2(getManager().getViewport()) / 2.f - m_center_widget->getSize() / 2.f);
        }
        m_center_widget->onChildEvent(e);
    }

}
