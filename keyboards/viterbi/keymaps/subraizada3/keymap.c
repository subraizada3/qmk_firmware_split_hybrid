#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _______ KC_TRNS // this is defined by QMK, can't redefine it to KC_NO
#define ___o___ KC_NO   // so use this instead0
#define XXXXXXX KC_NO//KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Note: don't have F12 conflict with Delete key on second layer                                                            macros
 * ,---F1------F2------F3------F4------F5------F6------------------.      ,---F7------F8------F9-----F10-----F11-------------F12----------.
 * |   ~   |   1   |   2   |   3   |   4   |   5   |XXXXXXX|XXXXXXX|      |   6   |   7   |   8   |   9   |   0   | delete|   A   |XXXXXXX| A: Media +
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  tab  |   q   |   w   |   f   |   p   |   g   |XXXXXXX|XXXXXXX|      |   k   |   n   |   u   |   y   |   ;   |   L0  |   B   |XXXXXXX| B: Media -
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  esc  |   a   |   r   |   s   |   t   |   d   |XXXXXXX|XXXXXXX|      |   h   |   l   |   e   |   i   |   o   |  L1h  |   C   |XXXXXXX| C: Media play/pause
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * | shift |   z   |   x   |   c   |   v   |   b   |XXXXXXX|XXXXXXX|      |   j   |   m   |   ,   |   .   |   /   | shift |   D   |XXXXXXX| D: Volume +
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  ctrl |  L1h  |  win  |  alt  | space | enter |XXXXXXX|XXXXXXX|      |  bksp | space |  L1t  |  alt  |  win  |  ctrl |   E   |XXXXXXX| E: Volume -
 * `---------------------------------------------------------------'      `---------------------------------------------------------------'
 */
  [0] = LAYOUT(
// ,-------|-------|-------|-------|-------|-------|-------|-------.      ,-------|-------|-------|-------|-------|-------|-------|-------.
     KC_GRV,  KC_1 ,  KC_2 ,  KC_3 ,  KC_4 ,  KC_5 ,XXXXXXX,XXXXXXX,         KC_6 ,  KC_7 ,  KC_8 ,  KC_9 ,  KC_0 , KC_DEL,KC_MNXT,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
//     KC_TAB,  KC_Q ,  KC_W ,  KC_F ,  KC_P ,  KC_G ,XXXXXXX,XXXXXXX,         KC_K ,  KC_N ,  KC_U ,  KC_Y ,KC_SCLN, TO(0) ,KC_WHOM,XXXXXXX,
     KC_TAB,  KC_Q ,  KC_W ,  KC_E ,  KC_R ,  KC_T ,XXXXXXX,XXXXXXX,         KC_Y ,  KC_U ,  KC_I ,  KC_O ,  KC_P , TO(0) ,KC_MPRV,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
//     KC_ESC,  KC_A ,  KC_R ,  KC_S ,  KC_T ,  KC_D ,XXXXXXX,XXXXXXX,         KC_H ,  KC_L ,  KC_E ,  KC_I ,  KC_O , MO(1) ,LCA(KC_T),XXXXXXX,
     KC_ESC,  KC_A ,  KC_S ,  KC_D ,  KC_F ,  KC_G ,XXXXXXX,XXXXXXX,         KC_H ,  KC_J ,  KC_K ,  KC_L ,KC_SCLN, MO(1) ,KC_MPLY,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
//    KC_LSFT,  KC_Z ,  KC_X ,  KC_C ,  KC_V ,  KC_B ,XXXXXXX,XXXXXXX,         KC_J ,  KC_M ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,KC_VOLU,XXXXXXX,
    KC_LSFT,  KC_Z ,  KC_X ,  KC_C ,  KC_V ,  KC_B ,XXXXXXX,XXXXXXX,         KC_N ,  KC_M ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT,KC_VOLU,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
    KC_LCTL, MO(1) ,KC_LWIN,KC_LALT,KC_BSPC, KC_SPC,XXXXXXX,XXXXXXX,        KC_SPC, KC_ENT, TG(1) ,KC_RALT,KC_RWIN,KC_RCTL,KC_VOLD,XXXXXXX
// `-------|-------|-------|-------|-------|-------|-------|-------'      `-------|-------|-------|-------|-------|-------|-------|-------'
  ),


/* Note: don't have F12 conflict with Delete key on second layer                                                            macros
 * ,---------------------------------------------------------------.      ,---------------------------------------------------------------.
 * |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |XXXXXXX|XXXXXXX|      |   F7  |   F8  |   F9  |  F10  |  F11  | delete|  F12  |XXXXXXX| A: F12 (don't confict with Delete key)
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  tab  |  home |   ^   |  end  |  pgup |   (   |XXXXXXX|XXXXXXX|      |   -   |   {   |   [   |   ]   |   |   |   L0  |   B   |XXXXXXX| B: Print screen
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  esc  |   <   |   v   |   >   |  pgdn |   )   |XXXXXXX|XXXXXXX|      |   <   |   v   |   ^   |   >   |   &   |  L1h  |   C   |XXXXXXX| C:
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * | shift |   $   |   %   |   ^   |   =   |   +   |XXXXXXX|XXXXXXX|      |   _   |   }   |   '   |   "   |   \   | shift |   D   |XXXXXXX| D:
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  ctrl |  L1h  |  win  |  alt  | space | enter |XXXXXXX|XXXXXXX|      |  bksp | space |  L1t  |  alt  |  win  |  ctrl |   E   |XXXXXXX| E:
 * `---------------------------------------------------------------'      `---------------------------------------------------------------'
 */
  [1] = LAYOUT(
// ,-------|-------|-------|-------|-------|-------|-------|-------.      ,-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------.
     KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6 ,XXXXXXX,XXXXXXX,          KC_F7   ,   KC_F8   ,   KC_F9   ,   KC_F10  ,   KC_F11  ,   KC_DEL  ,  KC_F12   ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
     KC_TAB,KC_HOME, KC_UP , KC_END,KC_PGUP,S(KC_9),XXXXXXX,XXXXXXX,         KC_MINS  , S(KC_LBRC),  KC_LBRC  ,  KC_RBRC  , S(KC_BSLS),   TO(0)   ,  KC_PSCR  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
     TG(1) ,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,S(KC_0),XXXXXXX,XXXXXXX,         KC_LEFT  ,  KC_DOWN  ,   KC_UP   ,  KC_RGHT  ,  S(KC_7)  ,  XXXXXXX  ,  XXXXXXX  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
    KC_LSFT,S(KC_4),S(KC_5),S(KC_6),KC_EQL,S(KC_EQL),XXXXXXX,XXXXXXX,       S(KC_MINS), S(KC_RBRC),  KC_QUOT  ,S(KC_QUOTE),  KC_BSLS  ,  KC_RSFT  ,  XXXXXXX  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
    KC_LCTL,XXXXXXX,KC_LWIN,KC_LALT,KC_BSPC, KC_SPC,XXXXXXX,XXXXXXX,          KC_SPC  ,   KC_ENT  ,   TG(1)   ,  KC_RALT  ,  KC_RWIN  ,  KC_RCTL  ,  XXXXXXX  ,XXXXXXX
// `-------|-------|-------|-------|-------|-------|-------|-------'      `-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------'
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
  return true;
}
