// L4 makro layer seems to be more flexible than leader key 
/*LEADER_EXTERNS();
void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    // Replace the sequences below with your own sequences.
    SEQ_ONE_KEY(KC_T) {
        tap_code(KC_UP);tap_code(KC_RGHT);tap_code(KC_ENT);tap_code(KC_BSPC);
    }
    SEQ_ONE_KEY(KC_N) {
        tap_code(KC_UP);tap_code(KC_ENT);tap_code(KC_BSPC);
    }
    SEQ_ONE_KEY(KC_L) {
        tap_code(KC_UP);tap_code(KC_RGHT);tap_code(KC_RGHT);tap_code(KC_ENT);tap_code(KC_BSPC);
    }
    SEQ_ONE_KEY(TD(TD_F)) {
             register_mods(MOD_BIT(KC_LCTL));
             register_mods(MOD_BIT(KC_LSFT));
             tap_code(KC_F);             
             unregister_mods(MOD_BIT(KC_LSFT));
             unregister_mods(MOD_BIT(KC_LCTL));
    }
    // Note: This is not an array, you don't need to put any commas
    // or semicolons between sequences.
    SEQ_TWO_KEYS(KC_W, KC_E) {
             register_mods(MOD_BIT(KC_LCTL));
             register_mods(MOD_BIT(KC_LSFT));
             tap_code(KC_F);             
             unregister_mods(MOD_BIT(KC_LSFT));
             unregister_mods(MOD_BIT(KC_LCTL));
    }
  }
}
*/