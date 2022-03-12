/* custom KEY_HOLD feature functions must be used in process_record_user */

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
void key_hold_matrix_scan_user(void) {
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
}

bool process_record_hold_key(uint16_t keycode, keyrecord_t *record, uint16_t keycode2, int hold_status ){
    if (record->event.pressed) {
                hold_array[hold_status].key_tap_keycode =  keycode;
                if (get_mods() | get_oneshot_mods()) { // If key was held and no mods
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

 