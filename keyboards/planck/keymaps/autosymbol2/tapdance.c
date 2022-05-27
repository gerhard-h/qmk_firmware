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
  TD_ATAB,
  TD_APUP,
  TD_A,
  TD_O,
  TD_F,
  TD_D,
  TD_U,
  TD_SS,
  TD_DASH,
  TD_DOT,
  TD_PAR,
  TD_CUR,
  TD_SQU,
  TD_ANG,
  TD_QUOT,
  TD_DQUOT,
  TD_I,
  TD_COMM,
  TD_Q,
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
  TD_E,
  TD_L,
  TD_ESC,
  TD_R,
  TD_P,
  TD_BSP
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
    if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
}

// TD shortcut () <> {} [] "" '' // \\ triggered by HOLD or DOUBLE_HOLD or SHIFT_HOLD
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
            tap_code(keycode2);
            return;
        case TD_SINGLE_HOLD:
             if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {
                     // mods overwrite hold:  ctl + hold c -> C(c) instead of C({)
                     tap_code16(keycode); return;
             }
             if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
                    // sft + hold c -> TD_DOUBLE_HOLD
                    // imlements the SFT_HOLD layer
                    mod_state = get_mods();
                    clear_mods();
                    tap_code16(keycode3);
                    tap_code16(keycode4);
                    tap_code(keycode2);
                    set_mods(mod_state);
                    return;
             }
             // hold c -> {
             tap_code16(keycode3); return;
        case TD_SINGLE_TAP:
                // do we have to set n_rshft_done to avoid double uppercase like EC instead of Ec
                // applying shift even though the shift key got already released
                handle_force_shift_tap (keycode, false);
                return;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
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
    if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
}

// ß autocorrect Shift+Hold -> S :: idea $
static uint16_t tab_timer;
void dance_ss_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (atap_state.state) {
        case TD_SINGLE_HOLD:
             if ((get_mods() | get_oneshot_mods()) == MOD_BIT(KC_RSFT)) {
               tap_code16(keycode3); // ' extra
               return;
             }
             if ((get_mods() | get_oneshot_mods()) == MOD_BIT(KC_LALT)) {
               if(keycode == KC_R){
                tab_timer = timer_read();
                tap_code16(KC_TAB); // ' extra
               }
               return;
             }
             if (get_mods() | get_oneshot_mods()) {
                     tap_code16(keycode); // autocorrect into C(s),...
                     return;
             }
             tap_code16(keycode2); return;
        default:
                if (force_leftside_shift_tap(keycode, false)) {return;}
                if( f_lshft_pressed || n_rshft_pressed ){shft_used_timer = timer_read();}
                if(timer_elapsed(tab_timer) < 7000 && keycode == KC_R && (get_mods() | get_oneshot_mods()) == MOD_BIT(KC_LALT)) {
                        tab_timer = timer_read();
                        tap_code16(KC_TAB);
                        return;
                }
                if(timer_elapsed(tab_timer) < 7000 && keycode == KC_R && (get_mods() & MOD_MASK_SA)) {
                        tab_timer = timer_read();
                        tap_code(KC_LEFT);
                        return;
                }
                tap_code16(keycode);
                return;
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
        case TD_SINGLE_TAP:
                handle_force_shift_tap (keycode, false);
                return;
        case TD_SINGLE_HOLD:
             if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
             tap_code16(keycode2); break;
        default: tap_code16(keycode); break;
    }
}

/* ii /, zz & lost words when redefine double tap: eineiige unparteiische variieren ~ 50 words; jazz piazza skizzen bizzar kreuzzug kurzzeitig zzgl. ~ 100
 vv lost words: alternativvorschlag ~ 5 words;
* y comma q
* for when SINGLE_TAP, SINGLE_HOLD, DOUBLE_TAP should all behave different and DOUBLE_HOLD equals DOUBLE_TAP */
void dance_dbltap_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;        //normal
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;      //shifted = single hold
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;      //double hold and double tap
    switch (atap_state.state) {
        case TD_SINGLE_HOLD:
             //if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL )) {tap_code16(keycode); break;} //was there a reason to exclude shift ... yes ü ... put a mod mask in userdata vs di$erent$inished functions
             if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
                    // imlements the SFT_HOLD layer
                    mod_state = get_mods();
                    clear_mods();
                    tap_code16(keycode3);
                    set_mods(mod_state);
                    break;
             }
             // autocorrect to UPPER
             if (get_mods() | get_oneshot_mods()) {tap_code16(keycode); break;}
             tap_code16(keycode2); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_DOUBLE_HOLD: tap_code16(keycode3); break;
        case TD_SINGLE_TAP:
        default:
                handle_force_shift_tap (keycode, false);
                return;
    }
}

