/* Copyright 2020 gerhard-h
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


void rgb_matrix_indicators_user(void) {
switch (biton32(layer_state)) {
case 0:
rgb_matrix_set_color_all(0,1,10);
rgb_matrix_set_color(34, 70, 10, 10); // cursor keys
rgb_matrix_set_color(44, 70, 10, 10);
rgb_matrix_set_color(45, 70, 10, 10);
rgb_matrix_set_color(46, 70, 10, 10);
break;
case 1:
//rgb_matrix_set_color_all(0,150,55); // all bright
rgb_matrix_set_color_all(0,1,30); 
rgb_matrix_set_color(1, 150, 150, 50); // num pad
rgb_matrix_set_color(2, 150, 150, 50);
rgb_matrix_set_color(3, 150, 150, 50);
rgb_matrix_set_color(13, 150, 150, 50);
rgb_matrix_set_color(14, 150, 150, 50);
rgb_matrix_set_color(15, 150, 150, 50);
rgb_matrix_set_color(25, 150, 150, 50);
rgb_matrix_set_color(26, 150, 150, 50);
rgb_matrix_set_color(27, 150, 150, 50);
rgb_matrix_set_color(38, 150, 150, 50);
rgb_matrix_set_color(7, 1, 150, 50); // ue
rgb_matrix_set_color(9, 1, 150, 50); // oe
rgb_matrix_set_color(21, 1, 150, 50); // 1
rgb_matrix_set_color(33, 1, 150, 50); // 1
rgb_matrix_set_color(34, 100, 10, 10); // cursor keys
rgb_matrix_set_color(44, 100, 10, 10);
rgb_matrix_set_color(45, 100, 10, 10);
rgb_matrix_set_color(46, 100, 10, 10);
break;
case 2:
rgb_matrix_set_color_all(0,1,60);
rgb_matrix_set_color(13, 150, 150, 50); // ä
rgb_matrix_set_color(14, 150, 150, 50); // ß
rgb_matrix_set_color(8, 150, 150, 50); // nav
rgb_matrix_set_color(19, 150, 150, 50); // nav
rgb_matrix_set_color(20, 150, 150, 50); // nav
rgb_matrix_set_color(21, 150, 150, 50); // nav
rgb_matrix_set_color(30, 150, 150, 50); // esc
rgb_matrix_set_color(34, 100, 10, 10); // cursor keys
rgb_matrix_set_color(44, 100, 10, 10);
rgb_matrix_set_color(45, 100, 10, 10);
rgb_matrix_set_color(46, 100, 10, 10);
break;
case 3:
rgb_matrix_set_color_all(0,1,30);
rgb_matrix_set_color(1, 150, 150, 50); // reset
rgb_matrix_set_color(8, 150, 150, 50); // I I I
rgb_matrix_set_color(20, 150, 150, 50);
rgb_matrix_set_color(32, 150, 150, 50);
rgb_matrix_set_color(6, 150, 150, 50);
rgb_matrix_set_color(18, 150, 150, 50);
rgb_matrix_set_color(30, 150, 150, 50);
rgb_matrix_set_color(4, 150, 150, 50);
rgb_matrix_set_color(16, 150, 150, 50);
rgb_matrix_set_color(28, 150, 150, 50);

break;
case 4:
rgb_matrix_set_color_all(RGB_YELLOW);
rgb_matrix_set_color(1, 150, 150, 50); // num pad
rgb_matrix_set_color(2, 150, 150, 50);
rgb_matrix_set_color(3, 150, 150, 50);
rgb_matrix_set_color(13, 150, 150, 50);
rgb_matrix_set_color(14, 150, 150, 50);
rgb_matrix_set_color(15, 150, 150, 50);
rgb_matrix_set_color(25, 150, 150, 50);
rgb_matrix_set_color(26, 150, 150, 50);
rgb_matrix_set_color(27, 150, 150, 50);
rgb_matrix_set_color(38, 150, 150, 50);
rgb_matrix_set_color(19, 150, 150, 50); // makro
rgb_matrix_set_color(20, 150, 150, 50);
rgb_matrix_set_color(21, 150, 150, 50);
rgb_matrix_set_color(7, 150, 150, 50);
rgb_matrix_set_color(9, 150, 150, 50);
rgb_matrix_set_color(33, 150, 150, 50);
rgb_matrix_set_color(45, 50, 10, 10); // volume
rgb_matrix_set_color(34, 50, 10, 10);
break;
}
}


enum layers { _L0, _L1, _L2, _L3, _L4 };

// Macros
enum custom_keycodes {
    PICKFIRST = SAFE_RANGE,
    PICK2ND,
    PICK3RD,
    CTLSFTF,
//    CIRCUM
//    L0AUTOS,
//    ALT_TAB
};

/*static bool is_alt_tab_active = false;
static uint16_t alt_tab_timer = 0;*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case PICKFIRST:
        if (record->event.pressed) {
            // when keycode PICKFIRST is pressed
            tap_code(KC_UP);tap_code(KC_ENT);
        } else {
            // when keycode PICKFIRST is released
        }
        break;

    case PICK2ND:
        if (record->event.pressed) {
            // when keycode PICK2ND is pressed
            tap_code(KC_UP);tap_code(KC_RGHT);tap_code(KC_ENT);
        } else {
            // when keycode PICK2ND is released
        }
        break;

    case PICK3RD:
        if (record->event.pressed) {
             tap_code(KC_UP);tap_code(KC_RGHT);tap_code(KC_RGHT);tap_code(KC_ENT);
        }
        break;
        
    case CTLSFTF:
        if (record->event.pressed) {
             register_mods(MOD_BIT(KC_LCTL));
             register_mods(MOD_BIT(KC_LSFT));
             tap_code(KC_F);             
             unregister_mods(MOD_BIT(KC_LSFT));
             unregister_mods(MOD_BIT(KC_LCTL));
        }
        break;
/*    case CIRCUM:
        if (record->event.pressed) {
            if (get_mods() | MOD_MASK_SHIFT) {tap_code16(S(KC_GRV)); break;}
            tap_code16(KC_GRV);
            tap_code(KC_SPC);
            break;
        }
        break;
        */
