#define DISABLE_RGB_MATRIX_ALPHAS_MODS
#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define DISABLE_RGB_MATRIX_BREATHING
#define DISABLE_RGB_MATRIX_BAND_SAT
#define DISABLE_RGB_MATRIX_BAND_VAL
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define DISABLE_RGB_MATRIX_CYCLE_ALL
#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
//#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
//#define DISABLE_RGB_MATRIX_DUAL_BEACON
#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
//#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
//#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define DISABLE_RGB_MATRIX_RAINDROPS
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS // DO NOT ENABLE
#define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH

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
#define IGNORE_MOD_TAP_INTERRUPT  // affects MT() ~ ALT 
#define PERMISSIVE_HOLD           // affects tap dance (but seems to have no effect here)
//#define HOLD_ON_OTHER_KEY_PRESS // negative effect on MT() ~ too many ALT

#define ONESHOT_TAP_TOGGLE 3  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */
//#define LEADER_TIMEOUT 500
///#define EXTRA_SHORT_COMBOS // Defining EXTRA_SHORT_COMBOS combines a combo's internal state into just one byte. This can, in some cases, save some memory. If it doesn't, no point using it.
//#define COMBO_TERM 100 // default 50