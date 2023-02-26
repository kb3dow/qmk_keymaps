#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum custom_layers {
  _COLEMAK,
  _QWERTY,
  _LOWER,
  _RAISE,
  _MOUSECURSOR,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  MOUSECURSOR,
  ADJUST,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define KC_ KC_TRNS

#define KC_COLE COLEMAK
#define KC_LOWR LOWER
#define KC_QWER QWERTY
#define KC_RASE RAISE
#define KC_RECB DYN_REC_START1
#define KC_RECE DYN_REC_STOP
#define KC_RECP DYN_MACRO_PLAY1
#define KC_RSET RESET

#define KC_SCAP SFT_T(KC_CAPS)            // Tap for Caps Lock, hold for Shift
#define KC_CTLE CTL_T(KC_ESC)             // Tap for Escape, hold for Control
#define KC_HTAB ALL_T(KC_TAB)             // Tap for Tab, hold for Hyper (Super+Ctrl+Alt+Shift)
#define KC_SBSP SFT_T(KC_BSPC)            // Tap for Backspace, hold for Shift
#define KC_SENT KC_SFTENT                 // Tap for Enter, hold for Shift
#define KC_TGMC TG(_MOUSECURSOR)          // Toggle MOUSECURSOR layer
#define KC_SPMC LT(_MOUSECURSOR, KC_SPC)  // Tap for Space, hold for MOUSECURSOR layer
#define KC_LSBR MT(MOD_LSFT, KC_LBRC)     // Tap for Left Brace, hold for Shift
#define KC_RSBR MT(MOD_RSFT, KC_RBRC)     // Tap for Right Brace, hold for Shift

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     MEH , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,TGMC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     HTAB, Q  , W  , E  , R  , T  ,                Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CTLE, A  , S  , D  , F  , G  ,                H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SCAP, Z  , X  , C  , V  , B  ,LAPO,     RAPC, N  , M  ,COMM,DOT ,SLSH,SENT,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,SPMC,LOWR,         RASE,SPMC,RGUI
  //                  `----+----+----'        `----+----+----'
  ),

  [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
     MEH , 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,TGMC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     HTAB, Q  , W  , F  , P  , G  ,                J  , L  , U  , Y  ,SCLN,BSPC,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     CTLE, A  , R  , S  , T  , D  ,                H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     SBSP, Z  , X  , C  , V  , B  ,LALT,     RALT, K  , M  ,COMM,DOT ,SLSH,SENT,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI,LOWR,SPMC,         SPMC,RASE,RGUI
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TILD,EXLM, AT ,HASH,DLR ,PERC,               CIRC,AMPR,ASTR,LPRN,RPRN,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GRV , F1 , F2 , F3 , F4 , F5 ,                F6 ,UNDS,PLUS,LCBR,RCBR,PIPE,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         , F7 , F8 , F9 ,F10 ,F11 ,    ,         ,F12 ,MS_L,MS_D,MS_U,MS_R,BTN1,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TILD, 1  , 2  , 3  , 4  , 5  ,                6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     GRV , F1 , F2 , F3 , F4 , F5 ,                F6 ,MINS,EQL ,LBRC,RBRC,BSLS,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         , F7 , F8 , F9 ,F10 ,F11 ,    ,         ,F12 ,LEFT,DOWN, UP ,RGHT,BTN2,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_MOUSECURSOR] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 ,                F6 , F7 , F8 , F9 ,F10 ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,BTN1,MS_U,BTN2,    ,WH_U,               HOME,PGDN,PGUP,END ,F11 ,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,MS_L,MS_D,MS_R,    ,WH_D,               LEFT,DOWN, UP ,RGHT,F12 ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,LBRC,     RBRC,    ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  ),

  [_ADJUST] = LAYOUT_kc(
  //,----+----+----+----+----+----.              ,----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,                   ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,RSET,    ,    ,    ,    ,                   ,    ,    ,    ,RSET,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,                   ,QWER,COLE,    ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,RECB,RECE,RECP,CAPS,
  //`----+----+----+----+----+----+----/    \----+----+----+----+----+----+----'
                           ,    ,    ,             ,    ,
  //                  `----+----+----'        `----+----+----'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
 }
