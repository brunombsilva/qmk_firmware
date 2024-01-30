#include QMK_KEYBOARD_H
#include "enums.h"
#include "print.h"
#include "ansi.h"

void rgb_test_show_user(void);
void set_rgb_defaults(void);
void update_rbg_side_indicators(void);

//const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
//    &delete_key_override,
//    NULL // Null terminate the array of overrides!
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[DEFAULT_LAYER] = LAYOUT(
	KC_ESC,     KC_1,   	    KC_2,   	    KC_3,  		    KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	    KC_MINS,	KC_EQL, 	KC_BSPC,
	KC_TAB, 	KC_Q,   	    KC_W,   	    KC_E,  		    KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,       	KC_LBRC,	KC_RBRC, 	KC_BSLS,
	KC_CAPS,	KC_A,   	    KC_S,   	    KC_D,  		    KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	    KC_QUOT, 	            KC_ENT,
	KC_LSFT,    KC_Z,   	    KC_X,   	    KC_C,  		    KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,	    _______,	KC_UP,		CK_LEAD,
	KC_LCTL,	KC_LALT,	    KC_LGUI,										        KC_SPC, 							KC_RGUI,	TD(TD_LAYER),   KC_LEFT,	KC_DOWN,    KC_RGHT),

[FN_LAYER] = LAYOUT(
	KC_GRV, 	KC_BRID,  	    KC_BRIU,        MAC_TASK,       MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD,    KC_VOLU, 	KC_DEL,
	_______, 	KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     _______,   	_______,    _______,    _______,    _______,   	_______,  	_______,   	DEV_RESET,  SLEEP_MODE, BAT_SHOW,
	_______, 	KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    _______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	_______,    KC_MS_WH_UP,    CK_RGB_TEST,    KC_MS_WH_DOWN,  _______,   	_______,   	_______,   	_______,   	RGB_SPD,	RGB_SPI,  	_______,	_______,    KC_PGUP,    _______,
	_______,	_______,	    _______,										        _______, 					        _______,	_______,   	KC_HOME,	KC_PGDN,    KC_END),

