/* Copyright 2020 IFo Hancroft
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

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {6, 4, HSV_RED},       // Light 4 LEDs, starting with LED 6
    {12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 2, HSV_CYAN}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_PURPLE}
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {13, 2, HSV_GREEN}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer     // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

enum layers { _L0, _L1, _L2, _L3, _L4 };

#define PARAN TD(PAR)
#define CURLY TD(CUR)
#define SQUAR TD(SQU)
#define ANGUL TD(ANG)

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,  // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

/*struct to persisit td state*/
typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

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
  TD_ESC_DEL = 0,
  TD_A_UML,
  CT_AUML,
  TD_O_UML,
  TD_U_UML,
  TD_SS_UML,
  TD_DASH,
  TD_DOT,
  TD_Q,
  PAR,
  CUR,
  SQU,
  ANG
};


// Parantheses tap dance german
static td_tap_t paranthesistap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void paranthesis_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    paranthesistap_state.state = cur_dance(state);
    switch (paranthesistap_state.state) {
        case TD_SINGLE_TAP: SEND_STRING("*");
        break;
        case TD_SINGLE_HOLD:
            SEND_STRING("*("); 
            register_code(KC_LEFT);
            unregister_code(KC_LEFT); 
        break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP: SEND_STRING("**"); break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD: SEND_STRING("***"); 
        default: break;
    }
}

void paranthesis_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    paranthesistap_state.state = TD_NONE;
}
void paranthesis_dance (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    SEND_STRING("*("); 
    register_code(KC_LEFT);
    unregister_code(KC_LEFT);
  } else if (state->count == 2) {
    SEND_STRING("*");
  } else if (state->count == 3) {
    SEND_STRING("(");
  }
}
static td_tap_t curlytap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void curly_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
    curlytap_state.state = cur_dance(state);
    switch (curlytap_state.state) {
        case TD_SINGLE_TAP:tap_code16(A(C(KC_7)));
        break;
        case TD_SINGLE_HOLD:
            register_code(KC_LCTRL);
            register_code(KC_LALT);
            register_code(KC_7);
            unregister_code(KC_7);
            register_code(KC_0);
            unregister_code(KC_0);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTRL);
            register_code(KC_LEFT); 
        break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            register_code(KC_LCTRL);
            register_code(KC_LALT);
            register_code(KC_7);
            unregister_code(KC_7);
            register_code(KC_7);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTRL);
            break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
            register_code(KC_LCTRL);
            register_code(KC_LALT);
            register_code(KC_7);
            unregister_code(KC_7);
            register_code(KC_7);
            unregister_code(KC_7);
            register_code(KC_7);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTRL);
        default: break;
    }
}

void curly_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (curlytap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(A(C(KC_7))); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LEFT); break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        default:
            unregister_code(KC_7);
        break;
    }
    curlytap_state.state = TD_NONE;
}
static td_tap_t dashtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void dash_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    dashtap_state.state = TD_NONE;
}

void dash_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
        dashtap_state.state = cur_dance(state);
    switch (dashtap_state.state) {
        case TD_SINGLE_TAP:tap_code(KC_SLSH); break;
        case TD_SINGLE_HOLD:
            register_code16(S(KC_SLSH));
            unregister_code16(S(KC_SLSH));
        break;
        case TD_DOUBLE_HOLD:
            register_code16(S(KC_7));
            unregister_code16(S(KC_7));
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            register_code16(S(KC_SLSH));
            unregister_code16(S(KC_SLSH));
            register_code16(S(KC_SLSH));
            unregister_code16(S(KC_SLSH));
            break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
            register_code(KC_SLSH);
            unregister_code(KC_SLSH);
        default: break;
    }
}
static td_tap_t dottap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void dot_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    dottap_state.state = TD_NONE;
}

void dot_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
        dottap_state.state = cur_dance(state);
    switch (dottap_state.state) {
        case TD_SINGLE_TAP:tap_code(KC_DOT); break;
        case TD_SINGLE_HOLD:
            register_code16(S(KC_DOT));
            unregister_code16(S(KC_DOT));
        break;
        case TD_DOUBLE_HOLD:
            register_code16(S(KC_RBRC));
            unregister_code16(S(KC_RBRC));
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            register_code16(S(KC_DOT));
            unregister_code16(S(KC_DOT));
            register_code16(S(KC_DOT));
            unregister_code16(S(KC_DOT));
            break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_DOT);
            unregister_code(KC_DOT);
            register_code(KC_DOT);
            unregister_code(KC_DOT);
        default: break;
    }
}

