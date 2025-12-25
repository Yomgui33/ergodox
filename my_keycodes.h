#pragma once

#include "quantum.h"

enum layers {
    BASE,  // default layer
    SYMB,  // Symbols
    NAVI,  // Navigation
    ALTF,  // ALT GR replacement
};

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    FR_EFLX,
    FR_UFLX,
    FR_IFLX,
    FR_OFLX,
    FR_AFLX,
    FR_ETRM,
    FR_SUP2,
    INSEC,
    PSLASH,
    UPDIR,
    SLSH,
    COLC,
    COPCOL,
    QU,
    TILDE,
};

enum tap_dance_codes {
    DANCE_0,
};
