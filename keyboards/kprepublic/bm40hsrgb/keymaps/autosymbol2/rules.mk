VIA_ENABLE = no
AUTO_SHIFT_ENABLE = no
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = no
EXTRAKEY_ENABLE = yes
KEY_LOCK_ENABLE = no
# qmk compiler optimization -flto saves ~14% on firmware size
EXTRAFLAGS += -flto
# console might require to disable mouse to fit in memory
CONSOLE_ENABLE = no
COMBO_ENABLE = no
# DEBOUNCE and NKRO might be unecessary 
# todo needed at least sym_defer_g on planck -> otimization potential
# retest of NKRO no benefits spotted on planck so far
DEBOUNCE_TYPE = sym_defer_g
NKRO_ENABLE = no
COMMAND_ENABLE = no
SLEEP_LED_ENABLE = no
SWAP_HANDS_ENABLE = yes
#SRC += muse.c