#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "nwf_common.h"

enum tap_dances {
  TD_F1, TD_F2, TD_F3, TD_F4, TD_F5,
};

enum nwf_keycodes {
  LSHIFT0 = SAFE_RANGE,
  LSHIFT1,
  CONSUMER_EJECT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | L_LHAN |   1  |   2  |   3  |   4  |   5  |   6  |           |   5  |   6  |   7  |   8  |   9  |   0  |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           | PgUp |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|Home  |           |      |------+------+------+------+------+--------|
 * |ESC/LCtl|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | ; :  | Enter  |
 * |--------+------+------+------+------+------|      |           | PgDn |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |End   |           |      |   N  |   M  |  , < |  . > | / ?  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LS0  | ` ~  |      | Left | Right|                                       |  Up  | Down | App  | ' "  | Del  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       | RCtl |Insert|
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | LAlt |       | RAlt |      |      |
 *                                 |BackSp|Space |------|       |------|Space |BackSp|
 *                                 |      |      | LGUI |       | LS1  |      |      |
 *                                 `--------------------'       `--------------------'
 */
[L_BASE] = LAYOUT_ergodox(
 // LHS
 TG(L_LHAN)   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     , KC_6    ,
 KC_TAB       , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     , KC_HOME ,
 CTL_T(KC_ESC), KC_A     , KC_S     , KC_D     , KC_F     , KC_G     , /* gap */
 KC_LSFT      , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_END  ,
   LSHIFT0    , KC_GRV   , KC_NO    , KC_LEFT  , KC_RGHT  , /* gap            */

                                                            KC_NO    , KC_NO   ,
                                                                       KC_LALT ,
                                                 KC_BSPC  , KC_SPC   , KC_LGUI ,
 // RHS
 KC_5         , KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_NO    ,
 KC_PGUP      , KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_BSLS  ,
 /* gap      */ KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_ENT   ,
 KC_PGDN      , KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
 /* gap                 */ KC_UP    , KC_DOWN  , KC_APP   , KC_QUOT  , KC_DEL  ,

 KC_RCTL      , KC_INS   ,
 KC_RALT      ,
 LSHIFT1      , KC_SPC   , KC_BSPC
),

/* Keymap 2: Symbol Layer (either LS0 or LS1)
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |F1/F11|F2/F12|F3/F13|F4/F14|F5/F15|  F6  |           |F5/F15|  F6  |  F7  |  F8  |  F9  |  F10 | RESET  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |  !   |  @   |  #   |  $   |  %   |      |           | Home |  ^   |  &   |  *   |  (   |  )   |        |
 * |---------+------+------+------+------+------| PgUp |           |      |------+------+------+------+------+--------|
 * | xxxxxxx |  `   |  =   |  [   |  ]   |  -   |------|           |------|      |  Up  |      |  \   |  '   | xxxxxx |
 * |---------+------+------+------+------+------|      |           | End  |------+------+------+------+------+--------|
 * | xxxxxxx |  ~   |  +   |  {   |  }   |  _   | PgDn |           |      | Left | Down | Right|  |   |  "   | xxxxxx |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | xxxxx |      |      |  (   |  )   |                                       | Cut  | Copy | Paste|PrnScr| EJECT|
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Insert|      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Web  |      | xxxx |       | xxxx |      |      |
 *                                 | Back |xxxxx |------|       |------|xxxxx |      |
 *                                 |      |      | xxxx |       | xxxx |      |      |
 *                                 `--------------------'       `--------------------'
 */

[L_SYMB] = LAYOUT_ergodox(
 KC_NO        , TD(TD_F1), TD(TD_F2), TD(TD_F3), TD(TD_F4), TD(TD_F5), KC_F6   ,
 KC_NO        , KC_EXLM  , KC_AT    , KC_HASH  , KC_DLR   , KC_PERC  , KC_PGUP ,
 KC_TRNS      , KC_GRV   , KC_EQL   , KC_LBRC  , KC_RBRC  , KC_MINS  , /* gap */
 KC_TRNS      , KC_TILD  , KC_PLUS  , KC_LCBR  , KC_RCBR  , KC_UNDS  , KC_PGDN ,
   KC_TRNS    , KC_NO    , KC_NO    , KC_LPRN  , KC_RPRN  , /* gap            */

                                                            KC_INS   , KC_NO   ,
                                                                       KC_TRNS ,
                                                 KC_WBAK  , KC_TRNS  , KC_TRNS ,
 // RHS
 TD(TD_F5)    , KC_F6    , KC_F7    , KC_F8    , KC_F9    ,  KC_F10  , RESET    ,
 KC_HOME      , KC_CIRC  , KC_AMPR  , KC_ASTR  , KC_LPRN  ,  KC_RPRN , KC_NO    ,
 /* gap      */ KC_NO    , KC_UP    , KC_NO    , KC_BSLS  ,  KC_QUOT , KC_TRNS  ,
 KC_END       , KC_LEFT  , KC_DOWN  , KC_RIGHT , KC_PIPE  ,  KC_DQUO , KC_TRNS  ,
 /* gap                 */ KC_CUT   , KC_COPY  , KC_PASTE ,  KC_PSCR , CONSUMER_EJECT  ,

 KC_NO        , KC_NO    ,
 KC_TRNS      ,
 KC_TRNS      , KC_TRNS  , KC_NO
),

/* Keymap 1: left-hand accompaniment to right hand on mouse
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | L_LHAN |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Tab    |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |ESC/LCtl| Home | PgUp |  Up  | PgDn |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift | End  | Left | Down | Right|      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LS0  |      | Cut  | Copy | Paste|                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Insert| Del  |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | LAlt |       |      |      |      |
 *                                 |BackSp|Space |------|       |------|      |      |
 *                                 |      |      | LGUI |       | LS1  |      |      |
 *                                 `--------------------'       `--------------------'
 */

[L_LHAN] = LAYOUT_ergodox(
 TG(L_LHAN)   , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,
 KC_TAB       , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,
 CTL_T(KC_ESC), KC_HOME  , KC_PGUP  , KC_UP    , KC_PGDN  , KC_NO    , /* gap */
 KC_LSFT      , KC_END   , KC_LEFT  , KC_DOWN  , KC_RIGHT , KC_NO    , KC_NO   ,
   LSHIFT0    , KC_NO    , KC_CUT   , KC_COPY  , KC_PASTE , /* gap            */

                                                            KC_INS   , KC_DEL  ,
                                                                       KC_LALT ,
                                                 KC_BSPC  , KC_SPC   , KC_LGUI ,
 // RHS
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 /* gap      */ KC_NO    , KC_UP    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 /* gap                 */ KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,

 KC_NO        , KC_NO    ,
 KC_NO        ,
 LSHIFT1      , KC_NO    , KC_NO
),

/* Keymap 3: Extra Layer (both LS0 and LS1)
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | xxxxx |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       | xxxx |      |      |
 *                                 `--------------------'       `--------------------'
 */

[L_XTRA] = LAYOUT_ergodox(
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , /* gap */
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,
   KC_TRNS    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , /* gap            */

                                                            KC_NO    , KC_NO   ,
                                                                       KC_NO   ,
                                                 KC_NO    , KC_NO    , KC_NO   ,
 // RHS
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 /* gap      */ KC_NO    , KC_UP    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 /* gap                 */ KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,

 KC_NO        , KC_NO    ,
 KC_NO        ,
 KC_TRNS      , KC_NO    , KC_NO
),

};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_F1] = ACTION_TAP_DANCE_DOUBLE(KC_F1, KC_F11),
  [TD_F2] = ACTION_TAP_DANCE_DOUBLE(KC_F2, KC_F12),
  [TD_F3] = ACTION_TAP_DANCE_DOUBLE(KC_F3, KC_F13),
  [TD_F4] = ACTION_TAP_DANCE_DOUBLE(KC_F4, KC_F14),
  [TD_F5] = ACTION_TAP_DANCE_DOUBLE(KC_F5, KC_F15),
};