/*        
#   ifdef AUTO_SHIFT_ENABLE
    case L0AUTOS:
        layer_move(_L0);
            autoshift_enable();
        break;
#   endif
        
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
*/
    }
    return true;
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

/*struct to persisit td state*/
typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;


/*tap dance user_data*/
typedef struct {
    uint16_t keycode;
    uint16_t keycode2;
    uint16_t keycode3;
    uint16_t keycode4;
} dance_user_data_t;

//shared tapstate
static td_tap_t atap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
//static uint8_t active_osl = 0; //for OSL tap dance

/*general td state evaluation*/
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

//individual Tap Dance Declarations
enum {
  TD_A_UML,
  TD_O_UML,
  TD_F,
  TD_U_UML,
  TD_SS_UML,
  TD_DASH,
  TD_DOT,
  TD_PAR,
  TD_CUR,
  TD_SQU,
  TD_ANG,
  TD_QUOT,
//  TD_DQUOT,
  TD_I_BS,
  TD_CIRCUM,
  TD_TICK,
  TD_COMM,
  TD_DOL_CTL,
  TD_PIPE_SFT,
  TD_KOE_ALT,
  TD_1,
  TD_2,
  TD_3,
  TD_4,
  TD_5,
  TD_6,
  TD_7,
  TD_8,
  TD_9,
  TD_0,
  TD_10,
  TD_12,
//  TD_HASH,
  TD_Q,
  TD_TAB_ENT,
  TD_M,
  TD_H,
  TD_Z,
  TD_Y,
  TD_X,
  TD_C,
  TD_V,
  TD_B,
  TD_G,
  TD_J,
  TD_W,
  TD_N,
  TD_D,
  TD_E,
  TD_L,
  TD_ESC,
  TD_DEL10,
  TD_R,
  TD_P,
  TD_T,
};

/* ALT_TAB
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1500) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
*/

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
}*/

