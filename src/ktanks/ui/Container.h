#ifndef KTANKS_CONTAINER_H
#define KTANKS_CONTAINER_H

#include "ktanks/core/IWidget.h"

namespace ktanks {

    class Container final : public IWidget{
    public:
        Container();

        void onRender(Renderer &renderer) override;
        void performLayout() override;
    };

}

#endif //KTANKS_CONTAINER_H