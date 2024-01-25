#include QMK_KEYBOARD_H
#include "enums.h"

// Values from ../../side.c
#define SIDE_LINE           5
#define SIDE_INDEX          64
#define SIDE_OFF            4

#define RGB_CAPS_ON colour_lib[4][0], colour_lib[4][1], colour_lib[4][2]
#define RGB_LEADER_ON colour_lib[6][0], colour_lib[6][1], colour_lib[6][2]
#define RGB_AUTOCORRECT_ON colour_lib[1][0], colour_lib[1][1], colour_lib[1][2]
#define COLOR_ARRAY(color) color[0], color[1], color[2]

void rgb_matrix_update_pwm_buffers(void);
void set_left_rgb(uint8_t, uint8_t, uint8_t);
void set_right_rgb(uint8_t, uint8_t, uint8_t);

// From ../../side.c
extern uint8_t side_mode;
// From ../../side.h
extern uint8_t colour_lib[256][3];

// Default colors to indicate highest layer.
HSV layer_color_indicators[] = {
    [DEFAULT_LAYER] = {HSV_BLACK},
    [FN_LAYER] = {HSV_RED},
    [FN_SHIFT_LAYER] = {HSV_GREEN}
};

// Current color used to indicate highest layer.
RGB layer_color_indicator = {RGB_BLACK};

// An indicator is shown if the current color is not black.
bool show_layer_color_indicator(void) {
    return layer_color_indicator.r != 0 ||  layer_color_indicator.g != 0 || layer_color_indicator.b != 0;
}

// Default rgb lights configuration to be set when keyboard is powered on.
void set_rgb_defaults(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_WIDE);
    rgb_matrix_sethsv(HSV_WHITE);
    side_mode = SIDE_OFF;
}

// Lights up highest layer indicator color in the leds under the keys
// configured for that layer.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer < 0) return false;

    layer_color_indicator = hsv_to_rgb(layer_color_indicators[layer]);
    if (!show_layer_color_indicator()) return false;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= led_min && index < led_max && index != NO_LED &&
            keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                rgb_matrix_set_color(index, layer_color_indicator.r, layer_color_indicator.g, layer_color_indicator.b);
            }
        }
    }
    return false;
}

// Uses side leads to convey keyboard status.
// - Left side: caps word/caps lock on + leader sequence active
// - Right side: Autocorrect active + highest active layer indicator color
void update_rbg_side_indicators(void) {
    int side_left_start_index = 0;
    if (is_caps_word_on() || host_keyboard_led_state().caps_lock) {
        set_left_rgb(RGB_CAPS_ON);
        side_left_start_index = SIDE_LINE / 2 + 1;
    }
    if (leader_sequence_active()) {
        set_left_rgb(RGB_LEADER_ON);
        for (int i = side_left_start_index; i < SIDE_LINE; i++) {
            rgb_matrix_set_color(SIDE_INDEX + i, RGB_LEADER_ON);
        }
    }

    int side_right_start_index = 0;

    if (autocorrect_is_enabled()) {
        for (int i = 0; i < 1; i++) {
            rgb_matrix_set_color(SIDE_INDEX + SIDE_LINE + i, RGB_AUTOCORRECT_ON);
            side_right_start_index++;
        }
    }

    if (show_layer_color_indicator()) {
        for (int i = side_right_start_index; i < SIDE_LINE; i++) {
            rgb_matrix_set_color(SIDE_INDEX + SIDE_LINE + i, layer_color_indicator.r, layer_color_indicator.g, layer_color_indicator.b);
        }
    }
}

// Sequencially applies a set of colors of interest to all leds.
// One at a time, always the same order, for 500 milliseconds.
// It also logs color information to console for inspection.
void rgb_test_show_user(void)
{
    writePinHigh(DC_BOOST_PIN);
    writePinHigh(RGB_DRIVER_SDB1);
    writePinHigh(RGB_DRIVER_SDB2);

    for(int i = 0; i< 10;i++) {
        uprintf("colour_lib[%u] RGB(%u,%u,%u) #%X%X%X\n", i, COLOR_ARRAY(colour_lib[i]), COLOR_ARRAY(colour_lib[i]));
        rgb_matrix_set_color_all(COLOR_ARRAY(colour_lib[i]));
        rgb_matrix_update_pwm_buffers();
        wait_ms(500);
    }

    // for(int i = 0; i< 100;i++) {
    //     uprintf("RGB(%u,%u,%u) #%X%X%X\n", BLAH(flow_rainbow_colour_tab[i]), BLAH(flow_rainbow_colour_tab[i]));
    //     rgb_matrix_set_color_all(BLAH(flow_rainbow_colour_tab[i]));
    //     rgb_matrix_update_pwm_buffers();
    //     wait_ms(500);
    // }

}
