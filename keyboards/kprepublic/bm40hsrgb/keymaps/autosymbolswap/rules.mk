VIA_ENABLE = no
AUTO_SHIFT_ENABLE = no
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = no
EXTRAKEY_ENABLE = no
KEY_LOCK_ENABLE = yes
# -flto saves ~14% on firmware size
EXTRAFLAGS += -flto
CONSOLE_ENABLE = no
COMBO_ENABLE = no
NKRO_ENABLE = no
COMMAND_ENABLE = no
SLEEP_LED_ENABLE = no
#SRC += muse.c