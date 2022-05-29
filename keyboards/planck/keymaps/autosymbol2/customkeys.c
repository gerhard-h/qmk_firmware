/* custom keycodes (macros) */
// # include "customhold.c"
enum custom_keycodes {
    PICKFIRST = SAFE_RANGE,
    PICK2ND,
    PICK3RD,
    CTLSFTF,
    CIRCUMFL,
    TICKTICK,
    STICKTICK,
    BACKLIT,
    N_RSHFT,
    F_LSHFT,
    TG_LNAV,
    TG_L4
};
static bool default_layer_moved;
static bool default_layer_movedl4;
static uint16_t caps_lock_on_key = KC_NO;
static uint16_t n_rshft_timer;
static uint16_t f_lshft_timer;
static bool n_rshft_done;
static bool f_lshft_done;
static bool n_rshft_pressed;
static bool f_lshft_pressed;
static uint16_t rshft_up_timer; // when shift was last released
static uint16_t lshft_up_timer;
static uint16_t shft_used_timer; // when the last shifted letter was produced by a TAP and holding a home row mod

uint8_t mod_state; // holding the binary representation of active modifiers
static uint8_t caps_state = 0;
bool led_update_user(led_t led_state) {
    if (caps_state != led_state.caps_lock) {
        caps_state = led_state.caps_lock;
    }
    return true;
}

bool _force_shift_tap( uint16_t keycode, bool sft_done, bool sft_pressed, bool only_register, uint16_t shft_up_timer) {
        // force home row shift even if shift key was already released, but only if no other key consumed that shift. both timers are compared to 300ms but they could be adjusted individually        
        if ( !sft_done && !sft_pressed && timer_elapsed(shft_up_timer) < 300 && timer_elapsed(shft_used_timer) > 300 ) {
                                        dprintf("SHIFT enforced\n");
                                        if(only_register){
                                                register_code16(S(keycode));
                                        } else {
                                                tap_code16(S(keycode));
                                        }
                                        shft_used_timer = timer_read();
                                        if (f_lshft_pressed || n_rshft_pressed){shft_used_timer = timer_read();}
                                        return true;
        }
        if (f_lshft_pressed || n_rshft_pressed){shft_used_timer = timer_read();}
        return false;
}