// ^ °
void circum_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("` "); break;
        case TD_SINGLE_HOLD:
            SEND_STRING("~"); break;
        default: 
            switch (state->count) {
                case 2: SEND_STRING("``"); break;
                case 3: SEND_STRING("` ");SEND_STRING("` ");SEND_STRING("` "); break;
                case 4: SEND_STRING("` ");SEND_STRING("` ");SEND_STRING("` ");SEND_STRING("` "); break;
                case 5: SEND_STRING("` ");SEND_STRING("` ");SEND_STRING("` ");SEND_STRING("` ");SEND_STRING("` "); break;
            };
        break;
    }
}
void circum_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

//´`
void tick_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("= "); break;
        case TD_SINGLE_HOLD:
            SEND_STRING("+ "); break;
        default:
            switch (state->count) {
                case 2: SEND_STRING("=="); break;
                default: SEND_STRING("= ");SEND_STRING("= ");SEND_STRING("= "); break;
            };
        break;
    }
}
void tick_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

// () <> {} [] "" '' ...
//static uint8_t curly_layer;
void curly_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
     atap_state.state = cur_dance(state);
     uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
     uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD:
            tap_code16(keycode);
            tap_code16(keycode2);
            tap_code(KC_LEFT); 
        break;
        case TD_SINGLE_TAP:
        default: register_code16(keycode); break;
    }
}
void curly_dance_each(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1){
//        curly_layer = active_osl; //memorize the layer before we start messing around with it
//
//        if (curly_layer > 0) {
//            reset_oneshot_layer();
//            layer_move(curly_layer);
//        }
//
    }
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    if (state->count > 1) tap_code16(keycode);
};
void curly_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD: break;
        case TD_SINGLE_TAP:
        default:
            unregister_code16(keycode);
        break;
    }
    atap_state.state = TD_NONE;
///    if (curly_layer > 0) {
//            layer_move(_L0);
//            curly_layer = 0;
//    }
//    layer_move(_L0);
//    set_oneshot_layer(curly_layer, ONESHOT_START);
//    tap_code(KC_NO);
//    clear_oneshot_layer_state(ONESHOT_PRESSED);
//
     }

// TD shortcut () <> {} [] "" ''
void shortcut_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    uint16_t keycode4 = ((dance_user_data_t*)user_data)->keycode4;
    switch (atap_state.state) {
        case TD_DOUBLE_HOLD:
            tap_code16(keycode3);
            tap_code16(keycode4);
            tap_code(KC_LEFT); 
        break;
        case TD_SINGLE_HOLD:
             if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
#            ifdef AUTO_SHIFT_ENABLE
                 tap_code16(keycode2);
#            else
                 tap_code16(keycode3);
#            endif
        break;
        case TD_SINGLE_TAP: tap_code16(keycode); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
             if (keycode2 != KC_NO) {tap_code16(keycode2); break;}
        default:
        tap_code16(keycode); tap_code16(keycode); break;
    }
}
void shortcut_dance_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    if (state->count > 2) tap_code16(keycode);
};
void shortcut_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

// ö ß ä
/*for when DOUBLE_TAP should behave like TD_DOUBLE_SINGLE_TAP */
void dance_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;        //normal and double tap
#   ifdef AUTO_SHIFT_ENABLE
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;      //shifted
#   endif
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;      //double hold
    switch (atap_state.state) {
        case TD_SINGLE_TAP: tap_code(keycode); break;
        case TD_SINGLE_HOLD:
             if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
#            ifdef AUTO_SHIFT_ENABLE
                 if (get_autoshift_state()) {
                     tap_code16(keycode2); break;
                 }
             tap_code16(keycode); break;
#            else
                tap_code16(keycode3); break;
#            endif
        case TD_DOUBLE_HOLD: tap_code16(keycode3); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default: 
            for (uint8_t i=0; i < state->count; i++) {
                tap_code16(keycode);
            };
        break;
    }
}
void dance_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

