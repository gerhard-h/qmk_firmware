/* Copyright 2021 gerhard-h
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
#include "keymap_german.h"

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
rgb_matrix_set_color_all(0,1,60);
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
    CIRCUMFL,
    TICKTICK,
};

/*static bool is_alt_tab_active = false;
static uint16_t alt_tab_timer = 0;*/
typedef struct {
    uint16_t key_hold_timer;
    bool is_key_hold_active;
    uint16_t key_hold_keycode;
    uint16_t key_tap_keycode;
    bool permit_up;
} key_hold_data_t;


// each key needs its own set of status variables
#define HOLD_STAT_USER 10   // ATTENTION adjust array bounds
static key_hold_data_t hold_array[HOLD_STAT_USER] = {0};
static uint16_t key_hold_lastkey = 0;
static uint16_t key_hold_dbltap_timer = 0;                                          
static int hold_active_array[HOLD_STAT_USER];
static int hold_active_max = -1;
void hold_active_clear_at(int index) {
        for(int i = index; i < hold_active_max; i++) {
               hold_active_array[i] = hold_active_array[i+1];
        }
        hold_active_max--;
        if (hold_active_max < -1) hold_active_max = -1;
}
void hold_active_clear(int hold_active_index) {
        for(int i = 0; i <= hold_active_max; i++) {
               if(hold_active_array[i] == hold_active_index) hold_active_clear_at(i);
        }
}
void hold_active_add(int index) {
        hold_active_max++;
        hold_active_array[hold_active_max] = index;
}
void matrix_scan_user(void) {
        // instead of a for loop over all status, processing is improved by putting is_key_hold_active indices in a list and only iterate over that
        // control variables: hold_active_array [10] because number of fingers  or HOLD_STAT_USER,  int hold_active_max (highest used element of list)
        // add: 1. hold_active_max++ 2. hold_active_array[hold_active_max] = me_pointer   
        // clear: 1. find_me in hold_active_array shift higher array elements one index down 2. hold_active_max--  
        // 2a. find_me in matrix_scan_user is obvious because we are in an hign to low loop of hold_active_array
        // 2a. find_me in process_record_hold_key: linear search in hold_active_array
        // instead of &hold_array[1] process_record_hold_key  should use the index
        
        for (int j=hold_active_max; j >= 0; j--){
             int i = hold_active_array[j];
             if (timer_elapsed(hold_array[i].key_hold_timer) > TAPPING_TERM) {
                   if (hold_array[i].permit_up == true)  {  // todo check if permit_up is needed to prevent autorepeat
                       hold_array[i].is_key_hold_active = false;
                       hold_active_clear_at(j); 
                       if (hold_array[i].key_tap_keycode == key_hold_lastkey) {
                               if (timer_elapsed(key_hold_dbltap_timer) < (2 * TAPPING_TERM)) {
                                        tap_code16(hold_array[i].key_tap_keycode); //todo timer with reset here and in process_record_hold_key missing
                               } else {
                                        tap_code16(hold_array[i].key_hold_keycode);
                               }
                       } else {                               
                               tap_code16(hold_array[i].key_hold_keycode);
                       }
                       key_hold_lastkey = hold_array[i].key_tap_keycode;
                       hold_array[i].permit_up = false;
                   }
               }   
        }
}

