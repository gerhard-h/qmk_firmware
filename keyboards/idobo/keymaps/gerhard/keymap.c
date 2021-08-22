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
#include "print.h"


// Default LED colors
//uint8_t h = 170;
//uint8_t s = 10;
//uint8_t v;

// default animation
uint8_t rgbMode = RGBLIGHT_MODE_STATIC_LIGHT;

enum layers { _L0 = 0, _L1, _L2, _L3, _L4, _L5 };

// Macros
enum custom_keycodes {
    PICKFIRST = SAFE_RANGE,
    PICK2ND,
    PICK3RD,
    CTLSFTF
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    //uint8_t layer = get_highest_layer(layer_state);

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

void dbg_state(qk_tap_dance_state_t *state) {
        dprintf("count %d", state->count);
        dprintf("timer %d", state->timer);
        dprintf("pressed %d", state->pressed);
        dprintf("finished %d", state->finished);
        dprintf("keycode %d", state->keycode);
}

/*tap dance user_data*/
typedef struct {
    uint16_t keycode;
    uint16_t keycode2;
    uint16_t keycode3;
} dance_user_data_t;


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

// lets find a way to combine mod tap and autoshift
td_state_t mod_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted) return TD_SINGLE_TAP;
        else if (!state->pressed) return TD_DOUBLE_HOLD;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } else return TD_UNKNOWN;
}

//shared tapstate
static td_tap_t atap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

//individual Tap Dance Declarations
enum {
  TD_A_UML,
  TD_O_UML,
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
  TD_H,
  TD_I_BS,
  TD_CIRCUM,
  TD_TICK,
  TD_COMM,
  TD_DOL_CTL,
  TD_PIPE_SFT,
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
  TD_HASH
};

// ^ °
void circum_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("` ");
        break;
        case TD_SINGLE_HOLD:
            SEND_STRING("~");
        default: break;
    }
}
void circum_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}

//´`
void tick_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("= ");
        break;
        case TD_SINGLE_HOLD:
            SEND_STRING("+ "); 
        default: break;
    }
}
void tick_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = TD_NONE;
}


// () <> {} [] ...
void curly_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
     atap_state.state = cur_dance(state);
     uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
     uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code16(keycode);
            tap_code16(keycode2);
            tap_code(KC_LEFT); 
        break;
        default: break;
    }
}
void curly_dance_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    if (state->count > 1) unregister_code16(keycode);
    register_code16(keycode);
};
void curly_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD: break;
        default:
            unregister_code16(keycode);
        break;
    }
    atap_state.state = TD_NONE;
}

// ä ö ü ß
/*for when DOUBLE_TAP should behave like TD_DOUBLE_SINGLE_TAP */
void dance_norepeat_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (atap_state.state) {
        case TD_SINGLE_TAP: tap_code16(keycode); break;
        case TD_SINGLE_HOLD: tap_code16(keycode2); break;
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
void dance_norepeat_reset(qk_tap_dance_state_t *state, void *user_data) {
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
        case TD_SINGLE_TAP: register_code(KC_I); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_I)); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_HOLD: register_code16(ALGR(KC_MINS)); break;
        default: break;
    }
}
void dance_iuml_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (atap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_I); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_I)); break;
        case TD_DOUBLE_TAP: 
        case TD_DOUBLE_HOLD: 
        case TD_DOUBLE_SINGLE_TAP: unregister_code16(ALGR(KC_MINS));
        default: break;
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

// no autoshift for numbers on the number layer, also #
void noshift_fin(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
            for (uint8_t i=0; i < state->count; i++) {
                tap_code16(keycode);
            };
};
void noshift_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    tap_code16(keycode);
};

