#ifndef KTANKS_LOCATOR_H
#define KTANKS_LOCATOR_H

#include "AssetsManager.h"

namespace ktanks {

    class Locator final {
    public:
        static AssetsManager& getAssets();

        static void serve(AssetsManager*);

    private:
        inline static AssetsManager* m_assets_manager;
    };

}

#endif //KTANKS_LOCATOR_H