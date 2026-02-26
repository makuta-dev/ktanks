#ifndef KTANKS_GUIDATA_H
#define KTANKS_GUIDATA_H

namespace ktanks {

    enum class GuiSprites : int {
        input_outline_square = 0,
        input_square,
        arrow_basic_e,
        arrow_basic_w,
        button_rectangle_border,
        button_rectangle_depth_border,
        button_rectangle_depth_flat,
        button_rectangle_depth_gloss,
        button_rectangle_depth_gradient,
        button_rectangle_depth_line,
        button_rectangle_flat,
        button_rectangle_gloss,
        button_rectangle_gradient,
        button_rectangle_line,
        check_square_color_checkmark,
        check_square_color,
        check_square_grey_checkmark,
        check_square_grey,
        slide_hangle,
        slide_horizontal_color,
        slide_horizontal_grey,
    };

    enum class Icon : int {
        AudioOff = 21,
        AudioOn,
        Crosshair,
        CrosshairPlus,
        Exit,
        Export,
        Gear,
        Home,
        Save,
        ZoomDefault,
        ZoomIn,
        ZoomOut
    };

}

#endif //KTANKS_GUIDATA_H