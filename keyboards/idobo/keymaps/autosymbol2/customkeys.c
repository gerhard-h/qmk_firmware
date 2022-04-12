/* custom keycodes (macros) and KEY_HOLD feature are in the same file bc they both modify process_record_user */
// Macros
enum custom_keycodes {
    PICKFIRST = SAFE_RANGE,
    PICK2ND,
    PICK3RD,
    CTLSFTF,
    CIRCUMFL,
    TICKTICK,
    N_RSHFT,
    F_LSHFT
};

static uint16_t n_rshft_timer;
static uint16_t f_lshft_timer;
static bool n_rshft_done;
static bool f_lshft_done;
static bool n_rshft_pressed;
static bool f_lshft_pressed;

uint8_t mod_state; // holding the binary representation of active modifiers

typedef struct {
    uint16_t key_hold_timer;
    bool is_key_hold_active;
    uint16_t key_hold_keycode;
    uint16_t key_tap_keycode;
    bool permit_up; // used to prevent autorepeat
} key_hold_data_t;

// each key needs its own status object
#define HOLD_STAT_USER 10   // ATTENTION adjust array bounds
static key_hold_data_t hold_array[HOLD_STAT_USER] = {0};
static uint16_t key_hold_lastkey = 0;
static uint16_t key_hold_dbltap_timer = 0;                                          
static int hold_active_array[HOLD_STAT_USER];
static int hold_active_max = -1;
static int hold_feature_active = 1;
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
                       if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                       key_hold_lastkey = hold_array[i].key_tap_keycode;
                       hold_array[i].permit_up = false;
                   }
               }   
        }
        
        if (!n_rshft_done &&  f_lshft_pressed && (timer_elapsed(n_rshft_timer) > 240) && (timer_elapsed(n_rshft_timer) < 245)){
          if(timer_elapsed(f_lshft_timer) > timer_elapsed(n_rshft_timer)){ 
           if((get_mods() | get_oneshot_mods()) & MOD_BIT(KC_LSFT)) {
                  tap_code16(DE_LPRN);
                  n_rshft_done = true;
           }
          }
        }
        if (!f_lshft_done && n_rshft_pressed && (timer_elapsed(f_lshft_timer) > 240) && (timer_elapsed(f_lshft_timer) < 245)){
          if(timer_elapsed(f_lshft_timer) < timer_elapsed(n_rshft_timer)){ 
           if((get_mods() | get_oneshot_mods()) & MOD_BIT(KC_LSFT)) {
                  tap_code16(KC_DLR);
                  f_lshft_done = true;
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
                if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                return false;
    	}    
}

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
                n_rshft_pressed = false;      
                unregister_code(KC_RSFT); // Change the key that was held here, too!
                if (timer_elapsed(n_rshft_timer) < 120 ) {  // < TAPPING_TERM
                  dprintf("N tap ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                  dprintf("N tap diff: %u ls: %u rs: %u\n", f_lshft_timer - n_rshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
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
                  tap_code16(KC_N); // enable dbl tap ff
                  n_rshft_done = true;
                } else        
                if ((get_mods() | get_oneshot_mods()) & MOD_BIT(KC_LSFT)) {
                  if(!n_rshft_done){
                        tap_code16(DE_LPRN);
                        n_rshft_done = true;
                  }
                }
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
                f_lshft_pressed = false;
                unregister_code(KC_LSFT); // Change the key that was held here, too!
                if (timer_elapsed(f_lshft_timer) < 120 ) {  // < TAPPING_TERM
                  dprintf("F tap ft: %u nt: %u pressed: %b time: %u\n", f_lshft_timer, n_rshft_timer, record->event.pressed, record->event.time);
                  dprintf("F tap diff: %u ls: %u rs: %u\n", n_rshft_timer - f_lshft_timer, mod_state & MOD_BIT(KC_LSFT), mod_state & MOD_BIT(KC_RSFT));
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
                } else        
                if ((get_mods() | get_oneshot_mods()) & MOD_BIT(KC_RSFT )) {
                  if(!f_lshft_done){
                        tap_code16(KC_DLR);
                        f_lshft_done = true;
                  }      
                }
                return false;
              }
              break;
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
    }
// second lets handel the KEY_HOLD feature keycodes
    if (!hold_feature_active) return true;  
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
    // return false; // We handled this keypress
    return true; // We didn't handle other keypresses
};
 