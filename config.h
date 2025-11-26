/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#pragma once

// #undef DEBOUNCE
// #define DEBOUNCE 30

#undef TAPPING_TERM
#define TAPPING_TERM 200

// #define ORYX_CONFIGURATOR // needed for RGB

#define DISABLE_LEADER

// #define PERMISSIVE_HOLD

#define USB_SUSPEND_WAKEUP_DELAY 0
#define AUTO_SHIFT_TIMEOUT 200
#define AUTO_SHIFT_MODIFIERS  
#define RGB_MATRIX_STARTUP_SPD 60
#define NO_USB_STARTUP_CHECK = yes
#define COMBO_VARIABLE_LEN
#define LAYER_STATE_16BIT

#undef RGBLIGHT_ANIMATIONS
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE

// reduce firmware size from Thomas Baart
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

// // Prevent normal rollover on alphas from accidentally triggering mods.
// #define IGNORE_MOD_TAP_INTERRUPT
// // Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
// #define TAPPING_FORCE_HOLD
// // Apply the modifier on keys that are tapped during a short hold of a modtap
// #define PERMISSIVE_HOLD
// // Immediately turn on layer if key is pressed quickly
// #define HOLD_ON_OTHER_KEY_PRESS