static td_tap_t squaretap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void square_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    squaretap_state.state = TD_NONE;
}

void square_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
        squaretap_state.state = cur_dance(state);
    switch (squaretap_state.state) {
        case TD_SINGLE_TAP:tap_code16(A(C(KC_8))); break;
        case TD_SINGLE_HOLD:
            register_code(KC_LCTRL);
            register_code(KC_LALT);
            register_code(KC_8);
            unregister_code(KC_8);
            register_code(KC_9);
            unregister_code(KC_9);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTRL);
            register_code(KC_LEFT); 
            unregister_code(KC_LEFT);
        break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            register_code(KC_LCTRL);
            register_code(KC_LALT);
            register_code(KC_8);
            unregister_code(KC_8);
            register_code(KC_8);
            unregister_code(KC_8);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTRL);
            break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
            register_code(KC_LCTRL);
            register_code(KC_LALT);
            register_code(KC_8);
            unregister_code(KC_8);
            register_code(KC_8);
            unregister_code(KC_8);
            register_code(KC_8);
            unregister_code(KC_8);
            unregister_code(KC_LALT);
            unregister_code(KC_LCTRL);
        default: break;
    }
}

static td_tap_t angulartap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void angular_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
    angulartap_state.state = TD_NONE;
}

void angular_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
        angulartap_state.state = cur_dance(state);
    switch (angulartap_state.state) {
        case TD_SINGLE_TAP:tap_code16(KC_NUBS); break;
        case TD_SINGLE_HOLD:
            register_code(KC_NUBS);
            unregister_code(KC_NUBS);
            register_code(KC_LSFT);
            register_code(KC_NUBS);
            unregister_code(KC_NUBS);
            unregister_code(KC_LSFT);
            register_code(KC_LEFT); 
            unregister_code(KC_LEFT);
        break;
        case TD_DOUBLE_HOLD:
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            register_code(KC_LSFT);
            register_code(KC_NUBS);
            unregister_code(KC_NUBS);
            unregister_code(KC_LSFT);
            break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
            register_code(KC_NUBS);
            unregister_code(KC_NUBS);
            register_code(KC_NUBS);
            unregister_code(KC_NUBS);
            register_code(KC_NUBS);
            unregister_code(KC_NUBS);
        default: break;
    }
}

static td_tap_t atap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void dance_auml_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    switch (atap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_A); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_A)); break;
        case TD_DOUBLE_TAP: register_code(KC_QUOT); break;
        case TD_DOUBLE_HOLD: register_code16(S(KC_QUOT)); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_A); register_code(KC_A);
        default: break;
    }
}

void dance_auml_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (atap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_A); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_A)); break;
        case TD_DOUBLE_TAP: unregister_code(KC_QUOT); break;
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_QUOT)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_A);
        default: break;
    }
    atap_state.state = TD_NONE;
}

static td_tap_t qtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void dance_q_reset(qk_tap_dance_state_t *state, void *user_data) {atap_state.state = cur_dance(state);
    switch (qtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_U); break;
        case TD_SINGLE_HOLD: unregister_code(KC_U); break;
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_Q)); break;
        case TD_DOUBLE_TAP:
        default: unregister_code(KC_Q); break;
    }
    qtap_state.state = TD_NONE;
}
void dance_q_finished(qk_tap_dance_state_t *state, void *user_data) {
    qtap_state.state = cur_dance(state);
    switch (qtap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_Q); register_code(KC_U); break;
        case TD_SINGLE_HOLD: tap_code16(S(KC_Q));register_code(KC_U); break;
        case TD_DOUBLE_HOLD: register_code16(S(KC_Q)); break;
        case TD_DOUBLE_TAP:
        default: register_code(KC_Q); break;
    }
}

static td_tap_t utap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void dance_uuml_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (utap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_U); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_U)); break;
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_TAP: unregister_code(KC_LBRC); break;
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_LBRC)); break;
        default: break;
    }
    utap_state.state = TD_NONE;
}
void dance_uuml_finished(qk_tap_dance_state_t *state, void *user_data) {
        utap_state.state = cur_dance(state);
        switch (utap_state.state) {
                case TD_SINGLE_TAP: register_code(KC_U); break;
                case TD_SINGLE_HOLD: register_code16(S(KC_U)); break;
                case TD_DOUBLE_SINGLE_TAP:
                case TD_DOUBLE_TAP: register_code(KC_LBRC); break;
                case TD_DOUBLE_HOLD: register_code16(S(KC_LBRC)); break;
                default: break;
        }
}

