// Tap Hold functionality by Jonas Hietala
// Chech his layout ideas here :
// www.jonashietala.se
// https://github.com/treeman/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/treeman

// #include <stdint.h>

// Current version : 1.1.8
// compile : qmk compile -kb ergodox_ez/glow -km guillaume

#include QMK_KEYBOARD_H

#include "keymap_french_afnor.h"
#include "sendstring_french_afnor.h"
#include "my_keycodes.h"
#include "g/keymap_combo.h"
#include "tap_hold.h"
#include "rgb_lights.h"
#include "tap_dances.h"
#include "version.h"

tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
};

#ifdef RGB_MATRIX_ENABLE

// LED du pavé numérique sur SYMB : 1234567890./-*+=
static const uint8_t numpad_digits[] PROGMEM = {
    16, // 1
    17, // 2
    18, // 3
    11, // 4
    12, // 5
    13, // 6
    6,  // 7
    7,  // 8
    8,  // 9
    20, // 0
    21  // .
};

static const uint8_t numpad_ops[] PROGMEM = {
    5,  // /
    9,  // *
    10, // -
    14, // +
    15  // =
};

bool rgb_matrix_indicators_user(void) {
    if (!rgb_matrix_is_enabled()) {
        return false;
    }

    uint8_t highest = get_highest_layer(layer_state);

    // 1) BASE = toujours éteinte
    if (highest == BASE) {
        rgb_matrix_set_color_all(0, 0, 0);
        return false;
    }

    // 2) NAVI = toujours éteinte
    if (highest == NAVI) {
        rgb_matrix_set_color_all(0, 0, 0);
        return false;
    }

    // 3) ALTF = toujours éteinte
    if (highest == ALTF) {
        rgb_matrix_set_color_all(0, 0, 0);
        return false;
    }

    // 4) SYMB = éclairage personnalisé (rouge / blanc)
    if (highest == SYMB) {
        // Éteindre tout
        rgb_matrix_set_color_all(0, 0, 0);

        // Chiffres en rouge
        for (uint8_t i = 0; i < sizeof(numpad_digits); i++) {
            uint8_t led = pgm_read_byte(&numpad_digits[i]);
            rgb_matrix_set_color(led, 255, 0, 0); // rouge
        }

        // Opérateurs / ponctuation en blanc
        for (uint8_t i = 0; i < sizeof(numpad_ops); i++) {
            uint8_t led = pgm_read_byte(&numpad_ops[i]);
            rgb_matrix_set_color(led, 255, 255, 255); // blanc
        }

        return false; // on garde ce design
    }

    // 5) Layers restantes → RGB par défaut
    return true;
}

#endif



static bool     is_alt_tab_active = false;
static uint16_t alt_tab_timer     = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base layer
 */
