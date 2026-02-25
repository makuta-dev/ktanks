#include "MainScreen.h"

#include "ktanks/ui/Frame.h"

namespace ktanks {

    MainScreen::MainScreen(AssetManager& a, ScreenManager* m) : IScreen(m), m_renderer(a) {
        m_center_widget = std::make_unique<Frame>();
    }

    MainScreen::~MainScreen() = default;

    void MainScreen::onInit() {
        m_center_widget->setSize({300,200});
        m_center_widget->setPosition(glm::vec2(getManager().getViewport()) / 2.f - m_center_widget->getSize() / 2.f);
    }

    void MainScreen::onUpdate(const float dt) {
        m_center_widget->onUpdate(dt);
    }

    void MainScreen::onDraw() {
        m_renderer.beginFrame();
        onRender(m_renderer);
        m_renderer.endFrame();
    }

    void MainScreen::onEvent(const Event& e) {
        if (e.type == EventType::WindowResize) {
            m_renderer.resize(e.onWResize.width, e.onWResize.height);

            m_center_widget->setPosition(glm::vec2(getManager().getViewport()) / 2.f - m_center_widget->getSize() / 2.f);
            m_center_widget->invalidateLayout();
        }
        m_center_widget->onEvent(e);
    }

    void MainScreen::onRender(UIRenderer& r) {
        m_center_widget->onRender(r);
    }

}
