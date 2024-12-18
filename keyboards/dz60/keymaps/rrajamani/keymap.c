#include "dz60.h"

//RR: Idea from 
// https://www.reddit.com/r/olkb/comments/8cgr26/is_there_a_better_way_taphold_q/
//RR: Then modified with stuff from -
//    https://www.keebtalk.com/t/show-me-your-favorite-qmk-hacks/2682/48?u=kb3dow

// Timers for tap detection in process_record_user
uint16_t lalt_timer;
uint16_t ralt_timer;

// create some custom keycodes for your keymap
enum custom_keycodes {
  L_RESET = SAFE_RANGE,
  PREV_DESKTOP,
  NEXT_DESKTOP
};

// define some useful send strings
//TBD #define SS_PREV_DESKTOP SS_LCTRL(SS_LGUI(SS_TAP(X_LEFT)))
//TBD #define SS_NEXT_DESKTOP SS_LCTRL(SS_LGUI(SS_TAP(X_RIGHT)))

#define CTL_ESC LCTL_T(KC_ESC)
#define ALT_LDESK (PREV_DESKTOP)
#define ALT_RDESK (NEXT_DESKTOP)
#define LYR0 (0)
#define LYR1 (1)
#define LYR2 (2)
#define DFLYR (LYR0)
#define MS_BTN1 (KC_MS_BTN1)
#define MS_UP (KC_MS_UP)
#define MS_BTN2 (KC_MS_BTN2)
#define MS_LEFT (KC_MS_LEFT)
#define MS_DOWN (KC_MS_DOWN)
#define MS_RIGHT (KC_MS_RIGHT)
#define SCRL_LCK (KC_SCROLL_LOCK)


#define _______ KC_TRNS
#define XXXXXXX KC_NO

/* Ctrl-Command controls
 * CG_SWAP: Swap control with GUI on both sides
 * CG_NORM: UnSwap control with GUI
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [LYR0] = LAYOUT(
        KC_GRAVE, KC_1,    KC_2,      KC_3,   KC_4,    KC_5,    KC_6,      KC_7,    KC_8,      KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_ESC, 
        KC_TAB,   KC_Q,    KC_W,      KC_E,   KC_R,    KC_T,    KC_Y,      KC_U,    KC_I,      KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        CTL_ESC,  KC_A,    KC_S,      KC_D,   KC_F,    KC_G,    KC_H,      KC_J,    KC_K,      KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,  XXXXXXX, KC_Z,      KC_X,   KC_C,    KC_V,    KC_B,      KC_N,    KC_M,      KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(LYR2),
        MO(LYR1), KC_LGUI, ALT_LDESK, XXXXXXX, LT(LYR1,KC_SPC), XXXXXXX, ALT_RDESK, KC_RGUI, XXXXXXX, KC_RCTL, MO(LYR1)
	),

    [LYR1] = LAYOUT(
        TO(DFLYR), KC_F1, KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11 ,  KC_F12 , KC_INS , KC_DEL,
        _______, _______, MS_BTN1, MS_UP,   MS_BTN2,  _______, KC_END , KC_PGDN, KC_PGUP, KC_HOME, KC_MPLY,  KC_MRWD,  KC_MFFD, KC_DEL ,
        CG_NORM, _______, MS_LEFT, MS_DOWN, MS_RIGHT, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, SCRL_LCK, KC_PSCR,  _______,
        KC_CAPS, _______, _______, _______, _______,  _______, KC_SPC,  _______, KC_MUTE, KC_VOLD, KC_VOLU,  TO(LYR2), _______, _______,
        _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______
	),
                                                                
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
    [LYR2] = LAYOUT(                                                     
        TO(DFLYR), TO(1), TO(2), TO(3), TO(4), TO(5), TO(6), TO(7), TO(8), TO(9), TO(10), TO(11), TO(12),   KC_BRK, SCRL_LCK,
        _______, RGB_M_P, _______, _______,  _______,  _______, _______, _______, _______, _______, BL_TOGG, BL_DEC , BL_INC , QK_BOOT,
        CG_SWAP, RGB_M_B, _______, _______,  _______,  _______, RGB_HUD, RGB_SAD, RGB_SAI, RGB_HUI, _______, _______, _______,
        _______, _______, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_TOG, RGB_VAD, RGB_VAI, RGB_MOD, _______, _______,
        _______, _______, _______, _______,  _______,  _______, _______, _______, _______, _______, _______),
};


// Runs just one time when the keyboard initializes.
//void matrix_init_user(void) {
//};

// Runs constantly in the background, in a loop.
//void matrix_scan_user(void) {
//    LEADER_DICTIONARY() {
//        leading      = false;
//        leader_found = false;
//        SEQ_ONE_KEY(L_RESET) {
//            leader_found = true;
//            reset_keyboard();
//        }
//        else
//            SEQ_ONE_KEY(KC_DEL) {
//            leader_found = true;
//            layer_clear();
//        }
//        else
//            SEQ_ONE_KEY(LOWER) {
//            leader_found = true;
//            layer_on(_LOWER);
//        }
//        else
//            SEQ_ONE_KEY(RAISE) {
//            leader_found = true;
//            layer_on(_RAISE);
//        }
//        leader_end();
//    }
//};

/*
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
        //TBD if (timer_elapsed(lalt_timer) < TAPPING_TERM) {
          //TBD SEND_STRING(SS_PREV_DESKTOP);
        //TBD }
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
        //TBD if (timer_elapsed(ralt_timer) < TAPPING_TERM) {
          //TBD SEND_STRING(SS_NEXT_DESKTOP);
        //TBD }
      }
      return false;
      break;

    default:
      break;
  }
  return true;
}
*/

