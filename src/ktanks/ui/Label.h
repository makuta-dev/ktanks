#ifndef KTANKS_LABEL_H
#define KTANKS_LABEL_H

#include "ktanks/core/IWidget.h"

namespace ktanks {

    class Label final : public IWidget{
    public:
        explicit Label(std::string text);

        void onRender(UIRenderer &renderer) override;

    private:
        std::string m_text;
    };

}

#endif //KTANKS_LABEL_H