/*important macro to define userdata */
#define ACTION_TAP_DANCE_FN_ADVANCED_USER(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, user_user_data) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void*)user_user_data, }


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_A_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeat_finished, dance_norepeat_reset, &((dance_user_data_t){KC_A, S(KC_A), KC_QUOT})),
    [TD_O_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeat_finished, dance_norepeat_reset, &((dance_user_data_t){KC_O, S(KC_O), KC_SCLN})),
    [TD_U_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeat_finished, dance_norepeat_reset, &((dance_user_data_t){KC_U, S(KC_U), KC_LBRC})),
    [TD_SS_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_norepeat_finished, dance_norepeat_reset, &((dance_user_data_t){KC_S, S(KC_S), KC_MINS})),
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_DOT, S(KC_DOT), S(KC_RBRC)})),
    [TD_DASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_SLSH, S(KC_SLSH), S(KC_7)})),
    [TD_CIRCUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, circum_dance_finished, circum_dance_reset),
    [TD_TICK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tick_dance_finished, tick_dance_reset),
    [TD_I_BS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_iuml_finished, dance_iuml_reset),
    [TD_DOL_CTL] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dance_each, modifier_dance_finished, modifier_dance_reset, &((dance_user_data_t){S(KC_4), KC_LCTL})),
    [TD_PIPE_SFT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dance_each, modifier_dance_finished, modifier_dance_reset, &((dance_user_data_t){A(C(KC_NUBS)), KC_LSFT})),
    [TD_PAR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_8), S(KC_9)})),
    [TD_CUR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){A(C(KC_7)), A(C(KC_0))})),
    [TD_SQU] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){A(C(KC_8)), A(C(KC_9))})),
    [TD_ANG] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_NUBS, S(KC_NUBS)})),
    [TD_DQUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_AT, KC_AT})),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_NUHS), S(KC_NUHS)})),
    [TD_HASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER( NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_NUHS, KC_NUHS, KC_NUHS})),
    [TD_1] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_1})),
    [TD_2] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_2})),
    [TD_3] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_3})),
    [TD_4] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_4})),
    [TD_5] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_5})),
    [TD_6] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_6})),
    [TD_7] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_7})),
    [TD_8] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_8})),
    [TD_9] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_9})),
    [TD_0] = ACTION_TAP_DANCE_FN_ADVANCED_USER(noshift_each, NULL, NULL, &((dance_user_data_t){KC_0}))
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


* leader key for F1-F12
* tap dance on rsft  cycle layers or leaderkey
* q esc
* , ' "  or , is mod_ctrl
* combos
* qw = esc better than tapdance
* 
* numbers
* vvv = 0
* fff = 1.....
* vvq - vvc = 1 - 9
* home row mods?
. .. : .:hold > * 

-_  --hold > * /

ffhold > $

rsft rsft hold osl makro

