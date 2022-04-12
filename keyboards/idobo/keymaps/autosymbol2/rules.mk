VIA_ENABLE = no
AUTO_SHIFT_ENABLE = no
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = no
EXTRAKEY_ENABLE = yes
KEY_LOCK_ENABLE = no
# -flto saves ~14% on firmware size
EXTRAFLAGS += -flto
# console might require to disable mouse to fit in memory
CONSOLE_ENABLE = no
RGBLIGHT_ENABLE = yes
COMBO_ENABLE = no
# retest of NKRO no benefits spotted on planck so far
NKRO_ENABLE = no
COMMAND_ENABLE = no
SLEEP_LED_ENABLE = no
#SRC += muse.c