// ü, i  \bs, z ! C(z),
/*for when TD_SINGLE_TAP, TD_SINGLE_HOLD, DOUBLE_TAP should all behave different but DOUBLE_TAP=TD_DOUBLE_HOLD*/
void dance_dbltap_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;        //normal
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;      //shifted = single hold
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;      //double hold and double tap
    switch (atap_state.state) {
        case TD_SINGLE_TAP: tap_code(keycode); break;
        case TD_SINGLE_HOLD:
             if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
#            ifdef AUTO_SHIFT_ENABLE
                 if (get_autoshift_state()) {
                     tap_code16(keycode2); break;
                 }
                 tap_code(keycode); break;
#            else
                 tap_code16(keycode2); break;
#            endif
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
#            ifdef AUTO_SHIFT_ENABLE
                 if (!get_autoshift_state()) {
                     tap_code16(keycode);tap_code16(keycode); break;
                 }
#            endif
        case TD_DOUBLE_HOLD: tap_code16(keycode3); break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default: 
            for (uint8_t i=0; i < state->count; i++) {
                tap_code(keycode);
            };
        break;
    }
}
void dance_dbltap_reset(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

// ::: *** /// ...... ------ ____. triple tap for autorepeat keycode, no autorepeat on DTH
void dance_autorepeat_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (atap_state.state) {
        case TD_SINGLE_TAP: register_code16(keycode); break;
        case TD_SINGLE_HOLD:
                if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
                register_code16(keycode2); break;
        case TD_DOUBLE_HOLD: tap_code16(keycode3); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default: 
            for (uint8_t i=1; i < state->count; i++) {
                tap_code16(keycode);
            };
            register_code16(keycode);
        break;
    }
}
void dance_autorepeat_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    //uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (atap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(keycode); break;
        case TD_SINGLE_HOLD: unregister_code16(keycode2); break;
        case TD_DOUBLE_HOLD:  break;//unregister_code16(keycode3); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: 
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default: unregister_code16(keycode); break;
    }
    atap_state.state = TD_NONE;
}

// mod tap as tap dance
static td_tap_t mtap_state = { //tap dance with mods need there own status each else you may run into mod-tapping into a tap dance key
    .is_press_action = true,
    .state = TD_NONE
};
void modifier_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    mtap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    switch (mtap_state.state) {
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(keycode2)); break;
        default: register_code16(keycode); break;
    }
}
void modifier_dance_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    if (state->count > 1) {
            tap_code16(keycode);
    }
};
void modifier_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    switch (mtap_state.state) {
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(keycode2)); break;
        default: unregister_code16(keycode); break;
    }
    mtap_state.state = TD_NONE;
}

// mod tap as dbl tap dance
static td_tap_t ctap_state = { //tap dance with mods need there own status
    .is_press_action = true,
    .state = TD_NONE
};
void modifier_dbldance_finished (qk_tap_dance_state_t *state, void *user_data) {
    ctap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (ctap_state.state) {
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(keycode2)); break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: register_code16(keycode3); break;
        default: register_code(keycode); break;
    }
}
void modifier_dbldance_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    if (state->count > 2) {
            tap_code(keycode);
    }
};
void modifier_dbldance_reset (qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (ctap_state.state) {
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(keycode2)); break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(keycode3); break;
        default: unregister_code(keycode); break;
    }
    ctap_state.state = TD_NONE;
}


// no autoshift for numbers on the number layer, also # F key instead
// this is a way to set a shifted key however you want
/*
void noshift_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint8_t shifts = get_mods() & MOD_MASK_SHIFT;
    uint8_t osshifts = get_oneshot_mods() & MOD_MASK_SHIFT;
    if (shifts) del_mods(shifts);
    if (osshifts) del_oneshot_mods(osshifts);
    if (shifts | osshifts){
        tap_code16(keycode2);
    } else {
        tap_code16(keycode);
    }
    if (shifts) register_mods(shifts);
    // no reset for one shot mods
};
*/

