#include "Locator.h"

namespace ktanks {

    AssetsManager& Locator::getAssets() {
        return *m_assets_manager;
    }

    void Locator::serve(AssetsManager* assets_manager) {
        m_assets_manager = assets_manager;
    }

}