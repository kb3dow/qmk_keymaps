#include QMK_KEYBOARD_H

// Combo idea from https://github.com/qmk/qmk_firmware/blob/master/docs/feature_combo.md
enum combo_events {
  EM_EMAIL,        // Enter email address
  BSPC_LSFT_CLEAR, // Delete whole line
  JK_ENTER,        // jk does enter
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM email_combo[] = {KC_E, KC_M, COMBO_END};
const uint16_t PROGMEM clear_line_combo[] = {KC_BSPC, KC_LSFT, COMBO_END};
const uint16_t PROGMEM jk_enter_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[] = {
  [EM_EMAIL] = COMBO_ACTION(email_combo),
  [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
  [JK_ENTER] = COMBO_ACTION(jk_enter_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case EM_EMAIL:
      if (pressed) {
        SEND_STRING("r.rajamani@gmail.com");
      }
      break;
    case BSPC_LSFT_CLEAR:
      if (pressed) {
        tap_code16(KC_END);
        tap_code16(S(KC_HOME));
        tap_code16(KC_BSPC);
      }
      break;
    case JK_ENTER:
      if (pressed) {
        tap_code16(KC_ENT);
      }
      break;
  }
}

