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
rgb_matrix_set_color(7, 150, 150, 50); // ue oe
rgb_matrix_set_color(9, 150, 150, 50); // oe
break;
case 2:
rgb_matrix_set_color_all(0,1,60);
rgb_matrix_set_color(12, 150, 150, 50); // ä
rgb_matrix_set_color(13, 150, 150, 50); // ß
rgb_matrix_set_color(8, 150, 150, 50); // nav
rgb_matrix_set_color(19, 150, 150, 50); // nav
rgb_matrix_set_color(20, 150, 150, 50); // nav
rgb_matrix_set_color(21, 150, 150, 50); // nav
rgb_matrix_set_color(30, 150, 150, 50); // esc
break;
case 3:
rgb_matrix_set_color_all(0,1,30); 
rgb_matrix_set_color(12, 150,100,10); 
rgb_matrix_set_color(13, 150,100,10); 
rgb_matrix_set_color(22, 150,100,10); 
rgb_matrix_set_color(23, 150,100,10); 
rgb_matrix_set_color(24, 150,100,10); 
rgb_matrix_set_color(32, 150,100,10); 
rgb_matrix_set_color(33, 150,100,10); 
rgb_matrix_set_color(34, 150,100,10); 
rgb_matrix_set_color(35, 150,100,10); 
rgb_matrix_set_color(42, 150,100,10); 
rgb_matrix_set_color(43, 150,100,10); 
rgb_matrix_set_color(44, 150,100,10); 


break;
case 4:
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
rgb_matrix_set_color(17, 150, 150, 50); // makro
rgb_matrix_set_color(18, 150, 150, 50);
rgb_matrix_set_color(19, 150, 150, 50);
rgb_matrix_set_color(11, 150, 150, 50); // volume
rgb_matrix_set_color(21, 150, 150, 50);
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
    L0AUTOS
};

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
        
    case L0AUTOS:
        layer_move(_L0);
#       ifdef AUTO_SHIFT_ENABLE
            autoshift_enable();
#       endif
        break;
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
} dance_user_data_t;

//shared tapstate
static td_tap_t atap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
static uint8_t active_osl = 0; //for OSL tap dance

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
  TD_DQUOT,
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
  TD_HASH,
  TD_Q
};


LEADER_EXTERNS();
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

// ^ °
void circum_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("` "); break;
        case TD_SINGLE_HOLD:
            SEND_STRING("~"); break;
        default: 
            for (uint8_t i=0; i < state->count; i++) {
                SEND_STRING("` ");
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
            for (uint8_t i=0; i < state->count; i++) {
                SEND_STRING("= ");
            };
        break;
    }
}
void tick_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

// () <> {} [] "" '' ...
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
    	reset_oneshot_layer();
    	layer_move(_L2);
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
    //layer_move(0);
}

// ö ß
/*for when DOUBLE_TAP should behave like TD_DOUBLE_SINGLE_TAP */
void dance_norepeat_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;        //normal and double tap
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;      //shifted
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;      //double hold
    switch (atap_state.state) {
        case TD_SINGLE_TAP: tap_code(keycode); break;
        case TD_SINGLE_HOLD:
#            ifdef AUTO_SHIFT_ENABLE
                 if (get_autoshift_state()) {
                     tap_code16(keycode2); break;
                 }
#            endif
             tap_code(keycode); break;
        case TD_DOUBLE_HOLD: tap_code16(keycode3); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default: 
            for (uint8_t i=0; i < state->count; i++) {
                tap_code(keycode);
            };
        break;
    }
}
void dance_norepeat_reset(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

// ä ü
/*for when DOUBLE_TAP should behave like TD_DOUBLE*/
void dance_norepeatdt_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;        //normal
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;      //shifted
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;      //double hold and double tap
    switch (atap_state.state) {
        case TD_SINGLE_TAP: tap_code(keycode); break;
        case TD_SINGLE_HOLD:
#            ifdef AUTO_SHIFT_ENABLE
                 if (get_autoshift_state()) {
                     tap_code16(keycode2); break;
                 }
#            endif
             tap_code(keycode); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
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
void dance_norepeatdt_reset(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

// ::: *** /// ...... ------ ____
void dance_autorepeat_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (atap_state.state) {
        case TD_SINGLE_TAP: register_code16(keycode); break;
        case TD_SINGLE_HOLD: register_code16(keycode2); break;
        case TD_DOUBLE_HOLD: register_code16(keycode3); break;
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
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (atap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(keycode); break;
        case TD_SINGLE_HOLD: unregister_code16(keycode2); break;
        case TD_DOUBLE_HOLD: unregister_code16(keycode3); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: 
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default: unregister_code16(keycode); break;
    }
    atap_state.state = TD_NONE;
}


// "ii" -> "\"
void dance_iuml_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_I); break;
        case TD_SINGLE_HOLD:
#            ifdef AUTO_SHIFT_ENABLE
                 if (get_autoshift_state()) {
                     tap_code16(S(KC_I)); break;
                 }
#            endif
             tap_code(KC_I); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_HOLD: tap_code16(ALGR(KC_MINS)); break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:tap_code16(ALGR(KC_MINS));tap_code16(ALGR(KC_MINS)); break;
        default: break;
    }
}
void dance_iuml_reset(qk_tap_dance_state_t *state, void *user_data) {
        switch(atap_state.state) {
        case TD_SINGLE_TAP:
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        default:
            break;
    }
    atap_state.state = TD_NONE;
}