*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [0] = LAYOUT_ortho_5x15(
    KC_ESC,      KC_PSCR,        KC_NO,     KC_ESC,          KC_1,            KC_2,           KC_3,           KC_4,          KC_5,    KC_6,            KC_7,           KC_8,            KC_9,               KC_0,                         KC_DEL,
    TO(0),       TO(_L1),        KC_NO,     KC_DEL,          KC_Q,            KC_W,           KC_E,           KC_R,          KC_J,    KC_Y,    TD(TD_U_UML),    TD(TD_I_BS),    TD(TD_O_UML),               KC_P,                        KC_BSPC,
    KC_PGUP,     KC_VOLU,        KC_NO,MT(MOD_LCTL ,KC_TAB), TD(TD_A_UML),   TD(TD_SS_UML),   KC_D,           KC_F,          KC_G,    KC_H,            KC_N,            KC_T,           KC_L,  MT(MOD_LALT,KC_K), MT(MOD_LCTL | MOD_RCTL,KC_ENT),
    KC_PGDN,     KC_VOLD,        KC_NO,MT(MOD_LSFT,KC_HOME), KC_Z,            KC_X,           KC_C,           KC_V,          KC_B,    KC_M,         KC_COMM,      TD(TD_DOT),    TD(TD_DASH),              KC_UP, MT(MOD_LSFT | MOD_RSFT,KC_END),
    KC_LCTL,     KC_LALT,        KC_NO,MT(MOD_LCTL, KC_PGUP), MT(MOD_LGUI, KC_PGDN),
                                                                        MT(MOD_LALT,KC_DEL)
                                                                                         , LT(_L4,KC_TAB), 
                                                                                                        LT(_L1,KC_ENT),
                                                                                                                MT(MOD_LSFT,KC_SPC), MT(MOD_LSFT,KC_SPC),
                                                                                                                                             LT(_L2,KC_SPC),       OSL(_L4),        KC_LEFT,            KC_DOWN,                         KC_RGHT
 ),

 [1] = LAYOUT_ortho_5x15(
    KC_TRNS,     KC_TRNS,        KC_TRNS,       KC_F12,         KC_F1,                    KC_F2,                       KC_F3,                  KC_F4,         KC_F5,    KC_F6,    KC_F7,          KC_F8,         KC_F9,         KC_F10,        KC_F11,
    KC_TRNS,     TO(_L2),        KC_TRNS,       KC_TRNS,      TD(TD_1),                TD(TD_2),                    TD(TD_3),             ALGR(KC_E),        KC_DOT,  KC_EXLM,  KC_LBRC,  ALGR(KC_MINS),       KC_SCLN,  ALGR(KC_RBRC),       KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,       KC_TRNS,         TD(TD_4),              TD(TD_5),                    TD(TD_6),              TD(TD_0),         KC_GT,  KC_UNDS, TD(TD_PAR),        KC_LPRN, TD(TD_QUOT),    TD(TD_HASH),       KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,       KC_TRNS,         TD(TD_7),               TD(TD_8),                   TD(TD_9),               TD(TD_1),       KC_COMM,  KC_RPRN, TD(TD_ANG),     S(KC_NUBS),    KC_AMPR,          KC_UP,       KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,       KC_TRNS,      KC_TRNS,  MT(MOD_LALT,KC_0),                KC_TRNS,                KC_TRNS,       KC_TRNS,  KC_TRNS,  KC_TRNS,                   TG(_L2),       KC_TRNS,        KC_TRNS,       KC_TRNS
  ),

 [2] = LAYOUT_ortho_5x15(
    KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,     KC_TRNS,                 KC_TRNS,              KC_TRNS,                 KC_TRNS,              KC_TRNS,                  KC_TRNS,      KC_TRNS,      KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS,
    KC_TRNS, TG(_L1), KC_TRNS, TD(TD_CIRCUM),  ALGR(KC_Q),            TD(TD_DQUOT),           TD(TD_SQU),              ALGR(KC_9),              KC_PERC,                  KC_SLSH,      CTLSFTF,      KC_UP,      KC_SCLN,      KC_TRNS,      KC_BSPC,
    KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,     KC_QUOT,    MT(MOD_LALT,KC_MINS),       TD(TD_PIPE_SFT),         TD(TD_DOL_CTL),              KC_RBRC,                  KC_HOME,      KC_LEFT,      KC_DOWN,    KC_RGHT,      KC_END,       KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, TD(TD_TICK),                 KC_CIRC,            TD(TD_CUR),             ALGR(KC_0),           S(KC_RBRC),                   KC_ESC,      KC_BSPC,      KC_DEL,     KC_ENT,       KC_TRNS,      KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,     KC_LGUI,      MT(MOD_LALT,KC_DEL),              KC_TRNS,              KC_TRNS,                KC_TRNS,                  KC_TRNS,      KC_TRNS,      KC_TRNS,    KC_TRNS,      KC_TRNS,      KC_TRNS
  ),

 [3] = LAYOUT_ortho_5x15(
    RESET,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,     KC_TRNS,      KC_TRNS,       KC_TRNS,              KC_TRNS,
    KC_TRNS,    TO(_L4), KC_TRNS, KC_F1,     RESET,             DEBUG,      RGB_TOG,      RGB_MOD, RGB_HUI, RGB_HUD, KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,   KC_MS_WH_UP,                TO(0),
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_F2,     KC_F5,      KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT, KC_MS_WH_DOWN,              KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_F3,     KC_F6,             KC_F8,       KC_F10,       KC_F12, RGB_VAI, RGB_VAD, KC_MS_BTN1,   KC_MS_BTN2,  KC_MS_BTN2,    KC_MS_BTN3,              _______,
    KC_ASTG ,   KC_TRNS, KC_TRNS, KC_F4,     KC_F7, MT(MOD_LALT,KC_F9),      KC_F11,       KC_F12, KC_TRNS, KC_TRNS,    KC_TRNS,      KC_TRNS,     KC_VOLD,       KC_VOLU, MT(MOD_RALT, RGB_TOG)
  ),

 [4] = LAYOUT_ortho_5x15(
    KC_TRNS,     KC_TRNS,        KC_TRNS,       KC_F12,             KC_F1,                  KC_F2,          KC_F3,                  KC_F4,         KC_F5,    KC_F6,      KC_F7,          KC_F8,         KC_F9,         KC_F10,        KC_F11,
    KC_TRNS,     TO(_L5),        KC_TRNS,       KC_TRNS,         TD(TD_1),               TD(TD_2),       TD(TD_3),             ALGR(KC_E),        KC_DOT,  KC_EXLM,    KC_LBRC,  ALGR(KC_MINS),       KC_SCLN,  ALGR(KC_RBRC),       KC_TRNS,
    KC_ASDN,     KC_ASUP,        KC_TRNS,       KC_TRNS,         TD(TD_4),               TD(TD_5),       TD(TD_6),               TD(TD_0),         KC_GT,  KC_UNDS,   PICKFIRST,      PICK2ND,        PICK3RD,    TD(TD_HASH),       KC_TRNS,
    KC_ASON,    KC_ASOFF,        KC_TRNS,       KC_TRNS,         TD(TD_7),               TD(TD_8),       TD(TD_9),               TD(TD_1),       KC_COMM,  KC_RPRN,  TD(TD_ANG),     S(KC_NUBS),      KC_AMPR,        KC_VOLU,       KC_TRNS,
    KC_ASTG,     KC_ASRP,        KC_TRNS,       KC_TRNS,          KC_TRNS,      MT(MOD_LALT,KC_0),        KC_TRNS,                KC_TRNS,       KC_TRNS,  KC_TRNS,    KC_TRNS,        TG(_L2),       KC_TRNS,        KC_VOLD,       KC_TRNS
  ),
  
 [5] = LAYOUT_ortho_5x15(
    KC_ESC,      KC_PSCR,        KC_NO,     KC_ESC,          KC_1,            KC_2,           KC_3,           KC_4,          KC_5,    KC_6,            KC_7,           KC_8,            KC_9,               KC_0,                         KC_DEL,
    TO(0),       TO(_L0),        KC_NO,     KC_TAB,          KC_Q,            KC_W,           KC_E,           KC_R,          KC_T,    KC_Y,            KC_U,           KC_I,            KC_O,               KC_P,                        KC_BSPC,
    KC_F5,         KC_F6,        KC_NO,    KC_LSFT,          KC_A,            KC_S,           KC_D,           KC_F,          KC_G,    KC_H,            KC_N,           KC_J,            KC_L,  KC_K, MT(MOD_LCTL | MOD_RCTL,KC_ENT),
    KC_F7,         KC_F8,        KC_NO,    KC_LSFT,          KC_Z,            KC_X,           KC_C,           KC_V,          KC_B,    KC_M,         KC_COMM,      TD(TD_DOT),    TD(TD_DASH),              KC_UP, MT(MOD_LSFT | MOD_RSFT,KC_END),
    KC_F9,        KC_F10,        KC_NO,    KC_LCTL,        KC_SPC,          KC_SPC,         KC_SPC, LT(_L1,KC_ENT),
                                                                                                               MT(MOD_LSFT,KC_SPC), MT(MOD_LSFT,KC_SPC),
                                                                                                                                             LT(_L2,KC_SPC),           KC_NO,        KC_LEFT,            KC_DOWN,                         KC_RGHT
  )
};

/* ==========================================================================
    INITIALIZATION FUNCTION
   ========================================================================== */

/*void keyboard_post_init_user(void) {
  rgblight_enable();
};*/


layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _L0:
        rgblight_sethsv_noeeprom(HSV_PURPLE);
        break;
    case _L1:
        rgblight_sethsv_noeeprom(HSV_YELLOW);
        break;
    case _L2:
        if (layer_state_cmp(state, _L1)) {
             rgblight_sethsv_noeeprom(HSV_RED);
        } else {
        rgblight_sethsv_noeeprom(HSV_WHITE);
        }
        break;
    case _L3:
        rgblight_sethsv_noeeprom(HSV_RED);
        break;
    case _L4:
        rgblight_sethsv_noeeprom(HSV_GOLD);
        break;
    case _L5:
        rgblight_sethsv_noeeprom(HSV_AZURE);
        break;
    default:
        rgblight_sethsv_noeeprom(HSV_PURPLE);
        break;
    }
  return update_tri_layer_state(state, _L1, _L2, _L3);
}




