# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no       # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output
LTO_ENABLE = no            # Use link time optimization
DEBOUNCE_TYPE = sym_defer_g # sym_eager_pk
LAYOUTS = ortho_5x15