// mod tap as tap dance
void modifier_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    switch (atap_state.state) {
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
    switch (atap_state.state) {
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(keycode2)); break;
        default: unregister_code16(keycode); break;
    }
    atap_state.state = TD_NONE;
}

// mod tap as dbl tap dance
void modifier_dbldance_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(keycode2)); break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:register_code(keycode3); break;
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
    switch (atap_state.state) {
        case TD_SINGLE_HOLD: unregister_mods(MOD_BIT(keycode2)); break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: unregister_code(keycode3); break;
        default: unregister_code(keycode); break;
    }
    atap_state.state = TD_NONE;
}


// no autoshift for numbers on the number layer, also # F key instead
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

/*important macro to define userdata */
#define ACTION_TAP_DANCE_FN_ADVANCED_USER(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, user_user_data) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void*)user_user_data, }


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_Q] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeatdt_finished, dance_norepeatdt_reset, &((dance_user_data_t){KC_Q, S(KC_Q), KC_ESC})),
    [TD_F] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeat_finished, dance_norepeat_reset, &((dance_user_data_t){KC_F, S(KC_F), S(KC_4)})),
    [TD_A_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeatdt_finished, dance_norepeatdt_reset, &((dance_user_data_t){KC_A, S(KC_A), KC_QUOT})),
    [TD_O_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeat_finished, dance_norepeat_reset, &((dance_user_data_t){KC_O, S(KC_O), KC_SCLN})),
    [TD_U_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeatdt_finished, dance_norepeatdt_reset, &((dance_user_data_t){KC_U, S(KC_U), KC_LBRC})),
    [TD_SS_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeat_finished, dance_norepeat_reset, &((dance_user_data_t){KC_S, S(KC_S), KC_MINS})),
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_DOT, S(KC_DOT), S(KC_RBRC)})),
    [TD_DASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_SLSH, S(KC_SLSH), S(KC_7)})),
    [TD_CIRCUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, circum_dance_finished, circum_dance_reset),
    [TD_TICK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tick_dance_finished, tick_dance_reset),
    [TD_I_BS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_iuml_finished, dance_iuml_reset),
    [TD_DOL_CTL] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dance_each, modifier_dance_finished, modifier_dance_reset, &((dance_user_data_t){S(KC_4), KC_LCTL})),
    [TD_PIPE_SFT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dance_each, modifier_dance_finished, modifier_dance_reset, &((dance_user_data_t){A(C(KC_NUBS)), KC_LSFT})),
    [TD_KOE_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_K, KC_LALT, KC_SCLN})),
    [TD_PAR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_8), S(KC_9)})),
    [TD_CUR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){A(C(KC_7)), A(C(KC_0))})),
    [TD_SQU] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){A(C(KC_8)), A(C(KC_9))})),
    [TD_ANG] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_NUBS, S(KC_NUBS)})),
    [TD_DQUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_AT, KC_AT})),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_NUHS), S(KC_NUHS)})),
    [TD_HASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER( NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_NUHS, KC_NUHS, KC_NUHS})),
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
};
/*
* todo
* 
* (-) tap dance on lower/raise to lock layer_state_cmp ... but because space and emter are spammable keys 
fake layer tap with extra osl
OSL(num) num TO(sym) sym TG(num) layer3 TO(0)
double tap lock symbol layer double tap for exit
tripple tap lock layer3 single tap for exit
MO(sym) + TG(num) locked num tripple tap for exit
* combos
* qw = esc better than tapdance qq?
* 
* numbers
* vvv = 0
* fff = 1.....
* vvq - vvc = 1 - 9
* home row mods?

leader key  combos? are they compatible with tapdance keys? F keys
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* ESC           PSCR          NO            ESC           1             2             3             4             5             6             7             8             9             0             DEL
*  TO(L0)        TO(L1)        NO            DEL           Q ESC         W             E             R             J             Y             U Ü           I             O Ö           P             Backspc
*  PgUp          VOLU          NO            TAB/Ctrl      A Ä           S ß           D             F             G             H             N             T             L             K/Alt         Enter/Ctrl
*  PgDn          VOLD          NO            HOME/Shift    Z             X             C             V             B             M             ,             . : *         - _ /         Up            END/Shift
*  CTL           ALT           NO            PgUp/Ctrl     PgDn/WIN      Del/Alt       Tab/L2        Enter/L1      Space/Shift   Space/Shift   Space/L2      OSL L4        Left          Down          Right
*/
[0] = LAYOUT_planck_mit(    
                                             KC_DEL,          TD(TD_Q),            KC_W,   KC_E,     KC_R,          KC_J,    KC_Y,    TD(TD_U_UML),    TD(TD_I_BS),    TD(TD_O_UML),               KC_P,                        KC_BSPC,
                               MT(MOD_LCTL ,KC_TAB),      TD(TD_A_UML),   TD(TD_SS_UML),   KC_D, TD(TD_F),          KC_G,    KC_H,            KC_N,            KC_T,           KC_L,     TD(TD_KOE_ALT), MT(MOD_LCTL | MOD_RCTL,KC_ENT),
                                      OSM(MOD_LSFT),              KC_Z,            KC_X,   KC_C,     KC_V,          KC_B,    KC_M,         KC_COMM,      TD(TD_DOT),    TD(TD_DASH),              KC_UP,                  OSM(MOD_RSFT),
                              MT(MOD_LCTL, KC_PGUP), MT(MOD_LGUI, KC_PGDN),
                                                                     MT(MOD_LALT,KC_DEL),
                                                                                 LT(_L4,KC_TAB), 
                                                                                                 OSL(_L1),
                                                                                                                 MT(MOD_LSFT,KC_SPC),
                                                                                                                                          OSL(_L2),         KC_LEAD,        KC_LEFT,            KC_DOWN,                KC_RGHT
 ),
