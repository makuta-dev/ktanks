#ifndef KTANKS_ISCREEN_H
#define KTANKS_ISCREEN_H

namespace ktanks {

    struct Event;

    class IScreen {
    public:
        virtual ~IScreen() = default;

        virtual void onUpdate(float dt) = 0;
        virtual void onDraw() = 0;
        virtual void onEvent(const Event&) = 0;
    };

}

#endif //KTANKS_ISCREEN_H