[BASE] = LAYOUT_ergodox_pretty(
  // left hand
    KC_ESC,         FR_AMPR,        FR_EACU,        FR_DQUO,        FR_QUOT,        FR_LPRN,        KC_LGUI,                                        OSM(MOD_RALT),  FR_MINS,        FR_EGRV,        FR_UNDS,        FR_CCED,        FR_AGRV,        KC_TRANSPARENT,
    KC_TAB,         FR_W,           FR_QUOT,        FR_E,           FR_R,           FR_T,           OSM(MOD_LSFT),                                  OSM(MOD_RSFT),  FR_Y,           FR_U,           FR_I,           FR_O,           KC_TRANSPARENT, FR_DIAE,
    KC_ESC,         FR_A,           FR_S,           FR_D,           FR_F,           FR_G,                                                                           FR_J,           FR_H,           FR_C,           FR_L,           FR_M,           LCTL(LGUI(FR_K)),
    TT(SYMB),       QU,             FR_X,           FR_C,           FR_V,           FR_B,           OSM(MOD_LCTL),                                  OSM(MOD_RCTL),  KC_LGUI,        FR_N,           FR_Z,           PSLASH,         FR_P,           TT(SYMB),
    FR_SUP2,        FR_LABK,        ALT_TAB,        TD(DANCE_0),    LT(NAVI, KC_BSPC),                                                                                            OSL(ALTF),      KC_LCTL,        KC_LSFT,        FR_DLR,         KC_TRNS,
                                                                                                    LCTL(FR_Z),       LCTL(FR_Y),         KC_PAUSE,       KC_APPLICATION,
                                                                                                                      KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,
                                                                                    KC_ENTER,       LCTL(LGUI(KC_X)), KC_INS,             KC_SCROLL_LOCK,  LGUI(KC_E),     KC_SPACE
),
[SYMB] = LAYOUT_ergodox_pretty(
    KC_TRNS,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,                                  KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_TRNS,
    KC_TAB,     FR_HASH,    FR_EXLM,    FR_LBRC,    FR_RBRC,    FR_SLSH,    TILDE,                                KC_LSFT,    KC_PSLS,    KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_PAST,    KC_TRNS,
    KC_ESCAPE,  FR_LABK,    FR_RABK,    FR_LPRN,    FR_RPRN,    FR_BSLS,                                                         KC_PMNS,    KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_KP_PLUS, KC_F12,
    KC_TRNS,    KC_TRNS,    S(KC_LBRC), FR_LCBR,    FR_RCBR,    SLSH,       UPDIR,                                  KC_LCTL,    FR_EQL,     KC_KP_1,    KC_KP_2,    KC_KP_3,    COLC,       KC_TRNS,
    KC_ASTR,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                                                                                KC_KP_0,    KC_KP_DOT,  FR_COMM,    KC_TRNS,    KC_TRNS,
                                                                            RM_HUEU,    RM_HUED,            RM_TOGG, KC_PAUSE,
                                                                                        KC_TRNS,            KC_CAPS,
                                                                KC_TRNS,    KC_TRNS,    QK_BOOT,              KC_NUM,  KC_TRNS,   KC_TRNS
),
[NAVI] = LAYOUT_ergodox_pretty(
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                                 KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                                 KC_TRNS,   KC_PGUP,    KC_HOME,    KC_UP,      KC_END,     KC_TRNS,    KC_TRNS,
    KC_DELETE,  KC_TRNS,    KC_TRNS,    KC_LCTL,    KC_LSFT,    KC_TRNS,                                                        KC_PGDN,    KC_LEFT,    KC_DOWN,    KC_RIGHT,   KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    LCTL(FR_X), LCTL(FR_C), LCTL(FR_V), KC_TRNS,    KC_TRNS,                                 KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                                                                                KC_DELETE,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,            KC_TRNS, KC_TRNS,
                                                                                        KC_TRNS,            KC_TRNS,
                                                                KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS, KC_TRNS,   INSEC
),
[ALTF] = LAYOUT_ergodox_pretty(
    KC_TRNS,    FR_AMPR,    FR_PERC,    FR_HASH,    FR_LCBR,    FR_LBRC,    KC_TRNS,                                 KC_TRNS,   FR_PIPE,    FR_GRV,     FR_BSLS,    FR_DCIR,    FR_AT,      FR_RCBR,
    KC_TRNS,    KC_TRNS,    FR_EACU,    FR_EGRV,    FR_EFLX,    FR_ETRM,    KC_TRNS,                                 KC_TRNS,   KC_TRNS,    FR_UFLX,    FR_IFLX,    FR_OFLX,    KC_TRNS,    KC_TRNS,
    KC_DELETE,  FR_AGRV,    FR_AFLX,    FR_DLR,     FR_MINS,    KC_TRNS,                                                        KC_TRNS,    FR_UGRV,    FR_CCED,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    FR_Q,       LCTL(FR_X), LCTL(FR_C), LCTL(FR_V), KC_TRNS,    KC_TRNS,                                 KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_DELETE,                                                                              KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                            KC_TRNS,    KC_TRNS,            KC_TRNS, KC_TRNS,
                                                                                        KC_TRNS,            KC_TRNS,
                                                                KC_TRNS,    KC_TRNS,    KC_TRNS,            KC_TRNS, KC_TRNS,   KC_TRNS
),
};
// clang-format on

// Tap hold

bool tap_hold(uint16_t keycode) {
    switch (keycode) {
        case FR_ETRM:
        case FR_EFLX:
        case FR_UFLX:
        case FR_IFLX:
        case FR_OFLX:
        case FR_AFLX:
        case FR_AGRV:
        case FR_UGRV:
        case FR_EGRV:
        case FR_EACU:
        case FR_CCED:
        case FR_LCBR:
        case FR_LBRC:
        case FR_SUP2:
        case PSLASH:
        case SLSH:
        case COLC:
        case QU:
        case COPCOL:
        case KC_KP_1:
        case KC_KP_2:
        case KC_KP_3:
        case KC_KP_4:
        case KC_KP_5:
        case KC_KP_6:
        case KC_KP_7:
        case KC_KP_8:
        case KC_KP_9:
        case KC_PAST:
        case KC_KP_PLUS:
            return true;
        default:
            return false;
    }
}

