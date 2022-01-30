#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4

// LED strip stuff
#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_HUE_STEP 6
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 20
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 6
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 6
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 6
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 2000
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 1
#endif

#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 210
//#define MOD_CODE_DELAY 0
// # define TAP_CODE_DELAY 10 //will not fix Remotedesktop timings
// #define USB_POLLING_INTERVAL_MS 10 # tried 1 and 10 both resourceheavy or it's just NKRO
//#define AUTO_SHIFT_TIMEOUT 140
//#define AUTO_SHIFT_NO_AUTO_REPEAT
//#define NO_AUTO_SHIFT_NUMERIC
//#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define NO_ACTION_MACRO //disable old-style macro handling using MACRO(), action_get_macro() (deprecated) EXTRAFLAGS += -flto
#define NO_ACTION_FUNCTION //disable old-style function handling using fn_actions, action_function() (deprecated) EXTRAFLAGS += -flto
//#define TAPPING_FORCE_HOLD // gives the hold behavior priority over the keyrepeat behavior. eg. to get dünn instead of ddun with LT(1,KC_D)

/* enable home row mods */
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */
//#define LEADER_TIMEOUT 500
///#define EXTRA_SHORT_COMBOS // Defining EXTRA_SHORT_COMBOS combines a combo's internal state into just one byte. This can, in some cases, save some memory. If it doesn't, no point using it.
//#define COMBO_TERM 100 // default 50