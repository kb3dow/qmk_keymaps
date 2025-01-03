/* Copyright 2023 Rajarajan Rajamani
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H


enum planck_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _FNLYR,
    _ADJUST,
};

enum planck_keycodes {
    L_RESET = SAFE_RANGE,   // L_RESET NOT USED for now
    BSPCDEL,
    SHFT_CAPS
};

/*
// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_SFT_CAP] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
};
*/

#ifdef AUDIO_ENABLE
float planck_sound[][2] = SONG(PLANCK_SOUND);
#endif

#define LOWER MO(_LOWER)    // LOWER LAYER
#define RAISE MO(_RAISE)    // RAISE LAYER
#define FNLYR MO(_FNLYR)    // FUNCTION LAYER

#define SFTENT KC_SFTENT
#define KC_BSDEL BSPCDEL
#define CTL_ESC LCTL_T(KC_ESC)
#define SPC_LWR LT(_LOWER, KC_SPC)
#define SPC_RAS LT(_RAISE, KC_SPC)

/* Ctrl-Command controls
 * CG_SWAP: Swap control with GUI on both sides
 * CG_NORM: UnSwap control with GUI
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base
     * ,-----------------------------------------------------------------------------------.
     * |  Tab |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |<-/-> |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |EscCTL|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;/: | '\"  |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Fn   | GUI  |  Alt |  -/_ | Lower/Space | Raise/Space |  =/+ |  Alt | GUI  |  Fn  |
     * `-----------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSDEL,
	CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
	FNLYR,   KC_LGUI, KC_LALT, KC_MINS, _______, SPC_LWR, _______, SPC_RAS, KC_EQL,  KC_RALT, KC_RGUI, FNLYR /*KC_LEAD,*/
    ),

    [_FNLYR] = LAYOUT_planck_grid(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______
    ),
    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  Bsp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   _  |   +  |   {  |   }  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |      | Left | Down |  Up  | Right|      |  \"  |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Caps |      |      |      |      |      | Home |Pg Dn |Pg Up | End  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),


    /* Adjust (Lower + Raise)
     * ,-----------------------------------------------------------------------------------.
     * |      |      | Debug| Clear|  RGB | HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-| Reset|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |CGSWAP|      |      |Aud on|Audoff| Swap | Norm |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |Mus on|Musoff| NKRO | 6KRO |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |CGNORM|      |      |      |      |      |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(
        _______, QK_BOOT, DB_TOGG, EE_CLR,  RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, QK_BOOT,
        CG_SWAP, XXXXXXX, XXXXXXX, AU_ON,   AU_OFF,  AG_SWAP, AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, MU_ON,   MU_OFF,  NK_ON,   NK_OFF,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, CG_NORM, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, 0, 0, 0});

const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_RED});

const rgblight_segment_t PROGMEM raise_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_GREEN});

const rgblight_segment_t PROGMEM adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_BLUE});

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 5, HSV_WHITE});

// Later layers take precedence.
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_layer,
    lower_layer,
    raise_layer,
    adjust_layer,
    capslock_layer
);

bool audio_disable = false;

void keyboard_pre_init_user(void) {
    // If the audio is off during hardware init,
    // it causes problem when the audio is turn on later.
    // The workaround is to always set the audio on during hardware init,
    // then toggle audio back to the setting.
#ifdef AUDIO_ENABLE
    if (!is_audio_on()) {
        audio_disable = true;
        audio_on();
    }
#endif
}

void matrix_init_user(void) {
    // To fix a audio related problem. See comments in keyboard_pre_init_user().
#ifdef AUDIO_ENABLE
    if (audio_disable) {
        audio_off();
    }
#endif
}

void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
    rgblight_set_layer_state(0, true);
}

// Example of code using leader - use KC_LEAD in keymap above
// void leader_end_user(void) {
//    if (leader_sequence_one_key(KC_F)) {
//        // Leader, f => Types the below string
//        SEND_STRING("QMK is awesome.");
//    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
//        // Leader, d, d => Ctrl+A, Ctrl+C
//        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
//    } else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
//        // Leader, d, d, s => Types the below string
//        SEND_STRING("https://start.duckduckgo.com\n");
//    } else if (leader_sequence_two_keys(KC_A, KC_S)) {
//        // Leader, a, s => GUI+S
//        tap_code16(LGUI(KC_S));
//    }
//  // Call leader_end() ; // if needed
//}
//
//void leader_end(void) {
//    // Plays sound on if leader sequence found.
//    if (leader_found) {
//#ifdef AUDIO_ENABLE
//        PLAY_SONG(planck_sound);
//#endif
//    }
//}

bool led_update_user(led_t led_state) {
    // Turn on RBG for capslock.
    rgblight_set_layer_state(4, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Set RBG layer according to active keymap layer.
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 1) && layer_state_cmp(state, 2));
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool bsdel_mods = false;
  switch(keycode) {
    //Do a DEL if shift BSP
    //Ref: https://www.reddit.com/r/olkb/comments/byds0h/shift_space_and_shift_backspace/
    case BSPCDEL:
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSFT)) {
          unregister_code(KC_LSFT);
          register_code(KC_DEL);
          bsdel_mods = true;
        } else {
          register_code(KC_BSPC);
        }
      } else {
        if (bsdel_mods) {
          unregister_code(KC_DEL);
          register_code(KC_LSFT);
          bsdel_mods = false;
        } else {
          unregister_code(KC_BSPC);
        }
      }
      return false;
      break;
  }
  return true;
}
