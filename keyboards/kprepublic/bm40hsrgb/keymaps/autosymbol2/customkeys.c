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
    F_LSHFT
};
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
// force home row shift even if shift key is already released
bool force_shift_tap( uint16_t keycode, bool sft_done, bool sft_pressed, bool only_register, uint16_t shft_up_timer) {
        
        if ( !sft_done && !sft_pressed && timer_elapsed(shft_up_timer) < 300 && timer_elapsed(shft_used_timer) > 300 ) {
                                        dprintf("TD force SFT  \n");
                                        if(only_register){
                                                register_code16(S(keycode));
                                        } else {
                                                tap_code16(S(keycode));
                                        }
                                        shft_used_timer = timer_read();
                                        return true;
        }
        return false;
}
bool force_leftside_shift_tap( uint16_t keycode, bool only_register) {
        dprintf("TD left side tap keycode: %u done: %b pressed: %b rshft_up_timer: %u shft_used_timer: %u limit: 300\n", keycode, n_rshft_done,n_rshft_pressed,  timer_elapsed(rshft_up_timer), timer_elapsed(shft_used_timer));
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
                                return force_shift_tap( keycode, n_rshft_done, n_rshft_pressed, only_register, rshft_up_timer);
                        default:
                                dprintf("TD left side tap keycode: %u is ignored bc it is not left side\n", keycode);
                                return false;
        }
}
bool force_rightside_shift_tap( uint16_t keycode, bool only_register) {
        dprintf("TD right side tap keycode: %u done: %b pressed: %b lshft_up_timer: %u shft_used_timer: %u limit: 300\n", keycode, f_lshft_done,f_lshft_pressed,  timer_elapsed(lshft_up_timer), timer_elapsed(shft_used_timer));
                switch (keycode) {
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
                        case MT(MOD_LALT, KC_K):
                        case KC_M:
                        case KC_COMM:
                        case KC_DOT:
                                return force_shift_tap( keycode, f_lshft_done, f_lshft_pressed, only_register, lshft_up_timer);
                        default:
                                dprintf("TD right side tap keycode: %u is ignored bc it is not right side\n", keycode);
                                return false;
        }
}
void handle_force_shift_tap( uint16_t keycode, bool only_register) {
        if ( force_leftside_shift_tap(keycode, false)) {return;}
        if ( force_rightside_shift_tap(keycode, false)) {return;}
        if( f_lshft_pressed || n_rshft_pressed){shft_used_timer = timer_read();}
        if( only_register ) {
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
   // Store the current modifier state in the variable for later reference
    mod_state = get_mods();
   // first lets handel custom keycodes
   switch (keycode) {
        case N_RSHFT:
              if(record->event.pressed) {
                n_rshft_pressed = true;      
                n_rshft_done = false;
                n_rshft_timer = timer_read();
                dprintf("N down ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                register_code(KC_RSFT); // Change the key to be held here
              } else {
                rshft_up_timer = timer_read();
                n_rshft_pressed = false;      
                unregister_code(KC_RSFT); // Change the key that was held here, too!
                if (timer_elapsed(n_rshft_timer) < 120 ) {  // < TAPPING_TERM
                  dprintf("N tap ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                  dprintf("N tap diff: %u ls: %u rs: %u\n", f_lshft_timer - n_rshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
                  // if F (lsft) was pressed after N-down but before N-up don't shift N
                  if( n_rshft_timer < f_lshft_timer && f_lshft_timer - n_rshft_timer < 80){
                        unregister_code(KC_LSFT);
                        tap_code16(KC_N);
                        register_code(KC_LSFT);
                  } else {
                        tap_code16(KC_N); // Change the character(s) to be sent on tap here
                  }
                  n_rshft_done = true;
                } else 
                if (timer_elapsed(n_rshft_timer) < 240 ) {  // < TAPPING_TERM x 2
                  tap_code16(KC_N); // enable dbl tap nn
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
        case F_LSHFT:
              if(record->event.pressed) {
                f_lshft_pressed = true;     
                f_lshft_done = false;     
                f_lshft_timer = timer_read();
                register_code(KC_LSFT); // Change the key to be held here
                dprintf("F down ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
              } else {
                lshft_up_timer = timer_read();
                f_lshft_pressed = false;
                unregister_code(KC_LSFT); // Change the key that was held here, too!
                if (timer_elapsed(f_lshft_timer) < 120 ) {  // < TAPPING_TERM
                  dprintf("F tap ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                  dprintf("F tap diff: %u ls: %u rs: %u\n", n_rshft_timer - f_lshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
                  // if N (rsft) was pressed after F-down but before F-up don't shift F
                  if( f_lshft_timer < n_rshft_timer && n_rshft_timer - f_lshft_timer < 80){
                        unregister_code(KC_RSFT);
                        tap_code16(KC_F);
                        register_code(KC_RSFT);
                  } else {
                        tap_code16(KC_F); // Change the character(s) to be sent on tap here
                  }
                  f_lshft_done = true;
                } else 
                if (timer_elapsed(f_lshft_timer) < 240 ) {  // < TAPPING_TERM x 2
                          tap_code16(KC_F); // enable dbl tap ff
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
        case DF(_LNAV):
                if (record->event.pressed) {
                    tap_code(KC_NUMLOCK);
                }
                return true;
        case DF(_L0):
                if (record->event.pressed) {
                   if (IS_HOST_LED_ON(USB_LED_NUM_LOCK) == true){
                    tap_code(KC_NUMLOCK);
                   }
                }
                return true;
        case MT(MOD_LALT, KC_K):
            if (record->tap.count && record->event.pressed) {
                // Intercept tap function
                if ( force_rightside_shift_tap(KC_K, false)) {return false;}
                if( f_lshft_pressed || n_rshft_pressed){shft_used_timer = timer_read();}
            }
            return true;             // Return true for normal processing of tap keycode

            /*else if (record->event.pressed) {
                tap_code16(ALGR(KC_E)); // Intercept hold function to send Ctrl-V
            }
            
            return false;*/
            
        /* S(BSP) = DEL ... tends to be more confusing than helpfull   
        case KC_BSPC:
        {
        // Initialize a boolean variable that keeps track
        // of the delete key status: registered or not?
        static bool delkey_registered;
        if (record->event.pressed) {
            // Detect the activation of either shift keys
            if (mod_state & MOD_MASK_SHIFT) {
                // First temporarily canceling both shifts so that
                // shift isn't applied to the KC_DEL keycode
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_DEL);
                // Update the boolean variable to reflect the status of KC_DEL
                delkey_registered = true;
                // Reapplying modifier state so that the held shift key(s)
                // still work even after having tapped the Backspace/Delete key.
                set_mods(mod_state);
                return false;
            }
        } else { // on release of KC_BSPC
            // In case KC_DEL is still being sent even after the release of KC_BSPC
            if (delkey_registered) {
                unregister_code(KC_DEL);
                delkey_registered = false;
                return false;
            }
        }
        // Let QMK process the KC_BSPC keycode as usual outside of shift
        return true;
    }
    */
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
        
    case CTLSFTF:
        if (record->event.pressed) {
             register_mods(MOD_BIT(KC_LCTL));
             register_mods(MOD_BIT(KC_LSFT));
             tap_code(KC_F);             
             unregister_mods(MOD_BIT(KC_LSFT));
             unregister_mods(MOD_BIT(KC_LCTL));
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
  case KC_0..KC_9:
        if (record->event.pressed) {
                if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK) == true){
                        caps_lock_on_key = keycode;
                        tap_code16(KC_CAPS);
        } else {
                if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK) == true  && caps_lock_on_key == keycode){
                        tap_code16(KC_CAPS);
                }      
        }
        break;    
   case KC_CAPS:
        if (record->event.pressed) {
                caps_lock_on_key = KC_CAPS;
        }
        break;    
  }
// second lets handel the KEY_HOLD feature keycodes
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
