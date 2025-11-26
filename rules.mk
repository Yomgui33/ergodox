# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

VPATH  +=  keyboards/gboards/

WPM_ENABLE = no
LTO_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUTO_SHIFT_ENABLE = yes
# SRC = matrix.c
COMBO_ENABLE = yes
MOUSEKEY_ENABLE = no
TAP_DANCE_ENABLE = yes
POINTING_DEVICE_ENABLE = no

RGB_MATRIX_ENABLE = yes

EXTRAFLAGS += -flto
VERBOSE = no
DEBUG_MATRIX_SCAN_RATE  = no
DEBUG_MATRIX = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
SWAP_HANDS_ENABLE = no
RGBLIGHT_ENABLE = no

SRC += tap_hold.c