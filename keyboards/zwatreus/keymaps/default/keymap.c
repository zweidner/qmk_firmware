#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _RS 1
#define _LW 2

#define OSM_SFT OSM(MOD_LSFT)

/* In your system, make sure Caps Lock acts as the Compose Key, also known as the Multi Key. If so, then the quote on
 * the lower layer acts as macro to enter ¨ */
enum custom_keycodes {
	DIAERESIS = SAFE_RANGE,
	EN_DASH
};

  /* Basic layer (L0)
   *  q      d      r      w      b        ||       j      f      u      p      ;
   *  a      s      h      t      g        ||       y      n      e      o      i
   *  z      x      m      c      v        ||       k      l      ,      .      /
   * esc    tab   super  shift  bksp  ctrl || alt  space   RS     LW     '     ret
   */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QW] = LAYOUT( /* Workman */
    KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,                      KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN,
    KC_A,    KC_S,    KC_H,    KC_T,    KC_G,                      KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,
    KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,                      KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_GRV, KC_ESC,  KC_LALT, KC_LCTL, OSM_SFT,  KC_SPC,  KC_ENT,  KC_BSPC, MO(_RS), MO(_LW), KC_CAPS, KC_LGUI
  ),

  /* Raised layer (RS)
   *  !       @     {      }      |        ||       -      7      8      9      *
   *  #       $     (      )      `        ||       .      4      5      6      +
   *  %       ^     [      ]      ~        ||       &      1      2      3      \
   * menu    caps   <      >     del       ||       _                    0      =
   */

  [_RS] = LAYOUT( /* [> RAISE <] */
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_TAB,  KC_LEFT, KC_UP,   KC_RGHT, KC_LBRC,                   KC_RBRC, KC_TRNS ,KC_QUOT, KC_MINS, KC_EQL,
    KC_TRNS, KC_PGUP, KC_DOWN, KC_PGDN, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS ),

  /* Lower layer (LW)
   * insert  home   up    end    pgup      ||      vol+    F7     F8     F9    F10
   *  del    left  down  right   pgdn      ||      vol-    F4     F5     F6    F11
   *                                       ||      mute    F1     F2     F3    F12
	   *                                       ||        –                    ¨    reset
   */

  [_LW] = LAYOUT( /* [> LOWER <] */
    KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_TRNS,                   KC_VOLU, KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_DEL,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_VOLD, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_MUTE, KC_F1,   KC_F2,   KC_F3,   KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EN_DASH, KC_TRNS, KC_TRNS, DIAERESIS, QK_BOOT  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
		case DIAERESIS:
			// assuming KC_CAPS is your Multi Key
			SEND_STRING(SS_TAP(X_CAPS_LOCK)"\"");
			return false;
		case EN_DASH:
			// assuming KC_CAPS is your Multi Key
			SEND_STRING(SS_TAP(X_CAPS_LOCK)"--.");
			return false;
        }
    }
    return true;
};
