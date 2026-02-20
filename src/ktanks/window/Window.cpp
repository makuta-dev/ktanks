#include "Window.h"

#include <SDL3/SDL_init.h>
#include <spdlog/spdlog.h>

namespace ktanks {

    Window::Window(const std::string& title, const glm::ivec2& size) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            spdlog::error("Cannot init SDL3 library: {}", SDL_GetError());
            return;
        }

        constexpr auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
        m_window = SDL_CreateWindow(title.c_str(), size.x, size.y, flags);
        if (!m_window) {
            spdlog::error("Cannot create window: {}", SDL_GetError());
            return;
        }

        m_context = SDL_GL_CreateContext(m_window);
        if (!m_context) {
            spdlog::error("Cannot create OpenGL context: {}", SDL_GetError());
            return;
        }

        SDL_GL_MakeCurrent(m_window, m_context);
        SDL_GL_SetSwapInterval(1);

        m_running = true;
    }

    Window::~Window() {
        if (m_context) {
            SDL_GL_DestroyContext(m_context);
        }
        if (m_window) {
            SDL_DestroyWindow(m_window);
        }
        SDL_Quit();
    }

    bool Window::isRunning() const {
        return m_running;
    }

    glm::ivec2 Window::getSize() const {
        if (m_window) {
            glm::ivec2 size;
            SDL_GetWindowSize(m_window, &size.x, &size.y);
            return size;
        }
        return {0,0};
    }

    std::string Window::getTitle() const {
        if (m_window) {
            return SDL_GetWindowTitle(m_window);
        }
        return "";
    }

    glm::ivec2 Window::getPosition() const {
        if (m_window) {
            glm::ivec2 pos;
            SDL_GetWindowPosition(m_window, &pos.x, &pos.y);
            return pos;
        }
        return {0,0};
    }

    void Window::close() {
        m_running = false;
    }

    void Window::setSize(const glm::ivec2& size) const {
        if (m_window) {
            SDL_SetWindowSize(m_window, size.x, size.y);
        }
    }

    void Window::setPosition(const glm::ivec2& position) const {
        if (m_window) {
            SDL_SetWindowPosition(m_window, position.x, position.y);
        }
    }

    void Window::setTitle(const std::string& title) const {
        if (m_window) {
            SDL_SetWindowTitle(m_window, title.c_str());
        }
    }

    SDL_Window* Window::getSDLWindow() const {
        return m_window;
    }

    void Window::swapBuffers() const {
        if (m_window) {
            SDL_GL_SwapWindow(m_window);
        }
    }

}