#include QMK_KEYBOARD_H
#include "enums.h"

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_TAP,
    TD_TAP_HOLD,
} td_state_t;

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_TAP;
        else return TD_TAP_HOLD;
    } else {
        if (state->interrupted || !state->pressed) return TD_TAP;
        else return TD_TAP_HOLD;
    }
}

static td_state_t td_layer_state = TD_NONE;

void td_layer_finished(tap_dance_state_t *state, void *user_data) {
    td_layer_state = cur_dance(state);
    switch (td_layer_state) {
        case TD_TAP: layer_move(state->count); break;
        case TD_TAP_HOLD: layer_move(state->count); break;
        default: break;
    }
}

void td_layer_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_layer_state) {
        case TD_TAP_HOLD: layer_clear(); break;
        default: break;
    }
    td_layer_state = TD_NONE;
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_layer_finished, td_layer_reset)
};
