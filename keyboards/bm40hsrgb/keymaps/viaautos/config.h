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

#define TAPPING_TERM 200
// # define TAP_CODE_DELAY 10 //will not fix Remotedesktop timings
#define AUTO_SHIFT_TIMEOUT 150 //overwrite in C:\Users\heideg\qmk_firmware\quantum\process_keycode\process_auto_shift.h
#define AUTO_SHIFT_NO_AUTO_REPEAT
#define NO_AUTO_SHIFT_NUMERIC
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define NO_ACTION_MACRO //disable old-style macro handling using MACRO(), action_get_macro() (deprecated) EXTRAFLAGS += -flto
#define NO_ACTION_FUNCTION //disable old-style function handling using fn_actions, action_function() (deprecated) EXTRAFLAGS += -flto


#define TAPPING_FORCE_HOLD // gives the hold behavior priority over the keyrepeat behavior.
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD