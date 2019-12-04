#include "ergodox_ez.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "purplerage_common.h"

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  TMSLCLG, // Toggle Magic Swap Left Ctrl and Left Gui
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 0
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |   =     |   1  |   2  |   3  |   4  |   5  | Left |           |Right |    6 |    7 |    8 |    9 |    0 | BackSp |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |  Tab    |   Q  |   W  |   E  |   R  |   T  |      |           | TG1  |    Y |    U |    I |    O |    P | BckSla |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  BCKSP  |   A  |   S  |   D  |   F  |   G  |------|           |------|    H |    J |    K |    L | LT2/;| RGUI/' |
 * |---------+------+------+------+------+------| LGUI |           | -    |------+------+------+------+------+--------|
 * |  L SHFT |LCTL/Z|   X  |   C  |   V  |   B  |      |           |      |    N |    M |    , |    . |RCTL//| R SHFT |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LT1/` |  '   |ALT/SH| Left | Right|                                       |   Up | Down |   [  |   ]  | MO1  |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |ALT/AP| LGUI |       | L ALT|RC/ESC|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | Home |       | PgUp |      |      |
 *                                 |Space |BackSp|------|       |------| Tab  |Enter |
 *                                 |      |      | End  |       | PgDn |      |      |
 *                                 `--------------------'       `--------------------'
 */

[L_BASE] = LAYOUT_ergodox(
 KC_EQUAL     , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     , KC_LEFT ,
 KC_TAB       , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     , KC_NO   ,
 KC_BSPACE    , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     , /* gap */
 KC_LSHIFT    , LCTL_T(KC_Z), KC_X   , KC_C     , KC_V     , KC_B     , KC_LGUI ,
  LT(L_1,KC_GRAVE), KC_QUOTE, LALT(KC_LSHIFT) ,KC_LEFT, KC_RIGHT, /* gap            */

                                                ALT_T(KC_APPLICATION), KC_LGUI ,
                                                                       KC_HOME ,
                                                 KC_SPACE , KC_BSPACE, KC_END  ,

 // RHS

 KC_RIGHT     , KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSPACE,
 TG(L_1)      , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_BSLASH,
 /* gap      */ KC_H     , KC_J     , KC_K     , KC_L     ,LT(L_2,KC_SCOLON),RGUI_T(KC_QUOTE),
 KC_MINUS     , KC_N     , KC_M     , KC_COMMA , KC_DOT   ,RCTL_T(KC_SLASH),KC_RSHIFT,
 /* gap                 */ KC_UP    , KC_DOWN  , KC_LBRACKET,KC_RBRACKET,MO(L_1),

 KC_LALT      , RCTL_T(KC_ESCAPE),
 KC_PGUP,
 KC_PGDOWN    , KC_TAB   ,KC_ENTER
),

/* Layer 1
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | Esc     |  F1  |  F2  |  F3  |  F4  |  F5  | xxxx |           | LCLG |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | xxxx    |  !   |  @   |  {   |  }   |  |   | xxxx |           | xxxx | Up   |  7   |  8   |  9   |  *   |  F12   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | xxxx    |  #   |  $   |  (   |  )   |  `   |------|           |------| Down |  4   |  5   |  6   | xxxx | xxxx   |
 * |---------+------+------+------+------+------| xxxx |           | xxxx |------+------+------+------+------+--------|
 * | xxxx    |  %   |  ^   |  [   |  ]   |  ~   |      |           |      |  &   |  1   |  2   |  3   |  \   | xxxx   |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | xxxx  | xxxx | xxxx | xxxx | xxxx |                                       | xxxx |  .   |  0   |  =   | xxxx |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | RGBM | xxxx |       | RGBT | RGBS |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | RGB  | RGB  | xxxx |       | xxxx | RGB  | RGB  |
 *                                 | VAD  | VAI  |------|       |------| HUD  | HUI  |
 *                                 |      |      | xxxx |       |RESET |      |      |
 *                                 `--------------------'       `--------------------'
 */

