#include QMK_KEYBOARD_H

#include "version.h"
#include "debug.h"
#include "action_layer.h"

// TODO: Check out one-shot keys
// TODO: Muniter suggests considering doing something like OSM for Shift, for example

LEADER_EXTERNS();

enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  VRSN = EZ_SAFE_RANGE,
#else
  VRSN = SAFE_RANGE,
#endif
  RGB_SLD
};

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 200

#define PREVENT_STUCK_MODIFIERS

enum layers {
  BASE,
  SYMB,
  MDIA,
  WORK,
};

// MACROS
#define CTLSHFT 1  // M-CS
#define MAC_CA 2
#define MAC_CSA 3
#define WORKSPACE_LEFT 4
#define WORKSPACE_DOWN 5
#define WORKSPACE_UP 6
#define WORKSPACE_RGHT 7

// TIMERS
#define KEY_TAP_FAST 85
#define KEY_TAP_SLOW 200

#define M_CS  ( MOD_LSFT | MOD_LCTL )
#define M_LS  ( MOD_LSFT | MOD_LGUI )
/* #define M_CA  ( MOD_LSFT | MOD_LALT ) */
/* #define M_CSA ( MOD_LSFT | MOD_LALT | MOD_LCTL ) */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Del    |   Q  | W/L3 |   E  |   R  |   T  |Insrt |           | LDR  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Grv    |   A  |   S  |   D  | F/Alt|   G  |------|           |------|   H  | J/Alt|   K  |   L  |; / L2|   '    |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift | Ctrl |x:M_CS|   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//LGUI| ~L1    |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  Z   |  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | RShift |
 *   `----------------------------------'                                       `------------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 * Using:
 *  x:M_CS -> M(CTLSHFT): {tap: x, hold: CTRL + SHFT}
 *
 * Not using:
 *  M_CA -> {tap: c, hold: CTRL + ALT}
 *  M_CSA -> {tap: v, hold: CTRL + SHIFT + ALT}
 */

// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,           KC_3,           KC_4,            KC_5,   KC_LEFT,
        KC_DELT,        KC_Q,         LT(WORK, KC_W), KC_E,           KC_R,            KC_T,   KC_INSERT,
        KC_GRV,         KC_A,         KC_S,           KC_D,           ALT_T(KC_F),     KC_G,
        KC_LSFT,        KC_LCTL,      MT(M_CS, KC_X), MT(MOD_LGUI, KC_C),    KC_V,      KC_B,   ALL_T(KC_NO),
        KC_Z,           KC_QUOT,      LALT(KC_LSFT),  KC_LEFT, KC_RGHT,
                                                     KC_FN2,   KC_LGUI,
                                                               KC_HOME,
                                              KC_SPC,KC_BSPC,  KC_END,

        // right hand
             KC_RGHT,     KC_6,   KC_7,         KC_8,       KC_9,             KC_0,                    KC_MINS,
             KC_LEAD,     KC_Y,   KC_U,         KC_I,       KC_O,             KC_P,                    KC_BSLS,
                          KC_H,   ALT_T(KC_J),  KC_K,       KC_L,             LT(MDIA, KC_SCLN),       KC_QUOT,
             MEH_T(KC_NO),KC_N,   KC_M,         KC_COMM,    MT(M_LS, KC_DOT), MT(MOD_LGUI, KC_SLSH),   MO(SYMB),
                                  KC_UP,        KC_DOWN,    KC_LBRC,          KC_RBRC,                 KC_RSFT,
             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
/* Keymap 3: Window management
 *
 * ,--------------------------------------------------.           ,-------------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |       |       |       |       |       |        |
 * |--------+------+------+------+------+-------------|           |------+-------+-------+-------+-------+-------+--------|
 * |        |      |      | LSFT |      |      |      |           |      |       |       |       |       |       |        |
 * |--------+------+------+------+------+------|      |           |      |-------+-------+-------+-------+-------+--------|
 * |        |      |      |      |      |      |------|           |------| CA  < | CA  v | CA  ^ | CA  > |       |        |
 * |--------+------+------+------+------+------|      |           |      |-------+-------+-------+-------+-------+--------|
 * |        |      |      |      |      |      |      |           |      |       |       |       |       |       |        |
 * `--------+------+------+------+------+-------------'           `--------------+-------+-------+-------+-------+--------'
 *   |      |      |      |      |      |                                        |       |       |       |       |        |
 *   `----------------------------------'                                        `----------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Window management
[WORK] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,

    // right hand
       KC_TRNS,  KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
       KC_TRNS,  KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
                 M(WORKSPACE_LEFT),M(WORKSPACE_DOWN),M(WORKSPACE_UP),  M(WORKSPACE_RGHT),KC_TRNS,          KC_TRNS,
       KC_TRNS,  KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
                                   KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),                // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_LAYER_TAP_TOGGLE(WORK)
};

static uint16_t key_timer;  // Our timer to measure how long thins are taking! :D

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
          break;
        case CTLSHFT:
          if (record->event.pressed) {
            key_timer = timer_read();
            register_code(KC_LCTL);
            register_code(KC_LSFT);
          } else {
            unregister_code(KC_LCTL);
            unregister_code(KC_LSFT);

            if (timer_elapsed(key_timer) < KEY_TAP_SLOW) {
              register_code(KC_X);
              unregister_code(KC_X);
            }
          }
          break;
        case WORKSPACE_LEFT:
          if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_LEFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_LEFT);
          }
          break;
        case WORKSPACE_DOWN:
          if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_DOWN);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_DOWN);
          }
          break;
        case WORKSPACE_RGHT:
          if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_RGHT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_RGHT);
          }
          break;
        case WORKSPACE_UP:
          if (record->event.pressed) {
            register_code(KC_LCTL);
            register_code(KC_LALT);
            register_code(KC_UP);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
            unregister_code(KC_UP);
          }
          break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


bool did_leader_succeed;

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    // Short cut for go-to definition
    SEQ_ONE_KEY(KC_T) {
      register_code(KC_LCTL);
      register_code(KC_RBRC);
      unregister_code(KC_RBRC);
      unregister_code(KC_LCTL);
      did_leader_succeed = true;
    }

    // test of asd makes l gui
    SEQ_THREE_KEYS(KC_A, KC_S, KC_D) {
      register_code(KC_LGUI);
      unregister_code(KC_LGUI);
      did_leader_succeed = true;
    }

    // --- makes go to reset
    SEQ_THREE_KEYS(KC_MINS, KC_MINS, KC_MINS) {
#ifdef RGBLIGHT_COLOR_LAYER_0
      rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
      reset_keyboard();
      did_leader_succeed = true;
    }
    leader_end();
  };
};


/*  I have no idea what to do w/ this...
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}
 */

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
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
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};


