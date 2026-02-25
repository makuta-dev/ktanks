#ifndef KTANKS_ISCREEN_H
#define KTANKS_ISCREEN_H

#include <memory>
#include <glm/vec2.hpp>

namespace ktanks {

    struct Event;
    class IScreen;

    using ScreenPtr = std::unique_ptr<IScreen>;

    enum class ScreenID {
        Main,
        Play,
    };

    class ScreenManager {
    public:
        ScreenManager() = default;
        virtual ~ScreenManager() = default;

        virtual void navigate(ScreenID) = 0;
        virtual glm::uvec2 getViewport() = 0;
    };

    class IScreen {
    public:
        explicit IScreen(ScreenManager* manager) : m_manager(manager) {}
        virtual ~IScreen() = default;

        virtual void onInit(){}
        virtual void onUpdate(float dt) = 0;
        virtual void onDraw() = 0;
        virtual void onEvent(const Event&) = 0;

        [[nodiscard]] ScreenManager& getManager() const {
            return *m_manager;
        }

    private:
        ScreenManager* m_manager;
    };

}

#endif //KTANKS_ISCREEN_H