/*important macro to define userdata */
#define ACTION_TAP_DANCE_FN_ADVANCED_USER(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, user_user_data) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void*)user_user_data, }


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_ESC, KC_HOME, KC_HOME})), // tap, hold, double_tap 
    [TD_Q] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_Q, KC_END, A(C(KC_Q))})), 
    [TD_F] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_F, S(KC_F), S(KC_4)})), // tap, autoshift only hold, hold & double_hold
    [TD_X] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_X, S(KC_6), C(KC_X)})),
    [TD_C] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, shortcut_dance_reset, &((dance_user_data_t){KC_C, C(KC_C), A(C(KC_7)), A(C(KC_0))})), // tap, double tap key or KC_0, hold, double_hold autoclose
    [TD_V] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_V, A(C(KC_0)), C(KC_V)})),
    [TD_Y] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_Z, C(KC_Z), C(KC_Z)})),
    [TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_Y, KC_EXLM,  C(KC_Y)})),
    [TD_G] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_G, S(KC_G), KC_RPRN})),
    [TD_B] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_B, S(KC_B), KC_RBRC})),
    [TD_M] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_M, S(KC_RBRC), S(KC_RBRC)})),
    [TD_J] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_J, KC_PERC, KC_PERC})),
    [TD_U_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_U, KC_LBRC, KC_LBRC})),
    [TD_A_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_A, S(KC_A), KC_QUOT})),
    [TD_O_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_O, S(KC_O), KC_SCLN})),
    [TD_R] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_R, S(KC_R), A(C(KC_9))})),
//    [TD_P] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_P, A(C(KC_RBRC)), A(C(KC_RBRC))})),
    [TD_T] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_T, S(KC_9), S(KC_9)})),
    [TD_SS_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_S, S(KC_S), KC_MINS})),
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_DOT, S(KC_DOT), S(KC_NUBS)})),  // tap(repeated on tripple tap), hold(repeated), double_hold (not repeated)
    [TD_DASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_SLSH, S(KC_SLSH), S(KC_7)})),
    [TD_CIRCUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, circum_dance_finished, circum_dance_reset), //^
    [TD_TICK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tick_dance_finished, tick_dance_reset), //´´´```
    [TD_I_BS] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_I, A(C(KC_MINS)), S(KC_7)})),
    [TD_DOL_CTL] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dance_each, modifier_dance_finished, modifier_dance_reset, &((dance_user_data_t){S(KC_4), KC_LCTL})),
    [TD_PIPE_SFT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dance_each, modifier_dance_finished, modifier_dance_reset, &((dance_user_data_t){A(C(KC_NUBS)), KC_LSFT})),
    [TD_KOE_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_K, KC_LALT, A(KC_TAB)})),
    [TD_ANG] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_NUBS, S(KC_NUBS)})),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_NUHS), S(KC_NUHS)})),
    [TD_PAR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_8), S(KC_9)})),
    /*
    [TD_CUR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){A(C(KC_7)), A(C(KC_0))})),
    [TD_SQU] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){A(C(KC_8)), A(C(KC_9))})),

    [TD_DQUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_AT, KC_AT})),
    S(KC_8)*/
    [TD_COMM] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished,  dance_dbltap_reset, &((dance_user_data_t){KC_COMM, S(KC_COMM), KC_NUBS})),
    [TD_W] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, shortcut_dance_reset, &((dance_user_data_t){KC_W, KC_NO, KC_AT, KC_AT})),
    [TD_L] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, shortcut_dance_reset, &((dance_user_data_t){KC_L, KC_NO, S(KC_NUHS), S(KC_NUHS)})),
    [TD_E] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, shortcut_dance_reset, &((dance_user_data_t){KC_E, KC_NO, A(C(KC_8)), A(C(KC_9))})),
    [TD_D] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_D, S(KC_D),A(C(KC_NUBS))})),
    [TD_N] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, shortcut_dance_reset, &((dance_user_data_t){KC_N, KC_NO, S(KC_8), S(KC_9)})),