bool process_record_hold_key(uint16_t keycode, keyrecord_t *record, uint16_t keycode2, int hold_status ){
    if (record->event.pressed) {
                hold_array[hold_status].key_tap_keycode =  keycode;
                if (get_mods() | get_oneshot_mods()) { // If key was held ans no mods
                        hold_array[hold_status].key_hold_keycode =  keycode;
                } else {                       
                        hold_array[hold_status].key_hold_keycode = keycode2;
                }
                key_hold_dbltap_timer = timer_read();
                hold_array[hold_status].key_hold_timer = timer_read();  // start the timer
                hold_array[hold_status].is_key_hold_active = true;
                hold_active_add(hold_status);
                hold_array[hold_status].permit_up = true;
                return false;              // return false to keep keycode from being sent yet
        } else { 
                if (timer_elapsed(hold_array[hold_status].key_hold_timer) > TAPPING_TERM) { // If key was held and no mods
                        key_hold_lastkey = keycode2;
                        //unregister_code16(hold_status->key_hold_keycode);
                        hold_array[hold_status].is_key_hold_active = false;
                        hold_active_clear(hold_status);
                } else if (hold_array[hold_status].is_key_hold_active){                       
                        tap_code16(keycode);// if key was tapped
                        key_hold_lastkey = keycode;
                        hold_array[hold_status].is_key_hold_active = false;
                        hold_active_clear(hold_status);
                }
                hold_array[hold_status].permit_up = false;
                return false;
    	}    
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if ((key_hold_lastkey != keycode) || (timer_elapsed(key_hold_dbltap_timer) > (2 * TAPPING_TERM))) key_hold_lastkey = KC_NO;
    switch (keycode) {
    // this is an alternate key on hold feature case KC_A...KC_Z:
    // keys have no autorepeat
    case KC_P: return process_record_hold_key(keycode, record, A(C(KC_RBRC)), 0);	break;
    case KC_J: return process_record_hold_key(keycode, record, KC_PERC, 1);	break;
    case KC_R: return process_record_hold_key(keycode, record, A(C(KC_9)), 2);	break;
    case KC_B: return process_record_hold_key(keycode, record, KC_RBRC, 3);	break;
    case KC_T: return process_record_hold_key(keycode, record, S(KC_9), 4);	break;
    case KC_F: return process_record_hold_key(keycode, record, S(KC_4), 5);	break;
    case KC_G: return process_record_hold_key(keycode, record, KC_RPRN, 6);	break;
    case KC_D: return process_record_hold_key(keycode, record, A(C(KC_NUBS)), 7);	break;
    case KC_S: return process_record_hold_key(keycode, record, KC_MINS, 8);	break;
    case KC_H: return process_record_hold_key(keycode, record, KC_UNDS, 9);	break;
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
            tap_code(KC_UP);tap_code(KC_RGHT);tap_code(KC_ENT);
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
    case CIRCUMFL:
        if (record->event.pressed) {
            if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {tap_code16(S(KC_GRV)); break;}
            tap_code(KC_GRV);
            tap_code(KC_SPC);
            break;
        }
        break;
    case TICKTICK:
        if (record->event.pressed) {
            if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
                tap_code16(S(KC_EQL));}
            else {
                tap_code(KC_EQL);
            }
            tap_code(KC_SPC);
            break;
        }
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
/*general td state evaluation*/
td_state_t mod_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // ignore interrupted,
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


//individual Tap Dance Declarations
enum {
  TD_A_UML,
  TD_O_UML,
//  TD_F,
  TD_U_UML,
//  TD_SS_UML,
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
//  TD_HASH,
  TD_Q,
  TD_TAB_ENT,
  TD_M,
//  TD_H,
  TD_Z,
  TD_Y,
  TD_X,
  TD_C,
  TD_V,
//  TD_B,
//  TD_G,
//  TD_J,
  TD_W,
  TD_N,
//  TD_D,
  TD_E,
  TD_L,
  TD_ESC,
  TD_DEL10,
//  TD_R,
//  TD_P,
//  TD_T,
  TD_BSP,
};

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
                 tap_code16(keycode3);
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
//general reset function 
void atap_state_reset (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

// ö ä oo~200 aa~600 uu~50 vakuum 
/* DOUBLE_TAP should behave like 2 x SINGLE_TAP and Shift(SINGLE_HOLD) is allowed to get upper case Ä Ö other modifiers not */
void dance_hold_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    if (state->count > 1) tap_code16(keycode);
};
void dance_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;        // normal
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;      // hold
    switch (atap_state.state) {
        case TD_SINGLE_TAP: tap_code16(keycode); break;
        case TD_SINGLE_HOLD:
             if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
             tap_code16(keycode2); break;
        default: tap_code16(keycode); break;
    }
}

