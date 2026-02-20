#include "Tanks.h"

#include <spdlog/spdlog.h>

namespace ktanks {

    Tanks::Tanks() {

    }

    Tanks::~Tanks() {

    }

    void Tanks::onUpdate(float dt) {
        spdlog::info("dt = {}",dt);
    }

    void Tanks::onDraw() {

    }

    void Tanks::onEvent(const Event&) {

    }

}