[FN_SHIFT_LAYER] = LAYOUT(
	SHIFT_GRV, 	            KC_F1,  	    KC_F2,  	    KC_F3, 		    KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	_______,
	_______, 	            LNK_BLE1,  	    LNK_BLE2,  	    LNK_BLE3,  	    LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______,    _______,
	_______, 	            _______,   	    _______,   	    _______,  	    _______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	            _______,
	_______,	            _______,   	    _______,   	    AC_TOGG,  	    _______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,	_______, 	_______,    _______,
	_______,	            _______,	    _______,										        _______, 							_______,	_______,   	_______,	_______,    _______),
};

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, A_16,   B_16,   C_16},      // "Esc"
    {0, A_2,    B_2,    C_2},       // "!1"
    {0, A_3,    B_3,    C_3},       // "@2"
    {0, A_4,    B_4,    C_4},       // "#3"
    {0, A_5,    B_5,    C_5},       // "$4"
    {0, A_6,    B_6,    C_6},       // "%5"
    {0, A_7,    B_7,    C_7},       // "^6"
    {0, A_8,    B_8,    C_8},       // "&7"
    {0, A_9,    B_9,    C_9},       // "*8"
    {0, A_10,   B_10,   C_10},      // "(9"
    {0, A_11,   B_11,   C_11},      // ")0"
    {1, D_1,    E_1,    F_1},       // "_-"
    {1, D_2,    E_2,    F_2},       // "+="
    {1, D_3,    E_3,    F_3},       // "Backsp"
    {0, D_1,    E_1,    F_1},       // "Tab"
    {0, D_2,    E_2,    F_2},       // "Q"
    {0, D_3,    E_3,    F_3},       // "W"
    {0, D_4,    E_4,    F_4},       // "E"
    {0, D_5,    E_5,    F_5},       // "R"
    {0, D_6,    E_6,    F_6},       // "T"
    {0, D_7,    E_7,    F_7},       // "Y"
    {0, D_8,    E_8,    F_8},       // "U"
    {0, D_9,    E_9,    F_9},       // "I"
    {0, D_10,   E_10,   F_10},      // "O"
    {0, D_11,   E_11,   F_11},      // "P"
    {1, G_1,    H_1,    I_1},       // "{["
    {1, G_2,    H_2,    I_2},       // "}]"
    {1, G_3,    H_3,    I_3},       // "|\\"
    {0, G_1,    H_1,    I_1},       // "Caps"
    {0, G_2,    H_2,    I_2},       // "A"
    {0, G_3,    H_3,    I_3},       // "S"
    {0, G_4,    H_4,    I_4},       // "D"
    {0, G_5,    H_5,    I_5},       // "F"
    {0, G_6,    H_6,    I_6},       // "G"
    {0, G_7,    H_7,    I_7},       // "H"
    {0, G_8,    H_8,    I_8},       // "J"
    {0, G_9,    H_9,    I_9},       // "K"
    {0, G_10,   H_10,   I_10},      // "L"
    {0, G_11,   H_11,   I_11},      // ":"
    {1, G_16,   H_16,   I_16},      // "\""
    {1, G_14,   H_14,   I_14},      // "Enter"
    {0, J_1,    K_1,    L_1},       // "Shift"
    {0, J_3,    K_3,    L_3},       // "Z"
    {0, J_4,    K_4,    L_4},       // "X"
    {0, J_5,    K_5,    L_5},       // "C"
    {0, J_6,    K_6,    L_6},       // "V"
    {0, J_7,    K_7,    L_7},       // "B"
    {0, J_8,    K_8,    L_8},       // "N"
    {0, J_9,    K_9,    L_9},       // "M"
    {0, J_10,   K_10,   L_10},      // "<,"
    {0, J_11,   K_11,   L_11},      // ">."
    {1, J_1,    K_1,    L_1},       // "?/"
    {1, J_3,    K_3,    L_3},       // "Shift"
    {1, J_4,    K_4,    L_4},       // "↑"
    {1, G_4,    H_4,    I_4},       // "Del"
    {0, J_16,   K_16,   L_16},      // "Ctrl"
    {0, J_15,   K_15,   L_15},      // "Opt"
    {0, J_14,   K_14,   L_14},      // "Cmd"
    {0, J_13,   K_13,   L_13},      // "Space"
    {0, J_12,   K_12,   L_12},      // "Cmd"
    {1, J_16,   K_16,   L_16},      // "Fn"
    {1, J_13,   K_13,   L_13},      // "←"
    {1, J_12,   K_12,   L_12},      // "↓"
    {1, J_11,   K_11,   L_11},      // "→"

    {1, A_5,    B_5,    C_5},       // logo left
    {1, A_4,    B_4,    C_4},       //
    {1, A_3,    B_3,    C_3},       //
    {1, A_2,    B_2,    C_2},       //
    {1, A_1,    B_1,    C_1},       //

    {1, A_6,    B_6,    C_6},       // logo right
    {1, A_7,    B_7,    C_7},       //
    {1, A_8,    B_8,    C_8},       //
    {1, A_9,    B_9,    C_9},       //
    {1, A_10,   B_10,   C_10}       //
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case CK_LEAD: // QK_LEAD
            if (record->event.pressed) {
                leader_start();
            }
            return false;
        case CK_AAT: // AC_TOGG
            if (record->event.pressed) {
                autocorrect_toggle();
            }
            return false;
        case CK_RGB_TEST:
            if (record->event.pressed) {
                rgb_test_show_user();
            }
            return false;
    }
    return true;
}

extern DEV_INFO_STRUCT dev_info;

void keyboard_post_init_user(void) {
    // Reset to single default layer, regarldess of Mac|Win keyboard switch.
    switch (dev_info.sys_sw_state) {
        case SYS_SW_MAC:
        case SYS_SW_WIN:
            default_layer_set(DEFAULT_LAYER);
            break;
    }
    set_rgb_defaults();
}

void housekeeping_task_user() {
    // Maybe reset default layer?
    update_rbg_side_indicators();
}