[L_1] = LAYOUT_ergodox(
 KC_ESCAPE    , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_TRNS,
 KC_TRNS      , KC_EXLM  , KC_AT    , KC_LCBR  , KC_RCBR  , KC_PIPE  , KC_TRNS,
 KC_TRNS      , KC_HASH  , KC_DLR   , KC_LPRN  , KC_RPRN  , KC_GRAVE , /* gap */
 KC_TRNS      , KC_PERC  , KC_CIRC  , KC_LBRACKET,KC_RBRACKET,KC_TILD, KC_TRNS,
   KC_TRNS    , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , /* gap            */

                                                            RGB_MOD  , KC_TRNS,
                                                                       KC_TRNS,
                                                 RGB_VAD  , RGB_VAI  , KC_TRNS,
 // RHS
 TMSLCLG     , KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
 KC_TRNS     , KC_UP    , KC_7     , KC_8     , KC_9     , KC_ASTR  , KC_F12   ,
 /* gap      */ KC_DOWN , KC_4     , KC_5     , KC_6     , KC_TRNS  , KC_TRNS ,
 KC_TRNS     , KC_AMPR  , KC_1     , KC_2     , KC_3     , KC_BSLASH, KC_TRNS ,
 /* gap                 */ KC_TRNS , KC_DOT   , KC_0     , KC_EQUAL , KC_TRNS,

 RGB_TOG     , RGB_SLD  ,
 KC_TRNS     ,
 RESET       , RGB_HUD  , RGB_HUI
),

/* Layer 2
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * | xxxx    | xxxx | xxxx | xxxx | xxxx | xxxx | xxxx |           | xxxx | xxxx | xxxx | xxxx | xxxx | xxxx | xxxx   |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | xxxx    | xxxx | xxxx | M Up | xxxx | xxxx | xxxx |           | xxxx | xxxx | xxxx | xxxx | xxxx | xxxx | xxxx   |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | xxxx    | xxxx | M Lt | M Dn | M Rt | xxxx |------|           |------| xxxx | xxxx | xxxx | xxxx | xxxx | PLAY   |
 * |---------+------+------+------+------+------| xxxx |           | xxxx |------+------+------+------+------+--------|
 * | xxxx    | xxxx | xxxx | xxxx | xxxx | xxxx |      |           |      | xxxx | xxxx | PREV | NEXT | xxxx | xxxx   |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | xxxx  | xxxx | xxxx | M B1 | M B2 |                                       | V Up | V Dn | V Mt | xxxx | xxxx |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | xxxx | xxxx |       | xxxx | xxxx |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | xxxx | xxxx | xxxx |       | xxxx | xxxx | WWW  |
 *                                 |      |      |------|       |------|      | BACK |
 *                                 |      |      | xxxx |       | xxxx |      |      |
 *                                 `--------------------'       `--------------------'
 */

[L_2] = LAYOUT_ergodox(
 KC_TRNS      , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS ,
 KC_TRNS      , KC_TRNS  , KC_TRNS  , KC_MS_UP , KC_TRNS  , KC_TRNS  , KC_TRNS ,
 KC_TRNS      , KC_TRNS  ,KC_MS_LEFT,KC_MS_DOWN,KC_MS_RIGHT, KC_TRNS , /* gap */
 KC_TRNS      , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS ,
   KC_TRNS    , KC_TRNS  , KC_TRNS  ,KC_MS_BTN1,KC_MS_BTN2, /* gap            */

                                                            KC_TRNS  , KC_TRNS ,
                                                                       KC_TRNS ,
                                                 KC_TRNS  , KC_TRNS  , KC_TRNS ,
 // RHS
 KC_TRNS      , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
 KC_TRNS      , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
 /* gap      */ KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_MEDIA_PLAY_PAUSE,
 KC_TRNS      , KC_TRNS  , KC_TRNS  , KC_MEDIA_PREV_TRACK    , KC_MEDIA_NEXT_TRACK    , KC_TRNS  , KC_TRNS  ,
 /* gap                 */ KC_AUDIO_VOL_UP    , KC_AUDIO_VOL_DOWN    , KC_AUDIO_MUTE    , KC_TRNS  , KC_TRNS ,

 KC_TRNS      , KC_TRNS  ,
 KC_TRNS      ,
 KC_TRNS      , KC_TRNS  , KC_WWW_BACK
),

};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case TMSLCLG:
      if (record->event.pressed) {
        keymap_config.swap_lctl_lgui = !keymap_config.swap_lctl_lgui;
      }
      return false;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }
    return state;

};