static td_tap_t stap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void dance_suml_finished(qk_tap_dance_state_t *state, void *user_data) {
    stap_state.state = cur_dance(state);
    switch (stap_state.state) {
        case TD_SINGLE_TAP: tap_code(KC_S); break;
        case TD_SINGLE_HOLD: tap_code16(S(KC_S)); break;
        case TD_DOUBLE_TAP: 
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_S); tap_code(KC_S); break;
        case TD_DOUBLE_HOLD: tap_code(KC_MINS); break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD: tap_code(KC_S); tap_code(KC_S); tap_code(KC_S); break;
        default: break;
    }
}

void dance_suml_reset(qk_tap_dance_state_t *state, void *user_data) {
    stap_state.state = TD_NONE;
}

static td_tap_t otap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void dance_ouml_finished(qk_tap_dance_state_t *state, void *user_data) {
    otap_state.state = cur_dance(state);
    switch (otap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_O); break;
        case TD_SINGLE_HOLD: register_code16(S(KC_O)); break;
        case TD_DOUBLE_TAP: register_code(KC_SCLN); break;
        case TD_DOUBLE_HOLD: register_code16(S(KC_SCLN)); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_O); register_code(KC_O);
        default: break;
    }
}

void dance_ouml_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (otap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_O); break;
        case TD_SINGLE_HOLD: unregister_code16(S(KC_O)); break;
        case TD_DOUBLE_TAP: unregister_code(KC_SCLN); break;
        case TD_DOUBLE_HOLD: unregister_code16(S(KC_SCLN)); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_O);
        default: break;
    }
    otap_state.state = TD_NONE;
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC_DEL] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_ESC),
    [TD_Q] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_q_finished, dance_q_reset),
    [TD_DASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dash_dance_finished, dash_dance_reset),
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dot_dance_finished, dot_dance_reset),
    [TD_SS_UML] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_suml_finished, dance_suml_reset),
    [CT_AUML] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_auml_finished, dance_auml_reset),
    [TD_O_UML] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_ouml_finished, dance_ouml_reset),
    [TD_U_UML] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_uuml_finished, dance_uuml_reset),
    [PAR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, paranthesis_dance_finished, paranthesis_dance_reset )
   ,[CUR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, curly_dance_finished, curly_dance_reset)
   ,[SQU] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, square_dance_finished, square_dance_reset )
   ,[ANG] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, angular_dance_finished, angular_dance_reset )
};
/*
* todo
* 
* (-) tap dance on lower/raise to lock layer_state_cmp ... not working because space and emter are spammable keys
fake layer tap with extra osl
OSL(num) num TO(sym) sym TG(num) layer3 TO(0)
double tap lock symbol layer double tap for exit
tripple tap lock layer3 single tap for exit
MO(sym) + TG(num) locked num tripple tap for exit


* leader key for F1-F12
* tap dance on rsft  cycle layers or leaderkey
* (-) tap on spacebar to go to layer 0
* layer lights 
* tap dances
* q esc
* , ' "  or , is mod_ctrl
* . .. \
* - / *
* qu Qu q disabled when ctrl or alt are held
*  
* combos
* qw = esc better than tapdance
* 
* numbers
* vvv = 0
* fff = 1.....
* vvq - vvc = 1 - 9
* home row mods?

ii -> \
, ; 
. .. : .:hold > * 

-_  --hold > * /

vvhold > $

rsft rsft hold osl makro

´´
^^````°°´^ auto space 
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [0] = LAYOUT_ortho_5x15(
    RESET, KC_NO, KC_NO, KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_NO, KC_NO, KC_NO, KC_DEL,  TD(TD_Q),    KC_W,    KC_E,    KC_R,    KC_J,    KC_Y,TD(TD_U_UML),    KC_I, TD(TD_O_UML),    KC_P,    KC_BSPC,
    
    KC_NO, KC_NO, KC_NO, MT(MOD_LCTL | MOD_LSFT,KC_TAB),
             TD(CT_AUML), TD(TD_SS_UML), MT(MOD_LCTL, KC_D),   MT(MOD_LSFT, KC_F),    KC_G,    KC_H,    MT(MOD_LSFT, KC_N),   MT(MOD_LCTL,KC_T),  KC_L,MT(MOD_LALT,KC_K), MT(MOD_LCTL | MOD_RCTL,KC_ENT),
    
    KC_NO, KC_NO, KC_NO, MT(MOD_LSFT,KC_HOME)
           , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_M,    KC_COMM, TD(TD_DOT),  TD(TD_DASH), KC_UP, MT(MOD_LSFT | MOD_RSFT,KC_END) ,
    
    KC_NO, KC_NO, KC_NO, MT(MOD_LCTL, KC_PGUP), MT(MOD_LGUI, KC_PGDN), MT(MOD_LALT,KC_DEL)
                               , LT(_L1,KC_BSPC), 
                                        LT(_L2,KC_ENT),
                                                MT(MOD_LSFT,KC_SPC), MT(MOD_LSFT,KC_SPC),
                                                        LT(_L1,KC_SPC),
                                                                   OSL(_L2),
                                                                            KC_LEFT, KC_DOWN, KC_RGHT
 ),

 [1] = LAYOUT_ortho_5x15(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_ESC,   ALGR(KC_Q), KC_AT,    SQUAR     , ALGR(KC_9),  KC_PERC, KC_EXLM, KC_LBRC,ALGR(KC_MINS),KC_SCLN    ,ALGR(KC_RBRC), KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV,  KC_QUOT,    KC_MINS,  CURLY     , ALGR(KC_0), KC_RCBR , KC_UNDS, PARAN,KC_LPRN      ,S(KC_NUHS) ,KC_NUHS      , KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_EQL,     KC_CIRC,  ALGR(KC_NUBS),  KC_DLR,  KC_PPLS, KC_RPRN, ANGUL,ALGR(KC_MINS),    KC_AMPR,        KC_UP, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    TG(_L2),    KC_TRNS, KC_TRNS, KC_TRNS
  ),

 [2] = LAYOUT_ortho_5x15(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_ESC,       KC_1,      KC_2,                   KC_3,                   ALGR(KC_E),              KC_DOT,     KC_SLSH,      KC_LBRC,      KC_UP,      KC_SCLN,      KC_TRNS,      KC_BSPC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_4,      MT(MOD_LALT,KC_5),      MT(MOD_LSFT,KC_6),      MT(MOD_LCTL,KC_P1),      KC_GT,      KC_HOME,      KC_LEFT,      KC_DOWN,      KC_RGHT,      KC_END,      KC_TRNS,   
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_7,      KC_8,                   KC_9,                   KC_0,                   KC_COMM,    KC_RCBR,      KC_BSPC,      KC_DEL,      KC_ENT,      KC_TRNS,      KC_TRNS,      
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LGUI,MT(MOD_LALT,KC_0),TG(_L1), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   TO(_L1),    KC_TRNS, KC_TRNS, KC_TRNS
  ),

 [3] = LAYOUT_ortho_5x15(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, RESET,             DEBUG,      RGB_TOG,      RGB_MOD, RGB_HUI, RGB_HUD, KC_MS_BTN1,  KC_MS_UP,   KC_MS_BTN2, KC_MS_WH_UP     , TO(0),
    KC_TRNS, KC_TRNS, KC_TRNS, KC_F2, KC_F5,      KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,KC_MS_RIGHT, KC_MS_WH_DOWN, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_F3, KC_F6,             KC_F8,       KC_F10,       KC_F12, RGB_VAI, RGB_VAD, KC_MS_BTN1,  KC_MS_BTN3,  KC_MS_BTN2,      _______, _______,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_F4, KC_F7,MT(MOD_LALT,KC_F9),       KC_F11,       KC_F12, _______, _______, _______, TO(_L4),  KC_VOLD, KC_VOLU, MT(MOD_RALT, RGB_TOG)
  ),

 [4] = LAYOUT_ortho_5x15(
    KC_TRNS, KC_TRNS, KC_F12, KC_F1, KC_F2,             KC_F3,      KC_F4,      KC_F5, KC_F6, KC_F7, KC_F8,  KC_F9,   KC_F10, KC_F11,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(_L0),  KC_VOLD, KC_VOLU, MT(MOD_RALT, RGB_TOG)
  ),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _L1, _L2, _L3);
}