//    [TD_HASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER( NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_NUHS, KC_NUHS, KC_NUHS})),
    /*
    [TD_1] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_1, KC_F1})),
    [TD_2] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_2, KC_F2})),
    [TD_3] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_3, KC_F3})),
    [TD_4] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_4, KC_F4})),
    [TD_5] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_5, KC_F5})),
    [TD_6] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_6, KC_F6})),
    [TD_7] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_7, KC_F7})),
    [TD_8] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_8, KC_F8})),
    [TD_9] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_9, KC_F9})),
    [TD_0] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_0, KC_F11})),
    [TD_12] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_1, KC_F12})),
    [TD_10] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){ALGR(KC_E), KC_F10})),
    [TD_DEL10] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_DEL, KC_F10})),
    */
    [TD_1] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_1, KC_F1, KC_F1})),
    [TD_2] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_2, KC_F2, KC_F2})),
    [TD_3] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_3, KC_F3, KC_F3})),
    [TD_4] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_4, KC_F4, KC_F4})),
    [TD_5] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_5, KC_F5, KC_F5})),
    [TD_6] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_6, KC_F6, KC_F6})),
    [TD_7] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_7, KC_F7, KC_F7})),
    [TD_8] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_8, KC_F8, KC_F8})),
    [TD_9] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_9, KC_F9, KC_F9})),
    [TD_0] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_0, KC_F11, KC_F11})),
    [TD_12] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_1, KC_F12, KC_F12})),
    [TD_10] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){ALGR(KC_E),  KC_F10, KC_F10})),
    [TD_DEL10] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_hold_finished, dance_hold_reset, &((dance_user_data_t){KC_DEL, KC_F10, KC_F10})),
    [TD_TAB_ENT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_TAB, KC_LCTL, KC_ENT})),
    [TD_H] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_dbltap_finished, dance_dbltap_reset, &((dance_user_data_t){KC_H, KC_UNDS, KC_UNDS})),
};
/*
* todo
* 
* light_control on OSM fixed
*
* shift + non shiftable key (e.g. A(C(KC_E))) outputs nothing instead of ignoring the shift, maybe this can be checked automatically
* 
* re add curly dance to "[{}]"
* 
* OSL fixed Mods werden manchmal ignoriert

* (-) tap dance on lower/raise to lock layer_state_cmp ... but because space and emter are spammable keys 
fake layer tap with extra osl
OSL(num) num TO(sym) sym TG(num) layer3 TO(0)

* combos
* qw = esc better than tapdance qq?,<<,<<,,<    <<;<<<,,<;;<,<<;<>>>
* ,<<:;;>>>>

* home row mods?

2xesc = home 2xq = end 
hh ?
zz !
gG + bB * xX cC vV


* single key alt tab {KC_LCTL,KC_LALT,KC_TAB}
single hold: alt + ctrl + tab & modus=ON 
tap: tab
single hold: if  modus==ON & Space  

enable tap dance inside OSL > z!z!!!!!!!!!!

        
C+(W+W) = A+F4 oder(C+W)+W oder C+(W+Q)
*numberpad 2.0
€456:
3210.
-789,

leader key  combos? are they compatible with tapdance keys? F keys
always send KC_LEAD after ESC ?
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* ESC           PSCR          NO            ESC Home      1             2             3             4             5             6             7             8             9             0             DEL
*  TO(L0)        TO(L1)        NO            ESC Home      Q End         W             E             R             J             Y             U Ü           I             O Ö           P             Backspc
*  PgUp          VOLU          NO            TAB/Ctrl      A Ä           S ß           D             F             G             H             N             T             L             k/Alt K       Enter/Ctrl
*  PgDn          VOLD          NO            HOME/Shift    Z             X             C             V             B             M             ,             . : *         - _ /         Up            END/Shift
*  CTL           ALT           NO            PgUp/Ctrl     PgDn/WIN      Del/Alt       Tab/L2        Enter/L1      Space/Shift   Space/Shift   Space/L2      OSL L4        Left          Down          Right
*/
[0] = LAYOUT_planck_mit(    
                                         TD(TD_ESC),          TD(TD_Q),        TD(TD_W), TD(TD_E), TD(TD_R),      TD(TD_J), TD(TD_Z),    TD(TD_U_UML),    TD(TD_I_BS),    TD(TD_O_UML),               RESET,                        KC_BSPC,
                               MT(MOD_LCTL ,KC_TAB),      TD(TD_A_UML),   TD(TD_SS_UML), TD(TD_D), TD(TD_F),      TD(TD_G), TD(TD_H),        TD(TD_N),       TD(TD_T),        TD(TD_L),     TD(TD_KOE_ALT), MT(MOD_LCTL,KC_ENT),
                                      OSM(MOD_LSFT),          TD(TD_Y),        TD(TD_X), TD(TD_C), TD(TD_V),      TD(TD_B), TD(TD_M),     TD(TD_COMM),     TD(TD_DOT),     TD(TD_DASH),              KC_UP,                  OSM(MOD_LSFT),
                              MT(MOD_LCTL, KC_PGUP), MT(MOD_LGUI, KC_PGDN),
                                                                     MT(MOD_LALT,KC_DEL),
                                                                                 TD(TD_TAB_ENT),
                                                                                                 OSL(_L1),
                                                                                                                 MT(MOD_LSFT,KC_SPC),
                                                                                                                                          OSL(_L2),        OSL(_L4),         KC_LEFT,            KC_DOWN,                KC_RGHT
 ),
