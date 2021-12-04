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
/* td state evaluation ignoring interrupted */
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
  TD_F,
  TD_D,
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
  //TD_I_BS,
  //TD_CIRCUM,
  //TD_TICK,
  TD_COMM,
  //TD_DOL_SFT,
  //TD_PIPE_SFT,
  //TD_KOE_ALT,
  //TD_1,
  //TD_2,
  //TD_3,
  //TD_4,
  //TD_5,
  //TD_6,
  //TD_7,
  //TD_8,
  //TD_9,
  //TD_0,
  //TD_10,
  //TD_12,
//  TD_HASH,
  TD_Q,
//  TD_TAB_ENT,
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
  TD_E,
  TD_L,
  TD_ESC,
//  TD_DEL10,
//  TD_R,
//  TD_P,
  TD_T,
  TD_BSP,
};


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

// ß 
void dance_ss_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD:
             if (get_mods() | get_oneshot_mods()) {tap_code16(keycode); break;}
             tap_code16(keycode2); break;
        default: tap_code(keycode); break;
    }
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
    switch (atap_state.state) {
        case TD_SINGLE_HOLD:
                register_code16(keycode2); break;
        case TD_SINGLE_TAP:
        default: 
                register_code16(keycode); break;
    }
}
void dance_holdautorepeat_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD: unregister_code16(keycode2); break;
        default: unregister_code16(keycode); break;
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
/*
// unused
// can be used as replacement of MT() with shifted keys
// mod tap as tap dance only these functions need individual state variables
static td_tap_t dance_ctl = {
    .is_press_action = true,
    .state = TD_NONE
};
static td_tap_t dance_sft = {
    .is_press_action = true,
    .state = TD_NONE
};
// (bug) dance_mod_finished mods must be pressed one after the other, otherwise first key registers a tap instead of hold 
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
*/