static uint8_t nwf_flags;
enum nwf_flags_e {
  NWF_FL_LS0 = 0x01,
  NWF_FL_LS1 = 0x02,
};

static void
nwf_flags_to_layer(void) {
  switch(nwf_flags & (NWF_FL_LS0 | NWF_FL_LS1)) {
    case (NWF_FL_LS0 | NWF_FL_LS1) :
      // both down, bring both layers online
      layer_or(((1 << L_SYMB) | (1 << L_XTRA)));
      break;
    case 0 :
      // neither down, bring both layers offline
      layer_and(~((1 << L_SYMB) | (1 << L_XTRA)));
      break;
    case NWF_FL_LS0 :
    case NWF_FL_LS1 :
      // just one down, bring just symbol layer online
      layer_and(~(1 << L_XTRA));
      layer_or(1 << L_SYMB);
      break;
  }
}

bool
process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case LSHIFT0 :
     nwf_flags = (nwf_flags & ~NWF_FL_LS0) | (record->event.pressed ? NWF_FL_LS0 : 0);
     nwf_flags_to_layer();
     return false;
    case LSHIFT1 :
     nwf_flags = (nwf_flags & ~NWF_FL_LS1) | (record->event.pressed ? NWF_FL_LS1 : 0);
     nwf_flags_to_layer();
     return false;
    case CONSUMER_EJECT:
     if (record->event.pressed) {
       host_consumer_send(0xB8);
     } else {
       host_consumer_send(0);
     }
     return false;
    default:
      return true;
  }
}

#if 0
/* Blank keyboard template
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      |      |      |      |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

[L_] = LAYOUT_ergodox(
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , /* gap */
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,
   KC_NO      , KC_NO    , KC_NO    , KC_NO    , KC_NO    , /* gap            */

                                                            KC_NO    , KC_NO   ,
                                                                       KC_NO   ,
                                                 KC_NO    , KC_NO    , KC_NO   ,
 // RHS
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 /* gap      */ KC_NO    , KC_UP    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 KC_NO        , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
 /* gap                 */ KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO   ,

 KC_NO        , KC_NO    ,
 KC_NO        ,
 KC_NO        , KC_NO    , KC_NO
),

#endif
