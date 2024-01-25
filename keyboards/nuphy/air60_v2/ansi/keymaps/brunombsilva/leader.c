#include QMK_KEYBOARD_H

// Emoji key sequences.
#define SEQ_TU leader_sequence_two_keys(KC_T, KC_U)
#define SEQ_TD leader_sequence_two_keys(KC_T, KC_D)
#define SEQ_CAT leader_sequence_three_keys(KC_C, KC_A, KC_T)
#define SEQ_TKS leader_sequence_three_keys(KC_T, KC_K, KC_S)
#define SEQ_ROFL leader_sequence_four_keys(KC_R, KC_O, KC_F, KC_L)
#define SEQ_OOPS leader_sequence_four_keys(KC_O, KC_O, KC_P, KC_S)

// MacOS specific. Assumes there's only 1 input source other than
// Unicode Hex Input is present, that that it's currently selected.
// When the leader sequence matches:
//  - switches input source to Unicode Hex Input
//  - sends Unicode surrogate characters for emoji
//  - Restores input source to other than  Unicode Hex Input
#define SEND_EMOJI(leader_sequence, unicode_surrogate_pair) \
        if (leader_sequence) {\
            tap_code16(LCA(KC_SPACE));\
            SEND_STRING(SS_LALT(unicode_surrogate_pair));\
            tap_code16(LCA(KC_SPACE));\
            return;\
        }


void leader_end_user(void) {
    SEND_EMOJI(SEQ_CAT,     "D83D+DC31"); // 🐱
    SEND_EMOJI(SEQ_ROFL,    "D83E+DD23"); // 🤣
    SEND_EMOJI(SEQ_TKS,     "D83D+DE4F"); // 🙏
    SEND_EMOJI(SEQ_TU,      "D83D+DC4D"); // 👍
    SEND_EMOJI(SEQ_TD,      "D83D+DC4E"); // 👎
    SEND_EMOJI(SEQ_OOPS,    "D83D+DE05"); // 😅
}
