#include "Window.h"

#include <SDL3/SDL_init.h>
#include <spdlog/spdlog.h>

#include "glad/gl.h"

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

        if (!gladLoadGL(SDL_GL_GetProcAddress)) {
            spdlog::error("Cannot load OpenGL functions: {}", glGetError());
            return;
        }

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

    bool popEvent(Event& outEvent) {
        SDL_Event sdlEvent;

        if (!SDL_PollEvent(&sdlEvent)) {
            return false;
        }

        switch (sdlEvent.type) {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                outEvent.type = EventType::WindowClose;
                break;

            case SDL_EVENT_WINDOW_RESIZED:
                outEvent.type = EventType::WindowResize;
                outEvent.onWResize = { sdlEvent.window.data1, sdlEvent.window.data2 };
                break;

            case SDL_EVENT_WINDOW_MOVED:
                outEvent.type = EventType::WindowMove;
                outEvent.onWMove = { sdlEvent.window.data1, sdlEvent.window.data2 };
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
                outEvent.type = EventType::MouseButton;
                outEvent.onMButton = {
                    sdlEvent.type == SDL_EVENT_MOUSE_BUTTON_DOWN,
                    static_cast<int>(sdlEvent.button.button)
                };
                break;

            case SDL_EVENT_MOUSE_MOTION:
                outEvent.type = EventType::MouseMove;
                outEvent.onMMove = { sdlEvent.motion.x, sdlEvent.motion.y };
                break;

            case SDL_EVENT_MOUSE_WHEEL:
                outEvent.type = EventType::MouseWheel;
                outEvent.onMWheel = { sdlEvent.wheel.x, sdlEvent.wheel.y };
                break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                outEvent.type = EventType::Key;
                outEvent.onKey = {
                    sdlEvent.type == SDL_EVENT_KEY_DOWN,
                    (sdlEvent.key.repeat),
                    static_cast<int>(sdlEvent.key.scancode),
                    static_cast<int>(sdlEvent.key.mod)
                };
                break;

            default:
                return popEvent(outEvent);
        }

        return true;
    }

}
