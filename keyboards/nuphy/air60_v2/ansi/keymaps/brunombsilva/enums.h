// Keyboard layers available.
enum layers {
    DEFAULT_LAYER,
    FN_LAYER,
    FN_SHIFT_LAYER,
};

// Custom keycodes.
// Starting at QK_KB_25 (after the last custom keycode defined in ansi.h:custom_keycodes)
// instead of SAFE_RANGE to make the proper names to appear in Via (instead the hexadecimal codes).
enum my_keycodes {
  CK_LEAD = QK_KB_25,
  CK_AAT,
  CK_RGB_TEST
};

// Tap Dance keycodes.
enum tap_dance {
    TD_LAYER,
};
