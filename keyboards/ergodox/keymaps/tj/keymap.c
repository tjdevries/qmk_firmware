#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 200

#define PREVENT_STUCK_MODIFIERS

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define WORK 3 // workspace keys

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
 * | LShift | Ctrl |x:M_CS|   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| ~L1    |
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
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_EQL,         KC_1,         KC_2,           KC_3,           KC_4,            KC_5,   KC_LEFT,
        KC_DELT,        KC_Q,         LT(WORK, KC_W), KC_E,           KC_R,            KC_T,   KC_INSERT,
        KC_GRV,         KC_A,         KC_S,           KC_D,           ALT_T(KC_F),     KC_G,
        KC_LSFT,        KC_LCTL,      MT(M_CS, KC_X), KC_C,           KC_V,            KC_B,   ALL_T(KC_NO),
        KC_Z,           KC_QUOT,      LALT(KC_LSFT),  KC_LEFT, KC_RGHT,
                                                     KC_FN2,   KC_LGUI,
                                                               KC_HOME,
                                              KC_SPC,KC_BSPC,  KC_END,

        // right hand
             KC_RGHT,     KC_6,   KC_7,         KC_8,       KC_9,   KC_0,             KC_MINS,
             KC_LEAD,     KC_Y,   KC_U,         KC_I,       KC_O,   KC_P,             KC_BSLS,
                          KC_H,   ALT_T(KC_J),  KC_K,       KC_L,   LT(MDIA, KC_SCLN),KC_QUOT,
             MEH_T(KC_NO),KC_N,   KC_M,         KC_COMM,    KC_DOT, CTL_T(KC_SLSH),   KC_FN1,
                                  KC_UP,        KC_DOWN,    KC_LBRC,KC_RBRC,          KC_RSFT,
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
[SYMB] = KEYMAP(
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
[MDIA] = KEYMAP(
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
[WORK] = KEYMAP(
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


LEADER_EXTERNS();

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        case WORK:
            ergodox_right_led_3_on();
        default:
            // none
            break;
    }

    LEADER_DICTIONARY() {
      leading = false;
      leader_end();

      // SEQ_ONE_KEY(KC_F) {
      //   register_code(KC_S);
      //   unregister_code(KC_S);
      // }
      SEQ_ONE_KEY(KC_T) {
        register_code(KC_LCTL);
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
        unregister_code(KC_LCTL);
      }
      SEQ_THREE_KEYS(KC_A, KC_S, KC_D) {
        register_code(KC_LGUI);
        unregister_code(KC_LGUI);
    }
  }
};