/*            ________      ________      ________      F12           F1            F2            F3            F4            F5            F6            F7            F8            F9            F10           F11
*             ________      TO(_L2)       ________      ________      1             2             3             €             .             !             ü             \             ö             ~             ________
*             ________      ________      ________      ________      4             5             6             0             :             ?             (             )             '             #             ________
*             ________      ________      ________      ________      7             8             9             1             ,             =             <             >             /             ________      ________
*             ________      ________      ________      ________      ________      0/Alt         TO(2)      ________      ________      ________      ________      TG(_L2)          ________      ________      ________
*/
[1] = LAYOUT_planck_mit(

                                                          KC_ESC,         TD(TD_1),             TD(TD_2),                    TD(TD_3),             TD(TD_10),        KC_DOT,  KC_EXLM,    KC_LBRC,  ALGR(KC_MINS),       KC_SCLN,  ALGR(KC_RBRC),       KC_TRNS,
                                                         KC_TRNS,         TD(TD_4),             TD(TD_5),                    TD(TD_6),              TD(TD_0),         KC_GT,  KC_UNDS, TD(TD_PAR),        KC_LPRN,   TD(TD_QUOT),    TD(TD_HASH),       KC_TRNS,
                                                         KC_TRNS,         TD(TD_7),              TD(TD_8),                   TD(TD_9),             TD(TD_12),       KC_COMM,  KC_RPRN, TD(TD_ANG),     S(KC_NUBS),       KC_AMPR,          KC_UP,       KC_TRNS,
                                                         KC_TRNS,          KC_TRNS,     MT(MOD_LALT,KC_0),                      TO(2),               KC_TRNS,       KC_TRNS,              MO(_L2),        TG(_L2),       KC_TRNS,        KC_TRNS,       KC_TRNS
  ),
