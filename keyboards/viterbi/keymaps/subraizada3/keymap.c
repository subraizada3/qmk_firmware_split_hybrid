#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _LAYER_0 0
#define _LAYER_1 1
// TODO: delete raise/adjust layers
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  LAYER_0 = SAFE_RANGE,
  LAYER_1,
	// TODO: delete raise/adjust layers
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS // this is defined by QMK, can't redefine it to KC_NO
#define ___o___ KC_NO   // so use this instead0
#define XXXXXXX KC_NO//KC_TRNS
#define KC_AJST ADJUST
#define KC_LOWR LAYER_1
#define KC_RASE RAISE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Note: don't have F12 conflict with Delete key on second layer                                                            macros
 * ,---F1------F2------F3------F4------F5------F6------------------.      ,---F7------F8------F9-----F10-----F11-------------F12----------.
 * |   ~   |   1   |   2   |   3   |   4   |   5   |XXXXXXX|XXXXXXX|      |   6   |   7   |   8   |   9   |   0   | delete|   A   |XXXXXXX| A: Yaquake
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  tab  |   q   |   w   |   f   |   p   |   g   |XXXXXXX|XXXXXXX|      |   k   |   n   |   u   |   y   |   ;   |   L0  |   B   |XXXXXXX| B: Firefox
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  esc  |   a   |   r   |   s   |   t   |   d   |XXXXXXX|XXXXXXX|      |   h   |   l   |   e   |   i   |   o   |  L1h  |   C   |XXXXXXX| C: Konsole
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * | shift |   z   |   x   |   c   |   v   |   b   |XXXXXXX|XXXXXXX|      |   j   |   m   |   ,   |   .   |   /   | shift |   D   |XXXXXXX| D: Volume +
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  ctrl |  L1h  |  win  |  alt  | space | enter |XXXXXXX|XXXXXXX|      |  bksp | space |  L1t  |  alt  |  win  |  ctrl |   E   |XXXXXXX| E: Volume -
 * `---------------------------------------------------------------'      `---------------------------------------------------------------'
 */
  [_LAYER_0] = LAYOUT(
// ,-------|-------|-------|-------|-------|-------|-------|-------.      ,-------|-------|-------|-------|-------|-------|-------|-------.
     KC_GRV,  KC_1 ,  KC_2 ,  KC_3 ,  KC_4 ,  KC_5 ,XXXXXXX,XXXXXXX,         KC_6 ,  KC_7 ,  KC_8 ,  KC_9 ,  KC_0 , KC_DEL,  KC_1 ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
     KC_TAB,  KC_Q ,  KC_W ,  KC_F ,  KC_P ,  KC_G ,XXXXXXX,XXXXXXX,         KC_K ,  KC_N ,  KC_U ,  KC_Y ,KC_SCLN, TO(0) ,  KC_1 ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
     KC_ESC,  KC_A ,  KC_R ,  KC_S ,  KC_T ,  KC_D ,XXXXXXX,XXXXXXX,         KC_H ,  KC_L ,  KC_E ,  KC_I ,  KC_O , MO(1) ,  KC_1 ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
    KC_LSFT,  KC_Z ,  KC_X ,  KC_C ,  KC_V ,  KC_B ,XXXXXXX,XXXXXXX,         KC_J ,  KC_M ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,KC_VOLU,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
    KC_LCTL, MO(1) ,KC_LWIN,KC_LALT, KC_SPC, KC_ENT,XXXXXXX,XXXXXXX,       KC_BSPC, KC_SPC, TG(1) ,KC_RALT,KC_RWIN,KC_RCTL,KC_VOLD,XXXXXXX
// `-------|-------|-------|-------|-------|-------|-------|-------'      `-------|-------|-------|-------|-------|-------|-------|-------'
  ),

/* Note: don't have F12 conflict with Delete key on second layer                                                            macros
 * ,---------------------------------------------------------------.      ,---------------------------------------------------------------.
 * |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |XXXXXXX|XXXXXXX|      |   F7  |   F8  |   F9  |  F10  |  F11  | delete|  F12  |XXXXXXX| A: F12 (don't confict with Delete key)
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  tab  |  home |   ^   |  end  |  pgup |   (   |XXXXXXX|XXXXXXX|      |   ^   |   -   |   [   |   ]   |   |   |   L0  |   B   |XXXXXXX| B: Print screen
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  esc  |   <   |   v   |   >   |  pgdn |   )   |XXXXXXX|XXXXXXX|      |   <   |   >   |   {   |   }   |   &   |  L1h  |   C   |XXXXXXX| C: Media pause
 * |---------------------------------------------------------------|      |---------------------------------------------------------------| Note: media next/prev align with volume up/down
 * | shift |   $   |   %   |   ^   |   =   |   +   |XXXXXXX|XXXXXXX|      |   v   |   _   |   '   |   "   |   \   | shift |   D   |XXXXXXX| D: Media next
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  ctrl |  L1h  |  win  |  alt  | space | enter |XXXXXXX|XXXXXXX|      |  bksp | space |  L1t  |  alt  |  win  |  ctrl |   E   |XXXXXXX| E: Media prev
 * `---------------------------------------------------------------'      `---------------------------------------------------------------'
 */
  [_LAYER_1] = LAYOUT(
// ,-------|-------|-------|-------|-------|-------|-------|-------.      ,-------|-----------|-----------|-----------|-----------|-----------|-----------|-------.
     KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,XXXXXXX,XXXXXXX,        KC_F7 ,   KC_F8   ,   KC_F9   ,   KC_F10  ,   KC_F11  ,   KC_DEL  ,  KC_F12   ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
     KC_TAB,KC_HOME, KC_UP , KC_END,KC_PGUP,S(KC_9),XXXXXXX,XXXXXXX,        KC_UP ,  KC_MINS  ,  KC_LBRC  ,  KC_RBRC  , S(KC_BSLS),   TO(0)   ,  KC_PSCR  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
     KC_ESC,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,S(KC_0),XXXXXXX,XXXXXXX,       KC_LEFT,  KC_RGHT  , S(KC_LBRC), S(KC_RBRC),  S(KC_7)  ,  XXXXXXX  ,  KC_MPLY  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
    KC_LSFT,S(KC_4),S(KC_5),S(KC_6),KC_EQL,S(KC_EQL),XXXXXXX,XXXXXXX,      KC_DOWN, S(KC_MINS),  KC_QUOT  ,S(KC_QUOTE),  KC_BSLS  ,  KC_RSFT  ,  KC_MNXT  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
    KC_LCTL,XXXXXXX,KC_LWIN,KC_LALT, KC_SPC, KC_ENT,XXXXXXX,XXXXXXX,       KC_BSPC,   KC_SPC  ,   TG(1)   ,  KC_RALT  ,  KC_RWIN  ,  KC_RCTL  ,  KC_MPRV  ,XXXXXXX
// `-------|-------|-------|-------|-------|-------|-------|-------'      `-------|-----------|-----------|-----------|-----------|-----------|-----------|-------'
  ),

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(LAYER_0_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LAYER_0:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_LAYER_0);
      }
      return false;
      break;
    case LAYER_1:
      if (record->event.pressed) {
        layer_on(_LAYER_1);
        update_tri_layer(_LAYER_1, _RAISE, _ADJUST);
      } else {
        layer_off(_LAYER_1);
        update_tri_layer(_LAYER_1, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LAYER_1, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LAYER_1, _RAISE, _ADJUST);
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
