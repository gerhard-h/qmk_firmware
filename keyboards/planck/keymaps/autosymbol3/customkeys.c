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
    TG_LNAV,
    TG_L4
};
static bool default_layer_moved;
static bool default_layer_movedl4;
static uint16_t caps_lock_on_key = KC_NO;

uint8_t mod_state; // holding the binary representation of active modifiers
static uint8_t caps_state = 0;
bool led_update_user(led_t led_state) {
    if (caps_state != led_state.caps_lock) {
        caps_state = led_state.caps_lock;
    }
    return true;
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
    // return false; // We handled this keypress
    return true; // We didn't handle other keypresses
};