/*            ________      ________      ________      F12           F1            F2            F3            F4            F5            F6            F7            F8            F9            F10           F11
*             ________      TO(_L2)       ________      ________      1             2             3           DEL           BSP             !             ü            ä\             ö             ß~            ________
*             ________      ________      ________      ________      4             5             6             0             .             ?             (             )             '             #             ________
*             ________      ________      ________      ________      7             8             9             1             ,             =             <             >             /             ________      ________
*             ________      ________      ________      ________      ________      0/Alt         TO(2)      ________      ________      ________      ________      TG(_L2)          ________      ________      ________
*/
[1] = LAYOUT_planck_mit(

                                                         KC_TRNS,         TD(TD_1),             TD(TD_2),                    TD(TD_3),          TD(TD_DEL10),       KC_BSPC,     KC_EXLM,    KC_LBRC,        KC_QUOT,       KC_SCLN,        KC_MINS,       KC_TRNS,
                                                         KC_TRNS,         TD(TD_4),             TD(TD_5),                    TD(TD_6),              TD(TD_0),    TD(TD_DOT),     KC_UNDS, TD(TD_PAR),        KC_LPRN,   TD(TD_QUOT),        KC_NUHS,       KC_TRNS,
                                                         KC_TRNS,         TD(TD_7),              TD(TD_8),                   TD(TD_9),             TD(TD_12),   TD(TD_COMM),  S(KC_RBRC), TD(TD_ANG),     S(KC_NUBS),       KC_AMPR,          KC_UP,       KC_TRNS,
                                                         KC_TRNS,          KC_TRNS,     MT(MOD_LALT,KC_0),                    KC_TRNS,               KC_TRNS,       KC_TRNS,                 MO(_L2),        KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS
  ),
/*  ________      ________      ________      ________      ________                 ________              ________                ________                  ________                 ________      ________      ________      ________   ________      ________
*   ________      TG(_L1)       ________      ^             @                        "                     [                       ]                         %                        A(TAB)             HOME          UP            END        ________      ________
*   ________      ________      ________      ________      ä                        ß/alt                 |/Shift                 $/Ctrl                    +                        HOME          LEFT          DOWN          RGHT       END           ________
*   ________      ________      ________      ________      TD(TD_TICK)              CIRC                  TD(TD_CUR)              ALGR(0)                   S(RBRC)                  ESC           ENT           DEL           BSP        ________      Home/Shift
*   ________      ________      ________      ________      WIN                      Del/Alt                  TG(1)                ________                  ________                 ________      ________      ________      ________   ________      ________
*/
[2] = LAYOUT_planck_mit(
                                           TD(TD_CIRCUM),  ALGR(KC_Q),            S(KC_2),                 ALGR(KC_8),             ALGR(KC_9),              KC_PERC,                A(KC_TAB),      KC_HOME,        KC_UP,    KC_END,   A(S(KC_TAB)),     KC_BSPC,
                                                 KC_TRNS,     KC_QUOT,    MT(MOD_LALT,KC_MINS),       TD(TD_PIPE_SFT),         TD(TD_DOL_CTL),              KC_RPRN,                  KC_HOME,      KC_LEFT,      KC_DOWN,    KC_RGHT,        KC_END,     KC_TRNS,
                                                 KC_TRNS, TD(TD_TICK),                 KC_CIRC,            ALGR(KC_7),             ALGR(KC_0),              KC_RBRC,                   KC_ESC,      KC_ENT,        KC_DEL,    KC_BSPC,       KC_TRNS,     KC_TRNS,
                                                 KC_TRNS,     KC_LGUI,     MT(MOD_LALT,KC_DEL),               KC_TRNS,                MO(_L1),              KC_TRNS,                                KC_TRNS,      KC_TRNS,    KC_TRNS,       KC_TRNS,     KC_TRNS
  ),

