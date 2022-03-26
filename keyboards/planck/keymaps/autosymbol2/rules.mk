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
# CONSOLE_ENABLE = yes
COMBO_ENABLE = no
NKRO_ENABLE = no
COMMAND_ENABLE = no
SLEEP_LED_ENABLE = no
SWAP_HANDS_ENABLE = no
#SRC += muse.c