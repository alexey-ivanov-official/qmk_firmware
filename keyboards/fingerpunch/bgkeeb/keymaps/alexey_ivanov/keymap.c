#include QMK_KEYBOARD_H

#ifdef PIMORONI_TRACKBALL_ENABLE
#include "drivers/sensors/pimoroni_trackball.h"
#include "pointing_device.h"
#include "color.h"
#endif

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

bool is_caps_lock_on;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_split_3x5_4(
  KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,         KC_Y,         KC_U,         KC_I,         KC_O,         KC_P,
  LSFT_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LGUI_T(KC_F), KC_G,         KC_H,         RGUI_T(KC_J), RCTL_T(KC_K), LALT_T(KC_L), RSFT_T(KC_SCLN),
  KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,         KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,
                _______,      _______,      KC_TAB,       LT(2,KC_ENT), LT(1,KC_SPC), KC_BSPC,      _______,      _______
),

[_LOWER] = LAYOUT_split_3x5_4(
  KC_0,    KC_1,    KC_2,    KC_3,   KC_LPRN,     KC_RPRN, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS,
  KC_TRNS, KC_4,    KC_5,    KC_6,   KC_LBRC,     KC_RBRC, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
  KC_TRNS, KC_7,    KC_8,    KC_9,   KC_QUOT,     KC_MINS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
           _______, _______, KC_DEL, KC_ESC,      KC_NO,   KC_TRNS, _______, _______
),

[_RAISE] = LAYOUT_split_3x5_4(
  KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_LPRN,      KC_RPRN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_F5, KC_F6,   KC_F7,   KC_F8,   KC_BSLS,      KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_F9, KC_F10,  KC_F11,  KC_F12,  KC_GRV,       KC_EQL,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
         _______, _______, KC_TRNS, KC_NO,        KC_TRNS, KC_TRNS, _______, _______
),

[_ADJUST] =  LAYOUT_split_3x5_4(
  QK_BOOT, KC_NO,   KC_NO,   KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO,   KC_NO,  QK_BOOT,
  KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO,   KC_NO,  KC_NO,
  KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO,   KC_NO,  KC_NO,
           _______, _______, KC_NO, KC_NO,    KC_NO, KC_NO, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef PIMORONI_TRACKBALL_ENABLE
    switch(get_highest_layer(state)) {
        case _QWERTY:
            if (is_caps_lock_on) {
                pimoroni_trackball_set_rgbw(RGB_RED, 0x00);
            } else {
                pimoroni_trackball_set_rgbw(RGB_BLUE, 0x00);
            }
            break;
        case _LOWER:
            pimoroni_trackball_set_rgbw(RGB_PURPLE, 0x00);
            break;
        case _RAISE:
            pimoroni_trackball_set_rgbw(RGB_YELLOW, 0x00);
            break;
        case _ADJUST:
            pimoroni_trackball_set_rgbw(RGB_ORANGE, 0x00);
            break;
        default: //  for any other layers, or the default layer
            if (is_caps_lock_on) {
                pimoroni_trackball_set_rgbw(RGB_RED, 0x00);
            } else {
                pimoroni_trackball_set_rgbw(RGB_BLUE, 0x00);
            }
            break;
    }
    #endif
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void keyboard_post_init_user(void) {
    is_caps_lock_on = false;
    #ifdef PIMORONI_TRACKBALL_ENABLE
    pimoroni_trackball_set_rgbw(RGB_BLUE, 0x00);
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CAPS_LOCK:
            if (record->event.pressed) {
                if (is_caps_lock_on) {
                    is_caps_lock_on = false;
                } else {
                    is_caps_lock_on = true;
                }
            }
            break;
        default:
            break;
    }

    return true;
}
