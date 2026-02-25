#ifndef KTANKS_FRAME_H
#define KTANKS_FRAME_H

#include "ktanks/core/IWidget.h"

namespace ktanks {

    class Frame final : public IWidget{
    public:
        Frame();
        ~Frame() override;

        void onRender(UIRenderer &) override;
    };

}

#endif //KTANKS_FRAME_H