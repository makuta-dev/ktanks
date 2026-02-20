#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

namespace ktanks {

    class Event;

    class Tanks final {
    public:
        Tanks();
        ~Tanks();

        void onUpdate(float dt);
        void onDraw();
        void onEvent(const Event&);
    };

}

#endif //KTANKS_TANKS_H