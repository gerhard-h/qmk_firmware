VIA_ENABLE = no
AUTO_SHIFT_ENABLE = no
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = no
EXTRAKEY_ENABLE = yes
KEY_LOCK_ENABLE = no
# flashing once was more succecesfull with qmktoolbox version 0.0.21 or there is a size limit around 54kb to 58kb
# qmk compiler optimization before 58.176 Bytes after 53.964 ~ 7%
LTO_ENABLE=yes
# run "qmk console" to see the output disable to save firmware size
# CONSOLE_ENABLE = no
COMBO_ENABLE = no
# DEBOUNCE and NKRO might be unecessary 
# todo needed at least sym_defer_g on planck -> otimization potential
# retest of NKRO no benefits spotted on planck so far
DEBOUNCE_TYPE = sym_defer_g
NKRO_ENABLE = no
COMMAND_ENABLE = no
SLEEP_LED_ENABLE = no
#Plank SWAP_HANDS is not usable
SWAP_HANDS_ENABLE = no
#Plank Audio is not usable BEEP on RESET is the only feature active
AUDIO_ENABLE = yes
#SRC += muse.c
BACKLIGHT_ENABLE = yes      # Enable keyboard backlight functionality