void tap_hold_send_tap(uint16_t keycode) {
    switch (keycode) {
        case QU:                    // qu
            send_string("qu");
            return;
        case FR_SUP2:               // ²
            tap_code16(FR_DCIR);
            tap_code16(FR_2);
            return;
        case SLSH:                  // symbols /
            tap_code16(FR_SLSH);
            return;
        case COLC:                  // symbols :
            tap_code16(FR_COLN);
            return;
        case PSLASH:                // base : et /
            tap_code16(FR_COLN);
            return;
        case FR_ETRM:
            tap_code16(S(FR_DCIR));
            tap_code16(FR_E);
            return;
        case FR_EFLX:
            tap_code(FR_DCIR);
            tap_code(FR_E);
            return;
        case FR_UFLX:
            tap_code(FR_DCIR);
            tap_code16(FR_U);
            return;
        case FR_IFLX:
            tap_code(FR_DCIR);
            tap_code16(FR_I);
            return;
        case FR_OFLX:
            tap_code(FR_DCIR);
            tap_code16(FR_O);
            return;
        case FR_AFLX:
            tap_code(FR_DCIR);
            tap_code16(FR_A);
            return;
        case FR_AGRV:
            tap_code16(FR_AGRV);
            return;
        case FR_UGRV:
            tap_code16(FR_GRV);
            tap_code16(FR_U);
            return;
        case FR_EGRV:
            tap_code16(FR_EGRV);
            return;
        case FR_EACU:
            tap_code16(FR_EACU);
            return;
        case FR_CCED:
            tap_code16(FR_CCED);
            return;
        case COPCOL:
            tap_code16(LCTL(KC_C));
            return;
        default:
            tap_code16(keycode);
    }
}

void tap_hold_send_hold(uint16_t keycode) {
    switch (keycode) {
        case QU:
            send_string("Qu");
            return;
        case FR_SUP2:
            tap_code16(FR_DCIR);
            tap_code16(FR_2);
            return;
        case SLSH:
            tap_code16(FR_BSLS);
            return;
        case COLC:
            tap_code16(FR_SCLN);
            return;
        case PSLASH:
            tap_code16(FR_SLSH);
            return;
        case FR_ETRM:
            tap_code16(S(FR_DCIR));
            tap_code16(S(FR_E));
            return;
        case FR_EFLX:
            tap_code(FR_DCIR);
            tap_code16(S(FR_E));
            return;
        case FR_UFLX:
            tap_code(FR_DCIR);
            tap_code16(S(FR_U));
            return;
        case FR_IFLX:
            tap_code(FR_DCIR);
            tap_code16(S(FR_I));
            return;
        case FR_OFLX:
            tap_code(FR_DCIR);
            tap_code16(S(FR_O));
            return;
        case FR_AFLX:
            tap_code(FR_DCIR);
            tap_code16(S(FR_A));
            return;
        case FR_AGRV:
            tap_code16(S(ALGR(FR_AGRV)));
            return;
        case FR_UGRV:
            tap_code16(FR_GRV);
            tap_code16(S(FR_U));
            return;
        case FR_EGRV:
            tap_code16(FR_GRV);
            tap_code16(S(FR_E));
            return;
        case FR_EACU:
            tap_code16(FR_ACUT);
            tap_code16(S(FR_E));
            return;
        case FR_CCED:
            tap_code16(S(FR_CCED));
            return;
        case COPCOL:
            tap_code16(LCTL(KC_V));
            return;
        case KC_KP_1:
            tap_code(KC_F1);
            return;
        case KC_KP_2:
            tap_code(KC_F2);
            return;
        case KC_KP_3:
            tap_code(KC_F3);
            return;
        case KC_KP_4:
            tap_code(KC_F4);
            return;
        case KC_KP_5:
            tap_code(KC_F5);
            return;
        case KC_KP_6:
            tap_code(KC_F6);
            return;
        case KC_KP_7:
            tap_code(KC_F7);
            return;
        case KC_KP_8:
            tap_code(KC_F8);
            return;
        case KC_KP_9:
            tap_code(KC_F9);
            return;
        case KC_PAST:
            tap_code(KC_F10);
            return;
        case KC_KP_PLUS:
            tap_code(KC_F11);
            return;
       default:
            tap_code16(S(keycode));
    }
}

uint16_t tap_hold_timeout(uint16_t keycode) {
    switch (keycode) {
        case FR_ETRM:
        case FR_EFLX:
        case FR_UFLX:
        case FR_IFLX:
        case FR_OFLX:
        case FR_AFLX:
        case FR_AGRV:
        case FR_UGRV:
        case FR_EGRV:
        case FR_EACU:
        case FR_CCED:
        case FR_LCBR:
        case FR_LBRC:
        case PSLASH:
        case SLSH:
        case COLC:
        case QU:
            return 200;
        default:
            return 200;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_tap_hold(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            // Allow further processing of ALT_TAB if needed
            break;

        case INSEC:
            if (record->event.pressed) {
                tap_code16(RSA(KC_SPC));
            }
            return false;

        case UPDIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;

        case TILDE:
            if (record->event.pressed) {
                // AFNOR: AltGr+N pour ~ dead key, puis espace pour le produire
                register_code(KC_RALT);
                tap_code(KC_N);
                unregister_code(KC_RALT);
                wait_ms(10);
                tap_code(KC_SPC);
            }
            return false;

    }

    return true;
}


void matrix_scan_user(void) {

  tap_hold_matrix_scan();

  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 600) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}
