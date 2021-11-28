/* custom keycodes (macros) and KEY_HOLD feature are in the same file bc they both modify process_record_user */
// Macros
enum custom_keycodes {
    PICKFIRST = SAFE_RANGE,
    PICK2ND,
    PICK3RD,
    CTLSFTF,
    CIRCUMFL,
    TICKTICK,
};

typedef struct {
    uint16_t key_hold_timer;
    bool is_key_hold_active;
    uint16_t key_hold_keycode;
    uint16_t key_tap_keycode;
    bool permit_up; // used to prevent autorepeat
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
    case KC_P: return process_record_hold_key(keycode, record, DE_QUES, 0);	break;
    case KC_J: return process_record_hold_key(keycode, record, KC_PERC, 1);	break;
    case KC_R: return process_record_hold_key(keycode, record, DE_RBRC, 2);	break;
    case KC_I: return process_record_hold_key(keycode, record, DE_BSLS, 4);	break;
    case KC_B: return process_record_hold_key(keycode, record, DE_PLUS, 3);	break;
    //case KC_T: return process_record_hold_key(keycode, record, DE_RPRN, 4);	break;
    //case KC_F: return process_record_hold_key(keycode, record, S(KC_4), 5);	break;
    case KC_G: return process_record_hold_key(keycode, record, DE_EQL, 6);	break;
    //case KC_D: return process_record_hold_key(keycode, record, ALGR(KC_NUBS), 7);	break;
    case KC_S: return process_record_hold_key(keycode, record, DE_SS, 8);	break;
    case KC_H: return process_record_hold_key(keycode, record, DE_SLSH, 9);	break;
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
 