// mod tap with D_DOUBLE_HOLD
static td_tap_t c1tap_state_dbl = {
    .is_press_action = true,
    .state = TD_NONE
};
static td_tap_t c2tap_state_dbl = {
    .is_press_action = true,
    .state = TD_NONE
};
// static td_tap_t atap_state_dbl = { 
//     .is_press_action = true,
//     .state = TD_NONE
// };
static td_tap_t s1tap_state_dbl = { 
    .is_press_action = true,
    .state = TD_NONE
};
static td_tap_t s2tap_state_dbl = { 
    .is_press_action = true,
    .state = TD_NONE
};
//(bug - not verified lately ) modifier_dbldance_finished when interupted outputs the modifier instead of key (only with ALT).
// Enhance MT() with TD_DOUBLE_HOLD
void modifier_dbldance_finished (qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2param = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    uint16_t keycode2;
    switch (keycode2param) {
        case 11 :
        case 12 :  keycode2 = KC_LSFT; break;
        case 22 :
        case 21 :  keycode2 = KC_LCTL; break;
        default :  keycode2 = KC_LALT; break;
    }
    td_tap_t *ctap_state = (keycode2param == 11) ? &s1tap_state_dbl : (keycode2param == 12) ? &s2tap_state_dbl : (keycode2param == 21) ? &c1tap_state_dbl : &c2tap_state_dbl; 
    switch (keycode2) { 
        case KC_LSFT : ctap_state->state = mod_dance(state); break; // fast mod activation 
        case KC_LCTL : ctap_state->state = cur_dance(state); break; // slow mod activation
    }   

    switch (ctap_state->state) {
        case TD_SINGLE_TAP: register_code16(keycode); break;
        case TD_SINGLE_HOLD: register_code16(keycode2); break;
        case TD_DOUBLE_HOLD: register_code16(keycode3); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:tap_code16(keycode);register_code16(keycode); break;
        default: register_code16(keycode); break;
    }
}
void modifier_dbldance_each(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    if (state->count == 3) {
            tap_code(keycode);
            tap_code(keycode);
    }
    else if (state->count > 3) {
            tap_code(keycode);
    }
};
void modifier_dbldance_reset (qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2param = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (keycode2param) {
        case 11 :
        case 12 :  keycode2 = KC_LSFT; break;
        case 22 :
        case 21 :  keycode2 = KC_LCTL; break;
        default :  keycode2 = KC_LALT; break;
    }
    td_tap_t *ctap_state = (keycode2param == 11) ? &s1tap_state_dbl : (keycode2param == 12) ? &s2tap_state_dbl : (keycode2param == 21) ? &c1tap_state_dbl : &c2tap_state_dbl; 
    switch (ctap_state->state) {
        case TD_SINGLE_TAP: unregister_code16(keycode); break;
        case TD_SINGLE_HOLD: unregister_code16(keycode2); break;
        case TD_DOUBLE_HOLD: unregister_code16(keycode3);break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        default: unregister_code16(keycode); break;
    }
    //s1tap_state_dbl.state = TD_NONE;
    //s2tap_state_dbl.state = TD_NONE;
    //c1tap_state_dbl.state = TD_NONE;
    //c2tap_state_dbl.state = TD_NONE;
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
    [TD_Q] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_Q, DE_EXLM, DE_AT})), // tap, hold, double_tap 
    //[TD_F] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_F, S(KC_4)})), // tap, hold
    
    //[TD_X] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_X, DE_PIPE, C(KC_X)})),
    //[TD_C] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_C, C(KC_C), ALGR(KC_7), ALGR(KC_0)})), // tap, double tap key or KC_NO for 2xtap, hold, double_hold autoclose for "" '' () []...
    //[TD_V] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_V, ALGR(KC_0), C(KC_V)})),
    [TD_X] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_X, DE_PIPE})),
    [TD_C] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_C, KC_NO, ALGR(KC_7), ALGR(KC_0)})), // tap, double tap key or KC_NO for 2xtap, hold, double_hold autoclose for "" '' () []...
    [TD_V] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_V, ALGR(KC_0)})),
    
    [TD_Y] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_Z, C(KC_Z), C(KC_Z)})),
    [TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_Y, DE_AMPR})),
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
    [TD_SS_UML] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_ss_finished, atap_state_reset, &((dance_user_data_t){KC_S, KC_MINS})),
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_DOT, S(KC_DOT), S(KC_NUBS)})),  // tap(repeated on tripple tap), hold(repeated), double_hold (not repeated)
    [TD_DASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_SLSH, S(KC_SLSH), DE_TILD})),
    //[TD_I_BS] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_I, DE_BSLS, S(KC_7)})),
    //[TD_DOL_SFT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_mod_finished, dance_mod_reset, &((dance_user_data_t){S(KC_4), KC_LSFT})), // only one KC_LCTL and KC_LSFT definition are currently supported
    //[TD_PIPE_SFT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_mod_finished, dance_mod_reset, &((dance_user_data_t){A(C(KC_NUBS)), KC_LSFT})),
    // unused because of bug [TD_KOE_ALT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_K, KC_LALT, A(KC_TAB)})),// only one KC_LALT and KC_LCTL definition are currently supported
    [TD_ANG] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_NUBS, S(KC_NUBS)})),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_NUHS), S(KC_NUHS)})),
    [TD_PAR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_8), S(KC_9)})),
    [TD_CUR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){ALGR(KC_7), ALGR(KC_0)})),
    [TD_COMM] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished,  atap_state_reset, &((dance_user_data_t){KC_COMM, S(KC_COMM), KC_NUBS})),
    [TD_W] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_W, KC_NO, KC_AT, KC_AT})),
    [TD_L] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_L, KC_NO, S(KC_NUHS), S(KC_NUHS)})),
    [TD_E] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_E, KC_NO, ALGR(KC_8), ALGR(KC_9)})),
    //[TD_1] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_1, KC_F1})),
    //[TD_2] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_2, KC_F2})),
    //[TD_3] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_3, KC_F3})),
    //[TD_4] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_4, KC_F4})),
    //[TD_5] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_5, KC_F5})),
    //[TD_6] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_6, KC_F6})),
    //[TD_7] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_7, KC_F7})),
    //[TD_8] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_8, KC_F8})),
    //[TD_9] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_9, KC_F9})),
    //[TD_0] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_0, KC_F11})),
    //[TD_12] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_1, KC_F12})),
    //[TD_10] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){DE_EURO, KC_F10})),
//    [TD_DEL10] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdwmod_finished, atap_state_reset, &((dance_user_data_t){KC_DEL, KC_F10})),
    [TD_F] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_F, 11, KC_DLR})),
    [TD_D] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_D, 21, DE_HASH})),
    [TD_N] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_N, 12, DE_LPRN})),
    [TD_T] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, modifier_dbldance_finished, modifier_dbldance_reset, &((dance_user_data_t){KC_T, 22, DE_RPRN})),
//    [TD_H] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_H, KC_UNDS, KC_UNDS})),
    [TD_DQUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_AT, KC_AT})),
    [TD_SQU] = ACTION_TAP_DANCE_FN_ADVANCED_USER(curly_dance_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){ALGR(KC_8), ALGR(KC_9)})),
//    [TD_BSP] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_holdautorepeat_finished, dance_holdautorepeat_reset, &((dance_user_data_t){KC_BSPC, KC_END})),
};
/* delete or get working
void oneshot_layer_changed_user(uint8_t layer) {
    active_osl = layer;
    if (!layer) {
        // deregister OSL here  println("Oneshot layer off");
  }
}
*/

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
        switch (keycode) {
            case TD(TD_A_UML):
            case TD(TD_O_UML):
            case TD(TD_U_UML):
            case TD(TD_SS_UML):
                return 140;
            default:
                return TAPPING_TERM;
        }
}