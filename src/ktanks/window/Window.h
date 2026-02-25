#ifndef KTANKS_WINDOW_H
#define KTANKS_WINDOW_H

#include <SDL3/SDL_video.h>
#include <glm/vec2.hpp>

#include <string>
#include <SDL3/SDL_scancode.h>

#include "Event.h"

namespace ktanks {

    class Window final {
    public:
        explicit Window(const std::string& title, const glm::ivec2& size = {640,480});
        ~Window();

        [[nodiscard]] bool isRunning() const;
        [[nodiscard]] glm::ivec2 getSize() const;
        [[nodiscard]] std::string getTitle() const;
        [[nodiscard]] glm::ivec2 getPosition() const;

        void close();
        void setSize(const glm::ivec2& size) const;
        void setPosition(const glm::ivec2& position) const;
        void setTitle(const std::string& title) const;

        [[nodiscard]] SDL_Window* getSDLWindow() const;
        void swapBuffers() const;

        static bool isPressed(SDL_Scancode key);

    private:
        bool m_running = false;
        SDL_Window *m_window = nullptr;
        SDL_GLContext m_context = nullptr;
    };

    bool popEvent(Event&);
    void closeEvent();

}

#endif //KTANKS_WINDOW_H