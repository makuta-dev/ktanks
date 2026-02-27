#ifndef KTANKS_EVENT_H
#define KTANKS_EVENT_H

#include <glm/vec2.hpp>

namespace ktanks {

    enum class EventType {
        WindowClose,
        WindowResize,
        WindowMove,

        MouseButton,
        MouseMove,
        MouseWheel,

        Text,
        Key,
    };

    struct WindowResizeEvent {
        int width;
        int height;
    };

    struct WindowMoveEvent {
        int x;
        int y;
    };

    struct MouseButtonEvent {
        bool pressed;
        int button;
    };

    struct MouseMoveEvent {
        float x;
        float y;
    };

    struct MouseWheelEvent {
        float dx;
        float dy;
    };

    struct KeyEvent {
        bool pressed;
        bool repeat;
        int key;
        int mods;
    };

    struct TextEvent {
        const char* text;
    };

    struct Event {
        EventType type;
        union {
            WindowResizeEvent onWResize;
            WindowMoveEvent onWMove;
            MouseButtonEvent onMButton;
            MouseMoveEvent onMMove;
            MouseWheelEvent onMWheel;
            TextEvent onText;
            KeyEvent onKey;
        };
    };

    inline Event resizeEvent(const glm::ivec2& size) {
        return Event{
            .type = EventType::WindowResize,
            .onWResize = WindowResizeEvent{
                .width = size.x,
                .height = size.y
            }
        };
    }

}

#endif //KTANKS_EVENT_H