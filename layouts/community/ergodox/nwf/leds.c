#include QMK_KEYBOARD_H
#include "nwf_common.h"

uint32_t
layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
    case L_BASE:
      ergodox_right_led_1_off();
      ergodox_right_led_2_off();
      break;
    case L_LHAN:
      ergodox_right_led_2_set(5);
      ergodox_right_led_2_on();
      ergodox_right_led_1_off();
      break;
    case L_SYMB:
      ergodox_right_led_1_set(15);
      ergodox_right_led_1_on();
      break;
    case L_XTRA:
      ergodox_right_led_1_set(30);
      ergodox_right_led_1_on();
      break;
  }
  return state;
}

void matrix_init_user(void) {
  rgblight_init();
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  rgblight_sethsv_noeeprom(0xC0, 0xFF, 0xFF);
}
