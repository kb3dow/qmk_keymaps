#include "infinity60.h"

//RR: Idea from 
// https://www.reddit.com/r/olkb/comments/8cgr26/is_there_a_better_way_taphold_q/
//RR: Then modified with stuff from -
//    https://www.keebtalk.com/t/show-me-your-favorite-qmk-hacks/2682/48?u=kb3dow
// Key must be released within this many milliseconds to be considered a tap
#define TAPPING_TERM 200

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
#define MY_DEFLYR (MY_LYR0)

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  BSp|
     * |-----------------------------------------------------------|
     * |EsCtrl|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |To1|
     * |-----------------------------------------------------------'
     * |Fn1  |Gui|LDesk|         SpaceFN       |RDesk|Gui|Fn1|Ctrl |
     * `-----------------------------------------------------------'
     */
    [MY_LYR0] = LAYOUT_60_ansi_split_bs_rshift(
      KC_ESC,  KC_1,    KC_2,      KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,      KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
      KC_TAB,  KC_Q,    KC_W,      KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,      KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, \
      ESC_CTL, KC_A,    KC_S,      KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,      KC_SCLN, KC_QUOT, KC_ENT,           \
      KC_LSFT, KC_Z,    KC_X,      KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,    KC_SLSH, KC_RSFT, MO(MY_LYR2),            \
      MO(MY_LYR1),   KC_LGUI, ALT_LDESK, LT(MY_LYR1,KC_SPC), ALT_RDESK, KC_RGUI, MO(MY_LYR1),   KC_RCTL),

    /* Layer 1: For Func, arrow keys (vi style)
     * ,-----------------------------------------------------------.
     * |TO0| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Ins|Del|
     * |-----------------------------------------------------------|
     * |     |   |BT1|MSU|BT2|   |End|PgD|PgU|Hom|Pla|Rew|FFw|Del  |
     * |-----------------------------------------------------------|
     * |      |   |MSL|MSD|MSR|   |Lft|Dwn|Up |Rgt|   |   |        |
     * |-----------------------------------------------------------|
     * | CapsLoc|   |   |   |   |   |   |MUT|VDn|VUp|   |      |   |
     * `-----------------------------------------------------------'
     * |     |Gui|Alt  |                       |     |   |   |     |
     * `-----------------------------------------------------------'
     */ 
    [MY_LYR1] = LAYOUT_60_ansi_split_bs_rshift(
      TO(MY_DEFLYR), KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS, KC_DEL,\
      _______,  _______, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2,  _______, KC_END , KC_PGDN, KC_PGUP, KC_HOME, KC_MPLY, KC_MRWD, KC_MFFD, KC_DEL,        \
      _______,  _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT,  _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, _______,                \
      KC_CAPS, _______, _______,   _______,  _______,  _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______,                \
      _______, _______, _______, _______,  _______,  _______, _______, _______),

    /* Layer 2: For extra mostly unused stuff
     * ,-----------------------------------------------------------.
     * |TO0|   |   |   |   |   |   |   |   |   |   |   |   |Brk|Psc|
     * |-----------------------------------------------------------|
     * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |
     * |-----------------------------------------------------------|
     * |      |   |   |   |   |   |   |   |   |   |   |   |        |
     * |-----------------------------------------------------------|
     * |        |   |RST|   |   |   |   |   |   |   |   |      |   |
     * `-----------------------------------------------------------'
     * |     |   |     |                       |     |   |   |     |
     * `-----------------------------------------------------------'
     */ 
    [MY_LYR2] = LAYOUT_60_ansi_split_bs_rshift(
      TO(MY_DEFLYR), _______, _______, _______, _______, _______, _______,  _______,   _______,   _______,   _______,  _______,  _______,  KC_BRK, KC_PSCREEN,\
      _______,       _______, _______, _______,  _______,  _______, _______ , _______, _______, _______, _______, _______, _______, _______,        \
      _______,       _______, _______, _______,  _______,  _______, _______, _______, _______  , _______, _______, _______, _______,                \
      _______,       _______, RESET,   _______,  _______,  _______, _______, _______, _______, _______, _______, _______, _______,                \
      _______,       _______, _______, _______,  _______,  _______, _______, _______),

};

const uint16_t fn_actions[] = {
    
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
  }
  return true;
}
