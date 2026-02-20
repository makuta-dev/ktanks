#ifndef KTANKS_TANKS_H
#define KTANKS_TANKS_H

namespace ktanks {

    class Renderer;
    class Event;

    class Tanks final {
    public:
        Tanks();
        ~Tanks();

        void onUpdate(float dt);
        void onDraw(Renderer&);
        void onEvent(const Event&);
    };

}

#endif //KTANKS_TANKS_H