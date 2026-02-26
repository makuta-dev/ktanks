#ifndef KTANKS_INPUTMANAGER_H
#define KTANKS_INPUTMANAGER_H

namespace ktanks {

    class InputManager final {
    public:
        static void enableInput();
        static void disableInput();

        static bool needInput();

    private:
        inline static bool is_input_enabled{false};
    };

}

#endif //KTANKS_INPUTMANAGER_H