// ::: *** /// ...... ------ ____. triple tap for autorepeat keycode, no autorepeat on Double_Tap_Hold
void dance_autorepeat_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    switch (atap_state.state) {
        case TD_SINGLE_TAP:
                switch (keycode) {
                        case KC_M:
                                if ( force_rightside_shift_tap(keycode, true)) {return;}
                }
                if( f_lshft_pressed || n_rshft_pressed){shft_used_timer = timer_read();}
                register_code16(keycode);
                return;
        case TD_SINGLE_HOLD:
                if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
                if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
                    // imlements the SFT_HOLD layer
                    mod_state = get_mods();
                    clear_mods();
                    tap_code16(keycode3);
                    if (keycode3 == KC_GRV) { tap_code(KC_SPC); }
                    set_mods(mod_state);
                    break;
                }
                register_code16(keycode2); break;
        case TD_DOUBLE_HOLD:
            if (keycode3 == KC_GRV) { // dead key handling for ^
                if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {tap_code16(S(KC_GRV)); break;}
                    tap_code(KC_GRV);
                    tap_code(KC_SPC);
            } else {
                tap_code16(keycode3);
            }
            break;
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
        case TD_SINGLE_HOLD:
                if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {break;}
                unregister_code16(keycode2); break;
        case TD_DOUBLE_HOLD:  break;//unregister_code16(keycode3); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default: unregister_code16(keycode); break;
    }
    atap_state.state = TD_NONE;
    if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
}
// atap one button
void dance_atab_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    register_code16(keycode2);  //alt
    switch (atap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(keycode);
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_HOLD:
            tap_code_delay(keycode, 40);
            tap_code_delay(KC_RIGHT, 500);
            break;
        default: 
            tap_code(keycode); 
            for (uint8_t i=1; i < state->count; i++) {
                tap_code_delay(keycode, 450);
            };
        break;
    }
}
void dance_atab_reset(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    unregister_code16(keycode2);
}
// esc home end ^
void dance_esc_finished(qk_tap_dance_state_t *state, void *user_data) {
    atap_state.state = cur_dance(state);
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode3 = ((dance_user_data_t*)user_data)->keycode3;
    uint16_t keycode4 = ((dance_user_data_t*)user_data)->keycode4;

    switch (atap_state.state) {
        case TD_SINGLE_TAP: register_code16(keycode); break;
        case TD_SINGLE_HOLD:
                if (get_mods() & (MOD_MASK_GUI | MOD_MASK_ALT | MOD_MASK_CTRL)) {tap_code16(keycode); break;}
                register_code16(keycode2); break;
        case TD_DOUBLE_HOLD:
            if (keycode3 == KC_GRV) { // dead key handling for ^
                if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {tap_code16(S(KC_GRV)); break;}
                    tap_code(KC_GRV);
                    tap_code(KC_SPC);
            } else {
                tap_code16(keycode3);
            }
            break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
                register_code16(keycode4);
            break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default:
            for (uint8_t i=2; i < state->count; i++) {
                tap_code16(keycode);
            };
            register_code16(keycode);
        break;
    }
}
void dance_esc_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((dance_user_data_t*)user_data)->keycode;
    uint16_t keycode2 = ((dance_user_data_t*)user_data)->keycode2;
    uint16_t keycode4 = ((dance_user_data_t*)user_data)->keycode4;
    switch (atap_state.state) {
        case TD_SINGLE_TAP: unregister_code16(keycode); break;
        case TD_SINGLE_HOLD: unregister_code16(keycode2); break;
        case TD_DOUBLE_HOLD:  break;//unregister_code16(keycode3); break;
        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
                unregister_code16(keycode4);
                break;
        case TD_TRIPLE_TAP:
        case TD_TRIPLE_HOLD:
        default: unregister_code16(keycode); break;
    }
    atap_state.state = TD_NONE;
    if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
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

/*important macro to define userdata */
#define ACTION_TAP_DANCE_FN_ADVANCED_USER(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset, user_user_data) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = (void*)user_user_data, }


// Tap Dance definitions - look at the _finished functions names to know what is happening, reset_ and each_ functions might be shared
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_esc_finished, dance_esc_reset, &((dance_user_data_t){KC_ESC, KC_HOME, KC_GRV, KC_END})), //tap (tripple tap hold for AutoRepeat), hold (with AR), double_hold (without AR), shift passthrough
    [TD_Q] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_esc_finished, dance_esc_reset, &((dance_user_data_t){KC_Q, DE_EXLM, DE_AT, DE_EXLM})),
    [TD_X] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_X, KC_NO, S(KC_NUHS), S(KC_NUHS)})),
    [TD_C] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_C, KC_LEFT, ALGR(KC_7), ALGR(KC_0)})), // tap, double_hold autoclose for "" '' () []...
    [TD_V] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_V, ALGR(KC_0), KC_ENT})),
    [TD_Y] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_Z, C(KC_Z), C(KC_Z)})),
    [TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_Y, KC_NO, DE_AMPR, DE_AMPR})),
    [TD_M] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_M, S(KC_RBRC), S(KC_RBRC)})),
    [TD_U] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_U, KC_LBRC})),
    [TD_A] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_A, KC_QUOT})),
    [TD_O] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_O, KC_SCLN})),
    [TD_SS] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_ss_finished, atap_state_reset, &((dance_user_data_t){KC_S, KC_MINS, DE_QUOT})),
    [TD_DOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_DOT, S(KC_DOT), S(KC_NUBS)})),  // tap(repeated on tripple tap), hold(repeated), double_hold (not repeated)
    [TD_DASH] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_SLSH, S(KC_SLSH), DE_TILD})),
    [TD_ANG] = ACTION_TAP_DANCE_FN_ADVANCED_USER( dance_hold_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_NUBS, S(KC_NUBS)})),
    [TD_QUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER( dance_hold_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_NUHS), S(KC_NUHS)})),
    [TD_PAR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( dance_hold_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){S(KC_8), S(KC_9)})),
    [TD_CUR] = ACTION_TAP_DANCE_FN_ADVANCED_USER( dance_hold_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){ALGR(KC_7), ALGR(KC_0)})),
    [TD_COMM] = ACTION_TAP_DANCE_FN_ADVANCED_USER(modifier_dbldance_each, dance_dbltap_finished, atap_state_reset, &((dance_user_data_t){KC_COMM, S(KC_COMM), KC_NUBS})),
    [TD_W] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_W, KC_LEFT, KC_AT, KC_AT})),
    [TD_L] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_L, KC_LEFT, S(KC_NUHS), S(KC_NUHS)})),// not used on _L0
    [TD_DQUOT] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){KC_AT, KC_AT})),
    [TD_SQU] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, curly_dance_finished, curly_dance_reset, &((dance_user_data_t){ALGR(KC_8), ALGR(KC_9)})),
    [TD_H] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_H, KC_NO, DE_SLSH, DE_SLSH})),
    [TD_I] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_I, KC_NO, DE_BSLS, DE_BSLS})),
    [TD_B] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_B, KC_NO, DE_PLUS, DE_PLUS})),
    [TD_P] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_P, DE_QUES})),
    [TD_G] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_G, KC_NO, DE_EQL, DE_EQL})),
    [TD_J] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_hold_finished, atap_state_reset, &((dance_user_data_t){KC_J, KC_DLR})),
    [TD_R] = ACTION_TAP_DANCE_FN_ADVANCED_USER(dance_hold_each, dance_ss_finished, atap_state_reset, &((dance_user_data_t){KC_R, S(KC_9), KC_R})), // KC_CAP is an option here
    [TD_E] = ACTION_TAP_DANCE_FN_ADVANCED_USER(shortcut_dance_each, shortcut_dance_finished, atap_state_reset, &((dance_user_data_t){KC_E, KC_LEFT, S(KC_8), S(KC_9)})),
    [TD_ATAB] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_atab_finished, dance_atab_reset, &((dance_user_data_t){KC_TAB, KC_LALT})),
    [TD_APUP] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_atab_finished, dance_atab_reset, &((dance_user_data_t){KC_PGUP, KC_LALT})),
    [TD_BSP] = ACTION_TAP_DANCE_FN_ADVANCED_USER(NULL, dance_autorepeat_finished, dance_autorepeat_reset, &((dance_user_data_t){KC_BSPC, C(KC_BSPC), C(KC_BSPC)})),
   
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
        switch (keycode) {
            // diacrits should activate much faster than normal symbols
            case TD(TD_A):
            case TD(TD_O):
            case TD(TD_U):
            case TD(TD_SS):
                return 140;
            // cases for testing Mod Tap capabilities bc Daten sometimes becomes DAten this only happens if a is a tap dance like NO but not Nl
            //case LSFT_T(KC_F):
            //case RSFT_T(KC_N):
             //return 120;
            case LCTL_T(KC_D):
            case LCTL_T(KC_T):
            case TD(TD_BSP):
                return 140;
            case TD(TD_Y):
            case TD(TD_R):
                return 250;
            case ALT_T(KC_L):
            case LALT_T(KC_K):
            case GUI_T(KC_K):
                return 350;
            default:
                return TAPPING_TERM;  // ~ 250
        }
}