// TODO refactor: move force_leftside_shift_tap/force_rightside_shift_tap and timer reset: if (f_lshft_pressed || n_rshft_pressed){shft_used_timer = timer_read();} into a single funktion
bool force_shift_tap( uint16_t keycode, bool only_register) {
        // this allows for pressing multiple modifiers at the same time, but still predict shifts 
        switch (keycode) {
                        case KC_Q:
                        case KC_W:
                        case KC_R:
                        case KC_E:
                        case KC_J:
                        case KC_A:
                        case KC_S:
                        case KC_D:
                        case KC_F:
                        case KC_G:
                        case KC_Z:  //Y
                        case KC_X:
                        case KC_C:
                        case KC_V:
                        case KC_B:
                                dprintf("TD left side tap keycode: %u done: %b pressed: %b rshft_up_timer: %u shft_used_timer: %u limit: 300\n", keycode, n_rshft_done,n_rshft_pressed,  timer_elapsed(rshft_up_timer), timer_elapsed(shft_used_timer));
                                return _force_shift_tap( keycode, n_rshft_done, n_rshft_pressed, only_register, rshft_up_timer);
                        
                        case KC_Y: //Z
                        case KC_U:
                        case KC_I:
                        case KC_O:
                        case KC_P:
                        case KC_H:
                        case KC_N:
                        case KC_T:
                        case KC_L:
                        case KC_K:
                        //case MT(MOD_LALT, KC_K): // this line seems pointless todo
                        case KC_M:
                        case KC_COMM:
                        case KC_DOT:
                                dprintf("TD right side tap keycode: %u done: %b pressed: %b lshft_up_timer: %u shft_used_timer: %u limit: 300\n", keycode, f_lshft_done,f_lshft_pressed,  timer_elapsed(lshft_up_timer), timer_elapsed(shft_used_timer));
                                return _force_shift_tap( keycode, f_lshft_done, f_lshft_pressed, only_register, lshft_up_timer);
                        
                        default:
                                dprintf("tap keycode: %u is ignored bc it is not left or right side\n", keycode);
                                if (f_lshft_pressed || n_rshft_pressed){shft_used_timer = timer_read();}
                                return false;
        }
}
void handle_force_shift_tap( uint16_t keycode, bool only_register) {
        //remember! this function should be called from all:
        // --- all tapdance TD_SINGLE_TAP cases 
        // --- for each Mod Tap you have to add a case to process_record_user and call force_shift_tap there instead
        
        if (force_shift_tap(keycode, false)) {
            return;
        }
        else if (only_register) {
                register_code16(keycode);
        } else {
                tap_code16(keycode);
        }
}
#ifdef HOMEROWSFTSSYMBOL
void matrix_scan_user(void) {
        // key_hold_matrix_scan_user();

        // resposivnes for holding F (lsft) then holding N (rsft) -> (
        if (!n_rshft_done &&  f_lshft_pressed && (timer_elapsed(n_rshft_timer) > 240) && (timer_elapsed(n_rshft_timer) < 245)){
          if(timer_elapsed(f_lshft_timer) > timer_elapsed(n_rshft_timer)){ 
           if((get_mods() | get_oneshot_mods()) & MOD_BIT(KC_LSFT)) {
                  tap_code16(DE_LPRN);
                  n_rshft_done = true;
           }
          }
        }
        // resposivnes for holding holding N (rsft) then F (lsft) -> $
        if (!f_lshft_done && n_rshft_pressed && (timer_elapsed(f_lshft_timer) > 240) && (timer_elapsed(f_lshft_timer) < 245)){
          if(timer_elapsed(f_lshft_timer) < timer_elapsed(n_rshft_timer)){ 
           if((get_mods() | get_oneshot_mods()) & MOD_BIT(KC_LSFT)) {
                  tap_code16(KC_DLR);
                  f_lshft_done = true;
           }
          }
        }

}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    //dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
   
    mod_state = get_mods(); // Store the current modifier state in the variable for later reference
   // first lets handel custom keycodes
   switch (keycode) {
        case N_RSHFT:
              // bug sometimes Fe becomes Nfe  ... logging improved happens if timing is blow tappingterm 120, 
              if(record->event.pressed) {
                // immediatly Shift
                n_rshft_pressed = true;      
                n_rshft_done = false;
                n_rshft_timer = timer_read();
                dprintf("N down = RSFT ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                register_code(KC_RSFT); // Change the key to be held here
              } else {
                // immediatly Un-Shift
                rshft_up_timer = timer_read();
                n_rshft_pressed = false;      
                unregister_code(KC_RSFT);
                dprintf("unregister_code(KC_RSFT)\n");
                if (timer_elapsed(n_rshft_timer) < 100 ) {  // < TAPPING_TERM for this key
                  //preserver lowercase n: if F (lsft) was pressed after N-down but before N-up don't shift N
                  if( n_rshft_timer < f_lshft_timer && f_lshft_timer - n_rshft_timer < 80){
                        dprintf("lower n tap ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                        dprintf("lower n tap diff: %u ls: %u rs: %u\n", f_lshft_timer - n_rshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
                        unregister_code(KC_LSFT);
                        tap_code16(KC_N);
                        register_code(KC_LSFT);
                  } else {
                        dprintf("any N tap ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                        dprintf("any N tap diff: %u ls: %u rs: %u\n", f_lshft_timer - n_rshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
                        handle_force_shift_tap(KC_N, false); // TAP: can be n or N
                  }
                  dprintf("n_rshft_done = true\n");
                  n_rshft_done = true;
                } else 
                    if (timer_elapsed(n_rshft_timer) < 240 ) {  // < TAPPING_TERM x 2
                        dprintf("double N tap ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                        dprintf("double N tap diff: %u ls: %u rs: %u\n", f_lshft_timer - n_rshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
                        
                        handle_force_shift_tap(KC_N, false); // TAP: can be n or N
                        n_rshft_done = true;
                } 
#ifdef HOMEROWSFTSSYMBOL
                else if ((get_mods() | get_oneshot_mods()) & MOD_BIT(KC_LSFT)) {
                  if(!n_rshft_done){
                        tap_code16(DE_LPRN);
                        n_rshft_done = true;
                  }
                }
#endif
                return false;
              }
              break;
        case F_LSHFT
              if(record->event.pressed) {
                f_lshft_pressed = true;     
                f_lshft_done = false;     
                f_lshft_timer = timer_read();
                register_code(KC_LSFT); // Change the key to be held here 
                dprintf("F down = LSFT ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
              } else {
                lshft_up_timer = timer_read();
                f_lshft_pressed = false;
                unregister_code(KC_LSFT); // Change the key that was held here, too!
                dprintf("unregister_code(KC_LSFT)\n");
                if (timer_elapsed(f_lshft_timer) < 100 && f_lshft_timer < n_rshft_timer && n_rshft_timer - f_lshft_timer < 80){  //here you set something similar to TAPPING_TERM for F_LSHFT ~ 100
                        // protect lower f from delayed shifting: if the other home row shift N_RSHFT was pressed short after F-down but before F-up don't shift f
                        dprintf("lower F tap f down timer: %u n down timer: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                        dprintf("lower F tap diff: %u ls: %u rs: %u\n", n_rshft_timer - f_lshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
                        unregister_code(KC_RSFT);
                        tap_code16(KC_F);
                        register_code(KC_RSFT);
                        f_lshft_done = true; // we released shift within F_LSHFT-TAPPING_TERM so we don't want to shift anything anymore
                } else if (timer_elapsed(f_lshft_timer) < 240 ) {  // ~ F_LSHFT-TAPPING_TERM x 2
                
                        dprintf("any F tap f down timer: %u n down timer: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                        if (f_lshft_timer < n_rshft_timer ){
                            dprintf("any F tap diff: %u ls: %u rs: %u\n", n_rshft_timer - f_lshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
                        } else { 
                            dprintf("any F before N-sft tap diff: %u ls: %u rs: %u\n", f_lshft_timer - n_rshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
                        }                       
                        handle_force_shift_tap(KC_F, false); // Change the character(s) to be sent on tap here
                        f_lshft_done = true;
                }
#ifdef HOMEROWSFTSSYMBOL
                else if ((get_mods() | get_oneshot_mods()) & MOD_BIT(KC_RSFT )) {
                          if(!f_lshft_done){
                                tap_code16(KC_DLR);
                                f_lshft_done = true;
                          }      
                }
#endif
                return false;
              }
              break;
        case TG_LNAV:
                if (record->event.pressed) {
                        if (default_layer_moved) {
                                if (IS_HOST_LED_ON(USB_LED_NUM_LOCK) == true){
                                        tap_code(KC_NUMLOCK);
                                }
                                default_layer_set( ((layer_state_t)1 << _L0));
                                default_layer_moved = false;
                                layer_on(_L0);
                                return false;
                        };
                        default_layer_set( ((layer_state_t)1 << _LNAV));
                        default_layer_moved = true;
                        tap_code(KC_NUMLOCK);
                        return false;
                } else {
                        return false;
                }
                break;
        case TG_L4: // todo maybo osl -> TO -> exit
                if (record->event.pressed) {
                        if (default_layer_movedl4) {
                                default_layer_set( ((layer_state_t)1 << _L0));
                                default_layer_movedl4 = false;
                                layer_on(_L0);
                                return false;
                        };
                        default_layer_set( ((layer_state_t)1 << _L4));
                        default_layer_movedl4 = true;
                        return false;
                } else {
                        return false;
                }
                break;
        case CTL_T(KC_D):
            // you have to do this for all mod taps you use else a shift may get force applied to the next following tapdance
            if (record->tap.count && record->event.pressed) {
                // Intercept tap function
                if (force_shift_tap(KC_D, false)) {return false;}
            }
            return true;
        case CTL_T(KC_T):
            // you have to do this for all mod taps you use else a shift may get force applied to the next following tapdance
            if (record->tap.count && record->event.pressed) {
                // Intercept tap function
                if (force_shift_tap(KC_T, false)) {return false;}
            }
            return true;
        case ALT_T(KC_L):
            // you have to do this for all mod taps you use else a shift may get force applied to the next following tapdance
            if (record->tap.count && record->event.pressed) {
                // Intercept tap function
                if (force_shift_tap(KC_L, false)) {return false;}
            }
            return true;
        case GUI_T(KC_K):
            // you have to do this for all mod taps you use else a shift may get force applied to the next following tapdance
            if (record->tap.count && record->event.pressed) {
                // Intercept tap function
                if (force_shift_tap(KC_K, false)) {return false;}
            }
            return true;             // Return true for normal processing of tap keycode

            /*else if (record->event.pressed) {
                tap_code16(ALGR(KC_E)); // Intercept hold function to send Ctrl-V
            }
            
            return false;*/

    case PICKFIRST:
        if (record->event.pressed) {
            // when keycode PICKFIRST is pressed
            tap_code(KC_UP);tap_code(KC_ENT);
        } else {
            // when keycode PICKFIRST is released
           if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        }
        break;

    case PICK2ND:
        if (record->event.pressed) {
            tap_code(KC_UP);tap_code(KC_RGHT);tap_code(KC_ENT);
        } else {
           if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
           //PLAY_SONG(PLANCK_SOUND); error in makro
        }
        break;

    case PICK3RD:
        if (record->event.pressed) {
             tap_code(KC_UP);tap_code(KC_RGHT);tap_code(KC_RGHT);tap_code(KC_ENT);
        } else {
           if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        }
        break;
    case CIRCUMFL:
        if (record->event.pressed) {
            if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {tap_code16(S(KC_GRV)); break;}
            tap_code(KC_GRV);
            tap_code(KC_SPC);
            break;
        } else {
           if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
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
        } else {
           if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        }
        break;
    case STICKTICK:
        if (record->event.pressed) {
            tap_code16(S(KC_EQL));
            tap_code(KC_SPC);
            break;
        } else {
           if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
        }
        break;
   case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;   
    }
// lets handel the KEY_HOLD feature keycodes
/*    if (!hold_feature_active) return true;  
    if ((key_hold_lastkey != keycode) || (timer_elapsed(key_hold_dbltap_timer) > (2 * TAPPING_TERM))) key_hold_lastkey = KC_NO;
    switch (keycode) {
            // this is an alternate key on hold feature case KC_A...KC_Z:
            // keys have no autorepeat
            case KC_P: return process_record_hold_key(keycode, record, DE_QUES, 0);	break;
            case KC_J: return process_record_hold_key(keycode, record, KC_PERC, 1);	break;
            case KC_R: return process_record_hold_key(keycode, record, DE_RBRC, 2);	break;
            //case KC_I: return process_record_hold_key(keycode, record, DE_BSLS, 4);	break;
            case KC_B: return process_record_hold_key(keycode, record, DE_PLUS, 3);	break;
            //case KC_F: return process_record_hold_key(keycode, record, S(KC_4), 5);	break;
            case KC_G: return process_record_hold_key(keycode, record, DE_EQL, 6);	break;
            // KC_N                                                             7
            //case KC_S: return process_record_hold_key(keycode, record, DE_SS, 8);	break;
            //case KC_H: return process_record_hold_key(keycode, record, DE_SLSH, 9);	break;
    }
*/
    // return false; // We handled this keypress
    return true; // We didn't handle other keypresses
};