// This is the old default one... can use this to check on old things.
/*
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 // Keymap 0: Basic layer
 // *
 // * ,--------------------------------------------------.           ,--------------------------------------------------.
 // * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 // * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 // * | Del    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 // * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 // * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|' / Cmd |
 // * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 // * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 // * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 // *   |Grv/L1|  '"  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 // *   `----------------------------------'                                       `----------------------------------'
 // *                                        ,-------------.       ,-------------.
 // *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 // *                                 ,------|------|------|       |------+--------+------.
 // *                                 |      |      | Home |       | PgUp |        |      |
 // *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 // *                                 |      |ace   | End  |       | PgDn |        |      |
 // *                                 `--------------------'       `----------------------'
 //
[BASE] = LAYOUT_ergodox_pretty(
  // left hand
  KC_EQL,          KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_LEFT,              KC_RGHT,      KC_6,    KC_7,    KC_8,    KC_9,              KC_0,           KC_MINS,
  KC_DEL,          KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    TG(SYMB),             TG(SYMB),     KC_Y,    KC_U,    KC_I,    KC_O,              KC_P,           KC_BSLS,
  KC_BSPC,         KC_A,        KC_S,          KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L,    LT(MDIA, KC_SCLN), GUI_T(KC_QUOT),
  KC_LSFT,         CTL_T(KC_Z), KC_X,          KC_C,    KC_V,    KC_B,    ALL_T(KC_NO),                  MEH_T(KC_NO), KC_N,    KC_M,    KC_COMM, KC_DOT,           CTL_T(KC_SLSH), KC_RSFT,
  LT(SYMB,KC_GRV), KC_QUOT,     LALT(KC_LSFT), KC_LEFT, KC_RGHT,                                              KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, TT(SYMB),
                                                           ALT_T(KC_APP), KC_LGUI,                KC_LALT, CTL_T(KC_ESC),
                                                                          KC_HOME,                 KC_PGUP,
                                                         KC_SPC, KC_BSPC, KC_END,                  KC_PGDN, KC_TAB, KC_ENT
),
 // * Keymap 1: Symbol Layer
 // *
 // * ,---------------------------------------------------.           ,--------------------------------------------------.
 // * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 // * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 // * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 // * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 // * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 // * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 // * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 // * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 // *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 // *   `-----------------------------------'                                       `----------------------------------'
 // *                                        ,-------------.       ,-------------.
 // *                                        |Animat|      |       |Toggle|Solid |
 // *                                 ,------|------|------|       |------+------+------.
 // *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 // *                                 |ness- |ness+ |------|       |------|      |      |
 // *                                 |      |      |      |       |      |      |      |
 // *                                 `--------------------'       `--------------------'
 // *
[SYMB] = LAYOUT_ergodox_pretty(
  // left hand
  VRSN,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,     KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,     KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
  KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,               KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
  KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,     KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
  EEP_RST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                         KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
                                               RGB_MOD, KC_TRNS,     RGB_TOG, RGB_SLD,
                                                        KC_TRNS,     KC_TRNS,
                                      RGB_VAD, RGB_VAI, KC_TRNS,     KC_TRNS, RGB_HUD, RGB_HUI
),
 // * Keymap 2: Media and mouse keys
 // *
 // * ,--------------------------------------------------.           ,--------------------------------------------------.
 // * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 // * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 // * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 // * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 // * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 // * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 // * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 // * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 // *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 // *   `----------------------------------'                                       `----------------------------------'
 // *                                        ,-------------.       ,-------------.
 // *                                        |      |      |       |      |      |
 // *                                 ,------|------|------|       |------+------+------.
 // *                                 |      |      |      |       |      |      |Brwser|
 // *                                 |      |      |------|       |------|      |Back  |
 // *                                 |      |      |      |       |      |      |      |
 // *                                 `--------------------'       `--------------------'
 // *
[MDIA] = LAYOUT_ergodox_pretty(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,                                         KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,

                                               KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                        KC_TRNS,     KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_WBAK
),
};
*/
