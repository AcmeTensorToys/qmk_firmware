#include QMK_KEYBOARD_H
#include "version.h"
#include "raw_hid.h"

void
raw_hid_receive(uint8_t *data, uint8_t length) {
  switch(data[0]) {
    case 'V' :               // Version
      data[1] = 0x00;
      data[2] = 0xFF;
      data[3] = git_rev_bytes[0];
      data[4] = git_rev_bytes[1];
      data[5] = git_rev_bytes[2];
      data[6] = git_rev_bytes[3];
      data[7] = git_rev_bytes[4];
      break;
    case 'U' :               // Underglow
      switch(data[1]) {
        // 0x00
        case 0x01 :             // Single LED
          rgblight_sethsv_at(
                data[3],   // hue in 360/256 ~~ 1.4 degree increments
                data[4],   // saturation
                data[5],   // brightness
                data[2]);  // index
          data[6] = 0;
          data[7] = 0;
          break;
        // 0x02 -- 0xEF
        case 0xF0 :            // Whole underglow off
          rgblight_disable_noeeprom();
          data[2] = 0;
          data[3] = 0;
          data[4] = 0;
          data[5] = 0;
          data[6] = 0;
          data[7] = 0;
          break;
        case 0xF1 :            // Whole underglow on
          rgblight_enable_noeeprom();
          data[2] = 0;
          data[3] = 0;
          data[4] = 0;
          data[5] = 0;
          data[6] = 0;
          data[7] = 0;
          break;
        // 0xF2 -- 0xFD
        case 0xFE :
          rgblight_sethsv_noeeprom(
                data[2],   // hue in 360/256 ~~ 1.4 degree increments
                data[3],   // saturation
                data[4]);  // brightness
          data[5] = 0;
          data[6] = 0;
          data[7] = 0;
          break;
		// 0xFF
      }
      break;
    default :
        data[1] = data[0];
        data[0] = '?';
        data[2] = 0;
        data[3] = 0;
        data[4] = 0;
        data[5] = 0;
        data[6] = 0;
        data[7] = 0;
  }
  raw_hid_send( data, length );
}
