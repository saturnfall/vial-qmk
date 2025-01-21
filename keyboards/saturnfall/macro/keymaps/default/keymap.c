// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define NUM_TIMEOUT 5000

enum layers {
    _BASE,
    _NUM
};

enum custom_keys {
    A_T_HOLD = SAFE_RANGE
};

void matrix_scan_user(void) {
    if (get_highest_layer(layer_state) == _NUM && last_input_activity_elapsed() > NUM_TIMEOUT) {
        layer_off(_NUM);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_T_HOLD:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_TAB));
            }
            else {
                unregister_code(KC_LALT);
            }

        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_HOME,    KC_END,     KC_BSPC,
        A_T_HOLD,   G(KC_TAB),  KC_ENT,
        C(KC_A),    C(KC_C),    C(KC_V),
        MS_BTN1,    MS_BTN2,    TG(1)
    ),

    [_NUM] = LAYOUT(
        KC_7,       KC_8,       KC_9,
        KC_4,       KC_5,       KC_6,
        KC_1,       KC_2,       KC_3,
        KC_DOT,     KC_0,       KC_TRNS
    )
};