/*  ________      ________      ________      ________      ________      ________      ________      ________      ________      ________      ________      ________      ________      ________      ________
*   ________      TG(_L1)       ________      ^             @             "             [             ]             %             -             CTL+SFT+F     UP            PSCR          ________      ________
*   ________      ________      ________      ________      ä             ß/alt         |/Shift       $/Ctrl        +             HOME          LEFT          DOWN          RGHT          END           ________
*   ________      ________      ________      ________      TD(TD_TICK)   CIRC          TD(TD_CUR)    ALGR(0)       S(RBRC)       ESC           Backspc       DEL           ENT           ________      Home/Shift
*   ________      ________      ________      ________      WIN           Del/Alt          TG(1)      ________      ________      ________      ________      ________      ________      ________      ________
*/
[2] = LAYOUT_planck_mit(
                                           TD(TD_CIRCUM),  ALGR(KC_Q),            TD(TD_DQUOT),           TD(TD_SQU),              ALGR(KC_9),              KC_PERC,                  KC_SLSH,      CTLSFTF,      KC_UP,      KC_PSCR,      KC_TRNS,      KC_BSPC,
                                                 KC_TRNS,     KC_QUOT,    MT(MOD_LALT,KC_MINS),       TD(TD_PIPE_SFT),         TD(TD_DOL_CTL),              KC_RBRC,                  KC_HOME,      KC_LEFT,      KC_DOWN,    KC_RGHT,      KC_END,       KC_TRNS,
                                                 KC_TRNS, TD(TD_TICK),                 KC_CIRC,            TD(TD_CUR),             ALGR(KC_0),           TD(TD_I_BS),                   KC_ESC,      KC_BSPC,      KC_DEL,     KC_ENT,       KC_TRNS,      MT(MOD_LSFT,KC_HOME),
                                                 KC_TRNS,     KC_LGUI,      MT(MOD_LALT,KC_DEL),              TG(1),              MO(_L2),                KC_TRNS,                                KC_TRNS,      KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS
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
    KC_F1, RESET,             DEBUG,      RGB_TOG,      RGB_MOD, RGB_HUI, RGB_HUD, KC_MS_BTN1,  KC_MS_UP,   KC_MS_BTN2, KC_MS_WH_UP     , KC_ASTG,
    KC_F2, KC_F5,      KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,KC_MS_RIGHT, KC_MS_WH_DOWN, KC_TRNS,
    KC_F3, KC_F6,             KC_F8,       KC_F10,       KC_F12, RGB_VAI, RGB_VAD, KC_MS_BTN1,  KC_MS_BTN2,  KC_MS_BTN3,      _______, _______,
    KC_F4, KC_F7,MT(MOD_LALT,KC_F9),       KC_F11,       _______, _______,             _______, _______,  _______, _______, MT(MOD_RALT, KC_RGHT)
)
,

/* L4
 */
[_L4] = LAYOUT_planck_mit(
    KC_TRNS,         TD(TD_1),               TD(TD_2),       TD(TD_3),              TD(TD_10),        KC_DOT,  KC_EXLM,    KC_LBRC,  ALGR(KC_MINS),       KC_SCLN,  ALGR(KC_RBRC),       KC_TRNS,
    KC_TRNS,         TD(TD_4),               TD(TD_5),       TD(TD_6),               TD(TD_0),         KC_GT,  KC_UNDS,   PICKFIRST,       PICK2ND,       PICK3RD,    TD(TD_HASH),       KC_TRNS,
    KC_TRNS,         TD(TD_7),               TD(TD_8),       TD(TD_9),              TD(TD_12),       KC_COMM,  KC_RPRN,  TD(TD_ANG),    S(KC_NUBS),       KC_AMPR,        KC_VOLU,       KC_TRNS,
    KC_TRNS,          KC_TRNS,      MT(MOD_LALT,KC_0),        KC_TRNS,                KC_TRNS,       KC_TRNS,               KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_VOLD,       KC_TRNS
  ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _L1, _L2, _L3);
}

void oneshot_layer_changed_user(uint8_t layer) {
        active_osl = layer;
}