// 1-9
/*for when DOUBLE_TAP should behave like TD_DOUBLE_SINGLE_TAP but modifiers are allowed */
void dance_holdwmod_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;        // normal
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;      // hold
    switch (atap_state.state) {
        case TD_SINGLE_TAP: tap_code16(keycode); break;
        case TD_SINGLE_HOLD:
             //if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
             tap_code16(keycode2); break;
        default: tap_code16(keycode); break;
    }
}

/* i \ /, z ! C(z),... lost words: eineiige unparteiische variieren ~ 50 words; jazz piazza skizzen bizzar kreuzzug kurzzeitig zzgl. ~ 100
alternativvorschlag ~ 5 words; 
* for when SINGLE_TAP, SINGLE_HOLD, DOUBLE_TAP should all behave different and  DOUBLE_TAP equals DOUBLE_HOLD*/
void dance_dbltap_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;        //normal
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;      //shifted = single hold
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;      //double hold and double tap
    switch (atap_state.state) {
        case TD_SINGLE_HOLD:
             //if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL )) {tap_code16(keycode); break;} //was there a reason to exclude shift ... yes ü ... put a mod mask in userdata vs di$erent$inished functions 
             if (get_mods() | get_oneshot_mods()) {tap_code16(keycode); break;}
             tap_code16(keycode2); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_HOLD: tap_code16(keycode3); break;
        case TD_SINGLE_TAP:
        default: tap_code(keycode); break; // reuse modifier_dbldance_each toget the missing taps
    }
}

// bsp end bsp bsp... ERRROR it is still sending SFT+Del instead of DEL
void dance_holdautorepeat_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    uint8_t shifts = get_mods() & MOD_MASK_SHIFT;
    uint8_t osshifts = get_oneshot_mods() & MOD_MASK_SHIFT;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD:
                register_code16(keycode2); break;
        case TD_SINGLE_TAP:
        default: 
             if (shifts) del_mods(shifts);
             if (osshifts) del_oneshot_mods(osshifts);
             if (shifts | osshifts){
                 register_code16(keycode3);
             } else {
                 register_code16(keycode);
             }
             if (shifts) register_mods(shifts);
             // no reset for one shot mods
             break;
    }
}
void dance_holdautorepeat_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3; 
    uint8_t shifts = get_mods() & MOD_MASK_SHIFT;
    uint8_t osshifts = get_oneshot_mods() & MOD_MASK_SHIFT;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(keycode2); break;
        default: 
             if (shifts) del_mods(shifts);
             if (osshifts) del_oneshot_mods(osshifts);
             if (shifts | osshifts){
                 unregister_code16(keycode3);
             } else {
                 unregister_code16(keycode);
             }
             if (shifts) register_mods(shifts);
             break;
    }
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

// mod tap as tap dance only these functions need individual state variables
static td_tap_t dance_ctl = {
    .is_press_action = true,
    .state = TD_NONE
};
static td_tap_t dance_sft = {
    .is_press_action = true,
    .state = TD_NONE
};
void dance_mod_finished(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    td_tap_t *ctap_state = (keycode2 == KC_LSFT) ? &dance_sft : &dance_ctl; 
    ctap_state->state = cur_dance(state);
    switch (ctap_state->state) {
        case TD_SINGLE_TAP: register_code16(keycode); break;
        case TD_SINGLE_HOLD: register_code16(keycode2); break;        
        default: register_code16(keycode); break;
    }
}

void dance_mod_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    td_tap_t *ctap_state = (keycode2 == KC_LSFT) ? &dance_sft : &dance_ctl;
    switch (ctap_state->state) {
        case TD_SINGLE_TAP: unregister_code16(keycode); break;
        case TD_SINGLE_HOLD: unregister_code16(keycode2); break;
        default: unregister_code16(keycode); break;
    }
    ctap_state->state = TD_NONE;
}

// mod tap as dbl tap dance kk~220
static td_tap_t ctap_state_dbl = {
    .is_press_action = true,
    .state = TD_NONE
};
static td_tap_t atap_state_dbl = { 
    .is_press_action = true,
    .state = TD_NONE
};
void modifier_dbldance_finished (qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    /* selecting the state based on the keycode works fine, as
    * long as that modifier/dance_function combination is just used once */
    td_tap_t *ctap_state = (keycode2 == KC_LALT) ? &atap_state_dbl : &ctap_state_dbl; 
    ctap_state->state = mod_dance(state);
    switch (ctap_state->state) {
        case TD_SINGLE_HOLD: register_code16(keycode2); break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: tap_code16(keycode3); break;
        default: register_code(keycode); break;
    }
}
void modifier_dbldance_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    if (state->count > 2) {
            tap_code(keycode);
    }
    if (state->count == 3) {
            tap_code(keycode);
    }
};
void modifier_dbldance_reset (qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    td_tap_t *ctap_state = (keycode2 == KC_LALT) ? &atap_state_dbl : &ctap_state_dbl;
    switch (ctap_state->state) {
        case TD_SINGLE_HOLD: unregister_code16(keycode2); break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: break;
        default: unregister_code(keycode); break;
    }
    ctap_state->state = TD_NONE;
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


// Tap Dance definitions - look at the _finished functions names to know what is happening
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_ESC, KC_HOME, KC_GRV})), //tap (tripple tap hold for AutoRepeat), hold (with AR), double_hold (without AR), shift passthrough
    [TD_Q] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_Q, KC_END, A(C(KC_Q))})), // tap, hold, double_tap 
    //[TD_F] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_F, S(KC_4)})), // tap, hold
    [TD_X] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_X, S(KC_6), C(KC_X)})),
    [TD_C] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_C, C(KC_C), A(C(KC_7)), A(C(KC_0))})), // tap, double tap key or KC_NO for 2xtap, hold, double_hold autoclose for "" '' () []...
    [TD_V] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_V, A(C(KC_0)), C(KC_V)})),
    [TD_Y] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_Z, C(KC_Z), C(KC_Z)})),
    [TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_Y, KC_EXLM,  C(KC_Y)})),
    //[TD_G] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_G, KC_RPRN})),
    //[TD_B] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_B, KC_RBRC})),
    [TD_M] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_M, S(KC_RBRC), S(KC_RBRC)})),
    //P J R B are disabled to free up space in this array
    //[TD_J] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_J, KC_PERC, KC_PERC})),
    [TD_U_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_U, KC_LBRC})),
    [TD_A_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_A, KC_QUOT})),
    [TD_O_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_O, KC_SCLN})),
    //[TD_R] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_R, A(C(KC_9))})),
    //[TD_P] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_P, A(C(KC_RBRC))})),
    //[TD_T] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_T, S(KC_9)})),
    //[TD_SS_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_S, KC_MINS})),
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_DOT, S(KC_DOT), S(KC_NUBS)})),  // tap(repeated on tripple tap), hold(repeated), double_hold (not repeated)
    [TD_DASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_SLSH, S(KC_SLSH), S(KC_7)})),
    [TD_I_BS] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_I, A(C(KC_MINS)), S(KC_7)})),
    [TD_DOL_CTL] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_mod_finished, dance_mod_reset, &((dance_user_data_t){S(KC_4), KC_LCTL})), // only one KC_LCTL and KC_LSFT definition are currently supported
    [TD_PIPE_SFT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_mod_finished, dance_mod_reset, &((dance_user_data_t){A(C(KC_NUBS)), KC_LSFT})),
   // unused because of bug [TD_KOE_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_K, KC_LALT, A(KC_TAB)})),// only one KC_LALT and KC_LCTL definition are currently supported
    [TD_ANG] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_NUBS, S(KC_NUBS)})),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_NUHS), S(KC_NUHS)})),
    [TD_PAR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_8), S(KC_9)})),
    [TD_CUR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){A(C(KC_7)), A(C(KC_0))})),
    [TD_COMM] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished,  atap_state_reset, &((dance_user_data_t){KC_COMM, S(KC_COMM), KC_NUBS})),
    [TD_W] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_W, KC_NO, KC_AT, KC_AT})),
    [TD_L] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_L, KC_NO, S(KC_NUHS), S(KC_NUHS)})),
    [TD_E] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_E, KC_NO, A(C(KC_8)), A(C(KC_9))})),
    //[TD_D] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_D, A(C(KC_NUBS))})),
    [TD_N] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_N, KC_NO, S(KC_8), S(KC_9)})),
    [TD_1] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_1, KC_F1})),
    [TD_2] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_2, KC_F2})),
    [TD_3] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_3, KC_F3})),
    [TD_4] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_4, KC_F4})),
    [TD_5] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_5, KC_F5})),
    [TD_6] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_6, KC_F6})),
    [TD_7] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_7, KC_F7})),
    [TD_8] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_8, KC_F8})),
    [TD_9] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_9, KC_F9})),
    [TD_0] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_0, KC_F11})),
    [TD_12] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_1, KC_F12})),
    [TD_10] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){A(C(KC_E)), KC_F10})),
    [TD_DEL10] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_DEL, KC_F10})),
    [TD_TAB_ENT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_TAB, KC_LCTL, KC_ENT})),
//    [TD_H] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_H, KC_UNDS, KC_UNDS})),
    [TD_DQUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_AT, KC_AT})),
    [TD_SQU] = ACTION_TAP_DANCE_FN_ADVANCED_USER(curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){A(C(KC_8)), A(C(KC_9))})),
    [TD_BSP] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdautorepeat_finished, dance_holdautorepeat_reset, &((dance_user_data_t){KC_BSPC, KC_END, KC_DEL})),
};
/*
 tapdance usage before custom  
 23 x hold (autosymbol),
 11 x hold+dbltap,
  3 x hold+dbltap+dblhold,
  5 x hold+dblhold (autoclose),
6(4)x hold (autoclose),
  2 x mod_tap emulation with shifted keycode,
  2 x mod_tap emulation with extra double tap,
==============================================
 52(50) keys pysical keys 47

* ` backtick is only available as Shift(tick) on L2
* # is only available on L1
* 
now 9 x custom single_hold solution rjpsdfgtb
some numbers 12347891 could also get a custom solution with different modifier handling 
äüö behave similar to these numbers
*
* u h have will do/loose the same on dbltap and hold,  Auufer Buchhalter nachher 
*
* shift + backspace > delete not working (sends SFT(KC_DEL))
*
* h and u will now work on dbltap in Auufer, Buchhalter, nachher,... 
*
* / is most inconvinient frequent symbol: h=/ p=? --hold=~
*
* tap and single-hold for r p j b t s d f g h  is not realized by tap dance, but in matrix_scan_user and process_record_user because tap_dance array overflows
* DBL_TAP_HOLD is handled as SINGLE_TAP if modifiers are active SHIFT + r_hold > R instead of S(])
* DBL_TAP_HOLD is autocorreted to bb pp rr tt  instead of b+ p~ r] t)
*
* TAP Dance Problems/Inconsistencies
* DBL_TAP_HOLD m has autorepeat **** but DBL_TAP_HOLD * has no autorepeat
* DBL_TAP_HOLD bsp has autorepeat
* shift + SINGLE_HOLD n > (,
* shift + KOMMA > > instead of < modifies the wrong key 
* BUT shift + SINGLE_HOLD i > I, 
* shift + SINGLE_HOLD q > Q instead of S(END)
* Ä Ü Ö  works only shift neeeds to be passed through
* shift + SINGLE_HOLD . > correct >
* shift + SINGLE_HOLD - > correct /
* alt + hold_4  works
* F10-12 only on L4 not L1 hold r = F10 instead of DELETE/€, F11 instead of 0  is sometimes confusing
*
* ESC/Home BSP/End needs all mods passed through 
*
* _each and _reset funtions are often the same and therefore shared between declarations
* 
* dbl tap esc does not sends ^ not even as dead key instead of custom key CIRCUMFL dance_dbltap_ could check "is keycode element of enum custom_keycodes?" than call that code
*
* light_control if OSM(modifier) is locked
* light intensity controls are inactive -> search solution in oryx keymap code
*
* shift + non shiftable key (e.g. A(C(KC_E))) outputs shift+€=nothing instead of ignoring the shift, but ignoring the shift in general does not work either
* 
* (bug) dance_mod_finished mods must be pressed one after the other > workaround swap + and | because + is a not shifted key wich could use MT
*
* (bug) modifier_dbldance_finished when interupted outputs the modifier instead of key. workaround: use MT 
*
* bug tap dance inside OSL only works if OSL key is held down | process_record_user  all OSM set status-flag on down and clear status-flag on up 
* if tap_dance_each senses !status-flag & OSL active: OSL clear, permanent layer move...
* ...tap dance continues ... on tapdance reset layer move 0
* 
* combos - are there use cases? do combos conflict with tap dance
* c lower > enter
* qw = esc better than tapdance qq? ,k > # 
* comma - combos ,q > 1 ,w > 2 ... ,. >  ,- > 
* ,esc > F1 ,q > F2 ,bsp > F12
* comma diacrit opposit ,a > ä ,s > ß ,d > ö ,f > ü
* D = LT(1,KC_D)  
* dot diacrit ., > ä .n > ü .l > ö .- > ß/alt
* dot mix ., > ü .- > ö. ,. .. ä ,- > ß

* home row mods? F, N ~ SFT
*
* reevaluate copy paste undo: xx cc vv zz
* reevaluate alt-tab: kk vs L2z stick to kk
* reevaluate alt-shift-tab: L2p
* reevaluate 1=v on numpad1
* reevaluate del key positioin RSFT L2DOT L1R LALT
* reevaluate q END
*
* feature: single key alt tab {KC_LCTL,KC_LALT,KC_TAB}
* single hold & modus==OFF: alt + ctrl + tab & modus=ON 
* tap & modus==ON: tab
* single hold & modus==ON: modus==ON & Space  
*       
* Alt+F4: Ctl+(W+W) or (C+W)+W or C+(W+Q) or wq
*
*numberpad 2.0
* €456-
* 3210.
* /789,
*
* leader key  combos? are they compatible with tapdance keys? F keys
* always send KC_LEAD after ESC or up ?
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* ESC           PSCR          NO            ESC Home      1             2             3             4             5             6             7             8             9                          0             DEL
*  TO(L0)        TO(L1)        NO            ESC Home      Q End         W             E             R             J             Y             U Ü           I             O Ö                        P             Backspc
*  PgUp          VOLU          NO            TAB/Ctrl      A Ä           S ß           D             F             G             H             N             T             L                          k/Alt atab    Enter/Ctrl
*  PgDn          VOLD          NO            HOME/Shift    Z             X             C             V             B             M             ,             . : *         - _ /                      Up            END/Shift
*  CTL           ALT           NO            PgUp/Ctrl     PgDn/WIN      Del/Alt       Tab/L2        Enter/L1      Space/Shift   Space/Shift   Space/L2      OSL L4        Left                       Down          Right
*/
[0] = LAYOUT_planck_mit(    
                                         TD(TD_ESC),          TD(TD_Q),        TD(TD_W), TD(TD_E),     KC_R,          KC_J, TD(TD_Z),    TD(TD_U_UML),    TD(TD_I_BS),    TD(TD_O_UML),               KC_P,             TD(TD_BSP),
                               MT(MOD_LCTL ,KC_TAB),      TD(TD_A_UML),            KC_S,     KC_D,     KC_F,          KC_G,     KC_H,        TD(TD_N),           KC_T,        TD(TD_L),     MT(MOD_LALT, KC_K),    MT(MOD_LCTL,KC_ENT),
                                      OSM(MOD_LSFT),          TD(TD_Y),        TD(TD_X), TD(TD_C), TD(TD_V),          KC_B, TD(TD_M),     TD(TD_COMM),     TD(TD_DOT),     TD(TD_DASH),              KC_UP,    MT(MOD_LSFT,KC_DEL),
                              MT(MOD_LCTL, KC_PGUP),           KC_LGUI,
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

                                                         KC_TRNS,         TD(TD_1),             TD(TD_2),                    TD(TD_3),          TD(TD_DEL10),       KC_BSPC,     KC_EXLM,    KC_LBRC,        DE_BSLS,       KC_SCLN,        DE_TILD,       KC_TRNS,
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
                                                CIRCUMFL,  ALGR(KC_Q),            TD(TD_DQUOT),            TD(TD_SQU),             ALGR(KC_9),              KC_PERC,                A(KC_TAB),      KC_HOME,        KC_UP,    KC_END,   A(S(KC_TAB)),     KC_BSPC,
                                                 KC_TRNS,     KC_QUOT,    MT(MOD_LALT,KC_MINS),       TD(TD_PIPE_SFT),         TD(TD_DOL_CTL),              KC_RPRN,             A(S(KC_TAB)),      KC_LEFT,      KC_DOWN,    KC_RGHT,       KC_PGDN,     KC_TRNS,
                                                 KC_TRNS,    TICKTICK,                 KC_CIRC,            TD(TD_CUR),             ALGR(KC_0),              KC_RBRC,                   KC_ESC,      KC_ENT,        KC_DEL,    KC_BSPC,       KC_TRNS,     KC_TRNS,
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
    KC_F1, RESET,             DEBUG,      RGB_TOG,       RGB_MOD, RGB_HUI, RGB_HUD, KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,   KC_MS_WH_UP,               CMB_TOG,
    KC_F2, KC_F5,      KC_MS_ACCEL0, KC_MS_ACCEL1,  KC_MS_ACCEL2, RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT, KC_MS_WH_DOWN,               KC_TRNS,
    KC_F3, KC_F6,             KC_F8,       KC_F10,        KC_F12, RGB_VAI, RGB_VAD, KC_MS_BTN1,  KC_MS_BTN2,   KC_MS_BTN3,       _______,               _______,
    KC_F4, KC_F7,MT(MOD_LALT,KC_F9),       KC_F11,       _______, _______,             _______,     _______,      _______,       _______,  MT(MOD_RALT, KC_RGHT)
)
,

