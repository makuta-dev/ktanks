#include "InputManager.h"

namespace ktanks {

    void InputManager::enableInput() {
        is_input_enabled = true;
    }

    void InputManager::disableInput() {
        is_input_enabled = false;
    }

    bool InputManager::needInput() {
        return is_input_enabled;
    }

}