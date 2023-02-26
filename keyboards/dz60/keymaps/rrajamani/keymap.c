#include "dz60.h"

//RR: Idea from 
// https://www.reddit.com/r/olkb/comments/8cgr26/is_there_a_better_way_taphold_q/
//RR: Then modified with stuff from -
//    https://www.keebtalk.com/t/show-me-your-favorite-qmk-hacks/2682/48?u=kb3dow
// Key must be released within this many milliseconds to be considered a tap
#define TAPPING_TERM 150

// Timers for tap detection in process_record_user
uint16_t lalt_timer;
uint16_t ralt_timer;

// create some custom keycodes for your keymap
enum custom_keycodes {
  PREV_DESKTOP = SAFE_RANGE,
  NEXT_DESKTOP
};

// define some useful send strings
#define SS_PREV_DESKTOP SS_LCTRL(SS_LGUI(SS_TAP(X_LEFT)))
#define SS_NEXT_DESKTOP SS_LCTRL(SS_LGUI(SS_TAP(X_RIGHT)))

#define ESC_CTL   LCTL_T(KC_ESC)
#define ALT_LDESK (PREV_DESKTOP)
#define ALT_RDESK (NEXT_DESKTOP)
#define MY_LYR0 (0)
#define MY_LYR1 (1)
#define MY_LYR2 (2)
#define DEFLYR (MY_LYR0)

#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [MY_LYR0] = LAYOUT(
        KC_ESC, KC_1,    KC_2,      KC_3,   KC_4,    KC_5,    KC_6,      KC_7,    KC_8,      KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRAVE,
        KC_TAB,      KC_Q,    KC_W,      KC_E,   KC_R,    KC_T,    KC_Y,      KC_U,    KC_I,      KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        ESC_CTL,     KC_A,    KC_S,      KC_D,   KC_F,    KC_G,    KC_H,      KC_J,    KC_K,      KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,     XXXXXXX, KC_Z,      KC_X,   KC_C,    KC_V,    KC_B,      KC_N,    KC_M,      KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(MY_LYR2),
        MO(MY_LYR1), KC_LGUI, ALT_LDESK, XXXXXXX, LT(MY_LYR1,KC_SPC), XXXXXXX, ALT_RDESK, KC_RGUI, XXXXXXX, KC_RCTL, MO(MY_LYR1)),

    [MY_LYR1] = LAYOUT(
        TO(DEFLYR), KC_F1, KC_F2, KC_F3  ,  KC_F4  ,  KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_INS , KC_DEL,
        _______, _______, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2,  _______, KC_END , KC_PGDN, KC_PGUP, KC_HOME, KC_MPLY, KC_MRWD, KC_MFFD, KC_DEL ,
        _______, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,  _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_SCROLLLOCK, KC_PSCREEN, _______,
        KC_CAPS, _______, _______, _______,  _______,  _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, TO(MY_LYR2)  , _______, _______,
        _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______),
                                                                
/*

  RGB controls
  
  Key       ->  Description
  =========================
  RGB_TOG   ->  Toggle RGB lighting on or off
  RGB_MOD   ->  Cycle forward through modes, reverse when Shift is held
  RGB_RMOD  ->  Cycle through modes in reverse, forward when Shift is held
  RGB_HUI   ->  Increase hue
  RGB_HUD   ->  Decrease hue
  RGB_SAI   ->  Increase saturation
  RGB_SAD   ->  Decrease saturation
  RGB_VAI   ->  Increase value (brightness)
  RGB_VAD   ->  Decrease value (brightness)
  RGB_M_P   ->  Static (no animation) mode
  RGB_M_B   ->  Breathing animation mode
  RGB_M_R   ->  Rainbow animation mode
  RGB_M_SW  ->  Swirl animation mode
  RGB_M_SN  ->  Snake animation mode
  RGB_M_K   ->  "Knight Rider" animation mode
  RGB_M_X   ->  Christmas animation mode
  RGB_M_G   ->  Static gradient animation mode

*/
/*
  Mouse controls:

  Key           ->   Aliases  ->  Description
  ===================================================
  KC_MS_UP       ->   KC_MS_U  ->   Mouse Cursor Up
  KC_MS_DOWN     ->   KC_MS_D  ->   Mouse Cursor Down
  KC_MS_LEFT     ->   KC_MS_L  ->   Mouse Cursor Left
  KC_MS_RIGHT    ->   KC_MS_R  ->   Mouse Cursor Right
  KC_MS_BTN1     ->   KC_BTN1  ->   Mouse Button 1
  KC_MS_BTN2     ->   KC_BTN2  ->   Mouse Button 2
  KC_MS_BTN3     ->   KC_BTN3  ->   Mouse Button 3
  KC_MS_BTN4     ->   KC_BTN4  ->   Mouse Button 4
  KC_MS_BTN5     ->   KC_BTN5  ->   Mouse Button 5
  KC_MS_WH_UP    ->   KC_WH_U  ->   Mouse Wheel Up
  KC_MS_WH_DOWN  ->   KC_WH_D  ->   Mouse Wheel Down
  KC_MS_WH_LEFT  ->   KC_WH_L  ->   Mouse Wheel Left
  KC_MS_WH_RIGHT ->   KC_WH_R  ->   Mouse Wheel Right
  KC_MS_ACCEL0   ->   KC_ACL0  ->   Set mouse acceleration to 0
  KC_MS_ACCEL1   ->   KC_ACL1  ->   Set mouse acceleration to 1
  KC_MS_ACCEL2   ->   KC_ACL2  ->   Set mouse acceleration to 2
*/
    [MY_LYR2] = LAYOUT(                                                     
        TO(DEFLYR), M(1), M(2), M(3), M(4), M(5), M(6), M(7), M(8), M(9), M(10), M(11), M(12),   KC_BRK, KC_SCROLLLOCK,
        _______, RGB_M_P, _______, _______,  _______,  _______, _______, _______, _______, _______, BL_TOGG, BL_DEC , BL_INC , RESET,
        _______, RGB_M_B, _______, _______,  _______,  _______, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI, _______, _______, _______,
        _______, _______, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_TOG, RGB_VAD, RGB_VAI, RGB_MOD, _______, _______,
        _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______),
};


// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {
    case PREV_DESKTOP:
      if (record->event.pressed) {
        // Activate LALT
        lalt_timer = timer_read();
        SEND_STRING(SS_DOWN(X_LALT));
      } else {
        // Deactivate LALT
        SEND_STRING(SS_UP(X_LALT));
        // If the action was a tap
        if (timer_elapsed(lalt_timer) < TAPPING_TERM) {
          SEND_STRING(SS_PREV_DESKTOP);
        }
      }
      return false;
      break;

    case NEXT_DESKTOP:
      if (record->event.pressed) {
        // Activate RALT
        ralt_timer = timer_read();
        SEND_STRING(SS_DOWN(X_RALT));
      } else {
        // Deactivate RALT
        SEND_STRING(SS_UP(X_RALT));
        // If the action was a tap
        if (timer_elapsed(ralt_timer) < TAPPING_TERM) {
          SEND_STRING(SS_NEXT_DESKTOP);
        }
      }
      return false;
      break;

    default:
      break;
  }
  return true;
}


