#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Fillers to make layering more clear
#define _______ KC_TRNS // this is defined by QMK, can't redefine it to KC_NO
#define ___o___ KC_NO   // so use this instead0
#define XXXXXXX KC_NO//KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ,-----------F1------F2------F3------F4------F5------------------.      ,---F6------F7------F8----- F9-----F10-----F11-----F12----------.
 * |   ~   |   1   |   2   |   3   |   4   |   5   |XXXXXXX|XXXXXXX|      |   6   |   7   |   8   |   9   |   0   |   -   |   +   |XXXXXXX|
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  tab  |   q   |   w   |   e   |   r   |   t   |XXXXXXX|XXXXXXX|      |   y   |   u   |   i   |   o   |   p   |   {   |   }   |XXXXXXX|
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  esc  |   a   |   s   |   d   |   f   |   g   |XXXXXXX|XXXXXXX|      |   h   |   j   |   k   |   l   |   ;   |   "   |  L1h  |XXXXXXX|
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * | shift |   z   |   x   |   c   |   v   |   b   |XXXXXXX|XXXXXXX|      |   n   |   m   |   ,   |   .   |   /   | shift |  del  |XXXXXXX|
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  ctrl |  L1h  |  win  |  alt  |  bksp | space |XXXXXXX|XXXXXXX|      | space | enter |  alt  |  win  |  ctrl |  ctrl |   \   |XXXXXXX|
 * `---------------------------------------------------------------'      `---------------------------------------------------------------'
 */
  [0] = LAYOUT(
// ,-------|-------|-------|-------|-------|-------|-------|-------.      ,-------|-------|-------|-------|-------|-------|-------|-------.
     KC_GRV,  KC_1 ,  KC_2 ,  KC_3 ,  KC_4 ,  KC_5 ,XXXXXXX,XXXXXXX,         KC_6 ,  KC_7 ,  KC_8 ,  KC_9 ,  KC_0 ,KC_MINS, KC_EQL,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
     KC_TAB,  KC_Q ,  KC_W ,  KC_E ,  KC_R ,  KC_T ,XXXXXXX,XXXXXXX,         KC_Y ,  KC_U ,  KC_I ,  KC_O ,  KC_P ,KC_LBRC,KC_RBRC,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
     KC_ESC,  KC_A ,  KC_S ,  KC_D ,  KC_F ,  KC_G ,XXXXXXX,XXXXXXX,         KC_H ,  KC_J ,  KC_K ,  KC_L ,KC_SCLN,KC_QUOT, MO(1) ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
    KC_LSFT,  KC_Z ,  KC_X ,  KC_C ,  KC_V ,  KC_B ,XXXXXXX,XXXXXXX,         KC_N ,  KC_M ,KC_COMM, KC_DOT,KC_SLSH,KC_RSFT, KC_DEL,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-------|-------|-------|-------|-------|-------|-------|-------|
    KC_LCTL, MO(1) ,KC_LWIN,KC_LALT,KC_BSPC, KC_SPC,XXXXXXX,XXXXXXX,        KC_SPC, KC_ENT,KC_RALT,KC_RWIN,KC_RCTL,KC_RCTL,KC_BSLS,XXXXXXX
// `-------|-------|-------|-------|-------|-------|-------|-------'      `-------|-------|-------|-------|-------|-------|-------|-------'
  ),


/*
 * ,---------------------------------------------------------------.      ,---------------------------------------------------------------.
 * |prtscrn|   F1  |   F2  |   F3  |   F4  |   F5  |XXXXXXX|XXXXXXX|      |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |  F12  |XXXXXXX|
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  tab  |  home |   ^   |  end  |  pgup |  volu |XXXXXXX|XXXXXXX|      |   +   |   -   |   _   |   =   |       |       |       |XXXXXXX|
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  esc  |   <   |   v   |   >   |  pgdn |  mute |XXXXXXX|XXXXXXX|      |   <   |   v   |   ^   |   >   |       |       |  L1h  |XXXXXXX|
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * | shift |  prv  |  pau  |  nxt  |       |  vold |XXXXXXX|XXXXXXX|      |   L0  |perm-L1| insert|       |       | shift |  del  |XXXXXXX|
 * |---------------------------------------------------------------|      |---------------------------------------------------------------|
 * |  ctrl |  L1h  |  win  |  alt  |  bksp | space |XXXXXXX|XXXXXXX|      | space | enter |  alt  |  win  |  ctrl |  ctrl |       |XXXXXXX|
 * `---------------------------------------------------------------'      `---------------------------------------------------------------'
 */
  [1] = LAYOUT(
// ,-------|-------|-------|-------|-------|-------|-------|-------.      ,-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------.
    KC_PSCR, KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,XXXXXXX,XXXXXXX,          KC_F6   ,   KC_F7   ,   KC_F8   ,    KC_F9  ,   KC_F10  ,   KC_F11  ,  KC_F12   ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
     KC_TAB,KC_HOME, KC_UP , KC_END,KC_PGUP,KC_VOLU,XXXXXXX,XXXXXXX,        S(KC_EQL) ,  KC_MINS  , S(KC_MINS),   KC_EQL  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
     TO(0) ,KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,KC_MUTE,XXXXXXX,XXXXXXX,         KC_LEFT  ,  KC_DOWN  ,   KC_UP   ,  KC_RGHT  ,  XXXXXXX  ,  XXXXXXX  ,  XXXXXXX  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
    KC_LSFT,KC_MPRV,KC_MPLY,KC_MNXT,XXXXXXX,KC_VOLD,XXXXXXX,XXXXXXX,          TO(0)   ,   TG(1)   ,   KC_INS  ,  XXXXXXX  ,  XXXXXXX  ,  KC_RSFT  ,   KC_DEL  ,XXXXXXX,
// |-------|-------|-------|-------|-------|-------|-------|-------|      |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-------|
    KC_LCTL,XXXXXXX,KC_LWIN,KC_LALT,KC_BSPC, KC_SPC,XXXXXXX,XXXXXXX,          KC_SPC  ,   KC_ENT  ,  KC_RALT  ,  KC_RWIN  ,  KC_RCTL  ,  KC_RCTL  ,  XXXXXXX  ,XXXXXXX
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