/* L4
 */
[_L4] = LAYOUT_planck_mit(
    KC_TRNS,         TD(TD_1),               TD(TD_2),       TD(TD_3),              TD(TD_10),   TD(TD_DASH),     KC_EXLM,     KC_LBRC,        CTLSFTF,       KC_MINS,        KC_PSCR,       KC_TRNS,
    KC_TRNS,         TD(TD_4),               TD(TD_5),       TD(TD_6),               TD(TD_0),    TD(TD_DOT),     KC_UNDS,   PICKFIRST,        PICK2ND,       PICK3RD,        KC_LALT,       KC_TRNS,
    KC_TRNS,         TD(TD_7),               TD(TD_8),       TD(TD_9),              TD(TD_12),   TD(TD_COMM),  S(KC_RBRC),     KC_COMM,     KC_MS_BTN2,       KC_LGUI,        KC_VOLU,       KC_TRNS,
    KC_TRNS,          KC_TRNS,      MT(MOD_LALT,KC_0),        KC_TRNS,                KC_TRNS,       KC_TRNS,                  KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_VOLD,       KC_TRNS
  ),    

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _L1, _L2, _L3);
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
  //if (mods & MOD_MASK_SHIFT) {
  rgb_matrix_set_color_all(RGB_YELLOW);
  //}
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

/* COMBOS will deaktivate Autoshift not complex Tapdances also break it
tap dance callbacks fireing on default might be a Problem
{KC_LEFT, KC_RGHT, COMBO_END} works
{TD(TD_COMM), TD(TD_A_UML), COMBO_END}; , > k, ,a > ,fa comma_hold > ;kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
TD(TD_H), KC_R  > 4hr  4 = unsc4hift F$
TD(TD_U_UML), TD(TD_O_UML) uao 

interesting:
With #define COMBO_ONLY_FROM_LAYER _LAYER_A the combos' keys are always checked from layer _LAYER_A even though the active layer would be _LAYER_B.

using autohotkey
; eventmethode (se) plus raw()) (ist compatible mit qmk firmware
#Hotstring se
:*:,a::ä
:*:;A::Ä
:*:,s::ß
:*:,u::ü
:*:,o::ö
:*:,f::$

const uint16_t PROGMEM altf4_combo[] = {TD(TD_KOE_ALT), TD(TD_A_UML), COMBO_END};
const uint16_t PROGMEM re_combo[] = {TD(TD_U_UML), TD(TD_O_UML), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(altf4_combo, KC_F),
    COMBO(re_combo, KC_A)
}; */