/* L3
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |  F1  | Reset|AutoS | RGB  |RGBMOD| HUE+ | HUE- |lclick| ms-u |rclick|ms-w+ | ASTG |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F2  |  F5  |ACCEL0|ACCEL1|ACCEL2| SAT+ | SAT- | ms-l | ms-d | ms-r |ms-w- |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F3  |  F6  |  F8  |  F10 |  F12 |BRGTH+|BRGTH-|lclick|mclick|rclick|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F4  |  F7  |  F9  |  F11 |      |             |      |      |      |      | ALT  |
 * `-----------------------------------------------------------------------------------'
 * 
 */
[3] = LAYOUT_planck_mit(
    KC_F1, RESET,             DEBUG,      RGB_TOG,       RGB_MOD, RGB_HUI, RGB_HUD, KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,   KC_MS_WH_UP,               KC_ASTG,
    KC_F2, KC_F5,      KC_MS_ACCEL0, KC_MS_ACCEL1,  KC_MS_ACCEL2, RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT, KC_MS_WH_DOWN,               KC_TRNS,
    KC_F3, KC_F6,             KC_F8,       KC_F10,        KC_F12, RGB_VAI, RGB_VAD, KC_MS_BTN1,  KC_MS_BTN2,   KC_MS_BTN3,       _______,               _______,
    KC_F4, KC_F7,MT(MOD_LALT,KC_F9),       KC_F11,       _______, _______,             _______,     _______,      _______,       _______,  MT(MOD_RALT, KC_RGHT)
)
,

/* L4
 */
[_L4] = LAYOUT_planck_mit(
    KC_TRNS,         TD(TD_1),               TD(TD_2),       TD(TD_3),              TD(TD_10),       KC_SLSH,     KC_EXLM,     KC_LBRC,        CTLSFTF,       KC_MINS,        KC_PSCR,       KC_TRNS,
    KC_TRNS,         TD(TD_4),               TD(TD_5),       TD(TD_6),               TD(TD_0),        KC_DOT,     KC_UNDS,   PICKFIRST,        PICK2ND,       PICK3RD,        KC_LALT,       KC_TRNS,
    KC_TRNS,         TD(TD_7),               TD(TD_8),       TD(TD_9),              TD(TD_12),       KC_COMM,  S(KC_RBRC),     KC_COMM,     KC_MS_BTN2,       KC_LGUI,        KC_VOLU,       KC_TRNS,
    KC_TRNS,          KC_TRNS,      MT(MOD_LALT,KC_0),        KC_TRNS,                KC_TRNS,       KC_TRNS,                  KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_VOLD,       KC_TRNS
  ),    

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _L1, _L2, _L3);
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
  rgb_matrix_set_color_all(RGB_YELLOW);
  }
//  if (!mods) {
//    println("Oneshot locked mods off");
//  }
}


/* delete or get working
void oneshot_layer_changed_user(uint8_t layer) {
    active_osl = layer;
    if (!layer) {
        // deregister OSL here  println("Oneshot layer off");
  }
}
*/

/* COMBOS will deaktivate Autoshift 
const uint16_t PROGMEM altf4_combo[] = {TD(TD_TAB_ENT), KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM re_combo[] = {KC_R, KC_E, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(altf4_combo, KC_F),
    COMBO(re_combo, LALT(KC_F4))
}; 
*/