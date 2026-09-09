#include QMK_KEYBOARD_H

enum layers {
    _BASE = 0,
    _CYRILLIC,
    _LOWER,
    _RAISE,
    _ADJUST,
    _SIGN
};

enum {
    TD_CYR_E = 0,
    TD_CYR_SH = 1,
    TD_CYR_SO = 2,
    TD_CYR_SWITCH = 3,
    TD_BASE_SWITCH = 4,
    TD_EMPTY_CYR_SWITCH = 5,
    TD_EMPTY_BASE_SWITCH = 6,
    TD_SCROLL = 7,
    TD_SNIPE = 8,
    TD_CARRET = 9,
    TD_NAVIGATE = 10,
    TD_VOLUME = 11,
    TD_SIGNQ = 12,
    TD_SIGN = 13,
    TD_US_J = 14,
    TD_US_I = 15,
    TD_5 = 16
};

enum custom_keycodes {
    KC_SCROLL = SAFE_RANGE,
    KC_SNIPE,
    KC_CARRET,
    KC_NAVIGATE,
    KC_VOLUME,
    KC_CDOT,
    KC_CCOMM,
    KC_CQUES,
    KC_CEXLM,
    KC_CMINS,
    KC_CPLUS,
    KC_CUNDS,
    KC_CEQL,
    KC_CSLSH,
    KC_CBSLS,
    KC_CPIPE,
    KC_CAMPR,
    KC_CCIRC,
    KC_CASTR,
    KC_CLPRN,
    KC_CRPRN,
    KC_CSCLN,
    KC_CCOLN,
    KC_CQUOT,
    KC_CDQUO,
    KC_CLBRC,
    KC_CRBRC,
    KC_CLCBR,
    KC_CRCBR,
    KC_CTILD,
    KC_CGRV,
    KC_CLABK,
    KC_CRABK,
    KC_CHASH,
    KC_CNUM,
    KC_CAT,
    KC_CDLR,
    KC_CPERC,
    KC_MMO,
    KC_RTS,
    KC_US,
    KC_RU,
    KC_SCROLL_UP,
    KC_SCROLL_DOWN
};

static bool is_scrolling = false;
static bool is_sniping = false;
static uint16_t base_cpi = 400;
static uint16_t normal_cpi = 400;
static uint16_t snipe_cpi = 100;
static uint16_t game_normal_cpi = 800;
static uint16_t game_snipe_cpi = 100;

static bool is_carret_mode = false;
static bool is_navigate_mode = false;
static bool is_volume_mode = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_SCROLL) {
        if (record->event.pressed) {
            is_scrolling = true;
            pointing_device_set_cpi(1);
        } else {
            is_scrolling = false;
            pointing_device_set_cpi(base_cpi);
        }
        return false;
    }
    if (keycode == KC_SNIPE) {
        if (record->event.pressed) {
            is_sniping = true;
            pointing_device_set_cpi(game_snipe_cpi);
        } else {
            is_sniping = false;
            pointing_device_set_cpi(game_normal_cpi);
        }
        return false;
    }
    if (keycode == KC_CARRET) {
        if (record->event.pressed) {
            is_carret_mode = true;
            pointing_device_set_cpi(50);
        } else {
            is_carret_mode = false;
            pointing_device_set_cpi(normal_cpi);
        }
        return false;
    }
    if (keycode == KC_NAVIGATE) {
        if (record->event.pressed) {
            is_navigate_mode = true;
            pointing_device_set_cpi(5);
        } else {
            is_navigate_mode = false;
            pointing_device_set_cpi(base_cpi);
        }
        return false;
    }
    if (keycode == KC_VOLUME) {
        if (record->event.pressed) {
            is_volume_mode = true;
            pointing_device_set_cpi(5);
        } else {
            is_volume_mode = false;
            pointing_device_set_cpi(normal_cpi);
        }
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case KC_CDOT: SEND_STRING("."); return false;
            case KC_CCOMM: SEND_STRING(","); return false;
            case KC_CQUES: SEND_STRING("?"); return false;
            case KC_CEXLM: SEND_STRING("!"); return false;
            case KC_CMINS: SEND_STRING("-"); return false;
            case KC_CPLUS: SEND_STRING("+"); return false;
            case KC_CUNDS: SEND_STRING("_"); return false;
            case KC_CEQL: SEND_STRING("="); return false;
            case KC_CSLSH: SEND_STRING("/"); return false;
            case KC_CBSLS: SEND_STRING("\\"); return false;
            case KC_CPIPE: SEND_STRING("|"); return false;
            case KC_CAMPR: SEND_STRING("&"); return false;
            case KC_CCIRC: SEND_STRING("^"); return false;
            case KC_CASTR: SEND_STRING("*"); return false;
            case KC_CLPRN: SEND_STRING("("); return false;
            case KC_CRPRN: SEND_STRING(")"); return false;
            case KC_CSCLN: SEND_STRING(";"); return false;
            case KC_CCOLN: SEND_STRING(":"); return false;
            case KC_CQUOT: SEND_STRING("'"); return false;
            case KC_CDQUO: SEND_STRING("\""); return false;
            case KC_CLBRC: SEND_STRING("["); return false;
            case KC_CRBRC: SEND_STRING("]"); return false;
            case KC_CLCBR: SEND_STRING("{"); return false;
            case KC_CRCBR: SEND_STRING("}"); return false;
            case KC_CTILD: SEND_STRING("~"); return false;
            case KC_CGRV: SEND_STRING("`"); return false;
            case KC_CLABK: SEND_STRING("<"); return false;
            case KC_CRABK: SEND_STRING(">"); return false;
            case KC_CHASH: SEND_STRING("#"); return false;
            case KC_CNUM: SEND_STRING(SS_LCTL(SS_LSFT("u")) "2116" SS_TAP(X_SPACE)); return false;
            case KC_CAT: SEND_STRING("@"); return false;
            case KC_CDLR: SEND_STRING("$"); return false;
            case KC_CPERC: SEND_STRING("%"); return false;
            case KC_MMO:
                base_cpi = game_normal_cpi;
                pointing_device_set_cpi(game_normal_cpi);
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_1);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                register_code(KC_LGUI);
                tap_code(KC_C);
                unregister_code(KC_LGUI);
                layer_move(_LOWER);
                rgb_matrix_sethsv_noeeprom(0, 255, 50);
                return false;
            case KC_RTS:
                base_cpi = game_normal_cpi;
                pointing_device_set_cpi(game_normal_cpi);
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_1);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                register_code(KC_LGUI);
                tap_code(KC_C);
                unregister_code(KC_LGUI);
                layer_move(_RAISE);
                rgb_matrix_sethsv_noeeprom(85, 255, 50);
                return false;
            case KC_US:
                base_cpi = normal_cpi;
                pointing_device_set_cpi(normal_cpi);
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_1);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                register_code(KC_LGUI);
                tap_code(KC_D);
                unregister_code(KC_LGUI);
                layer_move(_BASE);
                rgb_matrix_sethsv_noeeprom(0, 255, 50);
                return false;
            case KC_RU:
                base_cpi = normal_cpi;
                pointing_device_set_cpi(normal_cpi);
                register_code(KC_LCTL);
                register_code(KC_LALT);
                register_code(KC_LSFT);
                tap_code(KC_2);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                register_code(KC_LGUI);
                tap_code(KC_D);
                unregister_code(KC_LGUI);
                layer_move(_CYRILLIC);
                rgb_matrix_sethsv_noeeprom(170, 255, 50);
                return false;
            case KC_SCROLL_UP:
                report_mouse_t mouse_u = pointing_device_get_report();
                mouse_u.v = 1;
                pointing_device_set_report(mouse_u);
                pointing_device_send();
                return false;
            case KC_SCROLL_DOWN:
                report_mouse_t mouse_d = pointing_device_get_report();
                mouse_d.v = -1;
                pointing_device_set_report(mouse_d);
                pointing_device_send();
                return false;
        }
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    static int16_t scroll_accum_h = 0;
    static int16_t scroll_accum_v = 0;
    static int16_t carret_accum_y = 0;
    static int16_t carret_accum_x = 0;
    static int16_t navigate_accum_y = 0;
    static int16_t navigate_accum_x = 0;
    static int16_t volume_accum_y = 0;

    if (is_carret_mode) {

        carret_accum_y += mouse_report.y;

        if (carret_accum_y >= 16) {
            tap_code(KC_UP);
            carret_accum_y -= 16;
        } else if (carret_accum_y <= -16) {
            tap_code(KC_DOWN);
            carret_accum_y += 16;
        }

        carret_accum_x += mouse_report.x;

        if (carret_accum_x >= 16) {
            tap_code(KC_LEFT);
            carret_accum_x -= 16;
        } else if (carret_accum_x <= -16) {
            tap_code(KC_RIGHT);
            carret_accum_x += 16;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    if (is_navigate_mode) {
        navigate_accum_y += mouse_report.y;

        if (navigate_accum_y >= 16) {
            register_code(KC_LGUI);
            tap_code(KC_UP);
            unregister_code(KC_LGUI);
            navigate_accum_y -= 16;
        } else if (navigate_accum_y <= -16) {
            register_code(KC_LGUI);
            tap_code(KC_DOWN);
            unregister_code(KC_LGUI);
            navigate_accum_y += 16;
        }

        navigate_accum_x += mouse_report.x;

        if (navigate_accum_x >= 16) {
            register_code(KC_LALT);
            tap_code(KC_LEFT);
            unregister_code(KC_LALT);
            navigate_accum_x -= 16;
        } else if (navigate_accum_x <= -16) {
            register_code(KC_LALT);
            tap_code(KC_RIGHT);
            unregister_code(KC_LALT);
            navigate_accum_x += 16;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    if (is_volume_mode) {
        volume_accum_y += mouse_report.y;

        if (volume_accum_y >= 16) {
            tap_code(KC_VOLU);
            volume_accum_y -= 16;
        } else if (volume_accum_y <= -16) {
            tap_code(KC_VOLD);
            volume_accum_y += 16;
        }

        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    if (is_scrolling) {
        scroll_accum_h += mouse_report.x;
        scroll_accum_v += mouse_report.y;

        mouse_report.h = scroll_accum_h / 8;
        mouse_report.v = scroll_accum_v / 8;

        scroll_accum_h %= 8;
        scroll_accum_v %= 8;

        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

void dance_e_yo_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_T);
    } else if (state->count == 2) {
        tap_code(KC_GRV);
    } else if (state->count == 3) {
        tap_code(KC_T);
        tap_code(KC_GRV);
    }
    if (state->count > 3) {
        reset_tap_dance(state);
    }
}

void dance_sh_sch_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_I);
    } else if (state->count == 2) {
        tap_code(KC_O);
    }
}

void dance_so_ho_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_M);
    } else if (state->count == 2) {
        tap_code(KC_RBRC);
    }
}

void dance_j_n_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_J);
    } else if (state->count == 2) {
        tap_code(KC_N);
    }
}

void dance_i_b_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_I);
    } else if (state->count == 2) {
        tap_code(KC_B);
    }
}

void dance_5_6_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_5);
    } else if (state->count == 2) {
        tap_code(KC_6);
    }
}

void cyr_switch_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_RALT);
    } else if (state->count == 1) {
        tap_code(KC_SLSH);
    } else if (state->count == 2) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_2);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        layer_move(_CYRILLIC);
        rgb_matrix_sethsv_noeeprom(170, 255, 50);
    }
}

void empty_cyr_switch_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        layer_on(_ADJUST);
        pointing_device_set_cpi(snipe_cpi);
        rgb_matrix_sethsv_noeeprom(43, 255, 50);
    }else if(state->count == 1) {
        tap_code(KC_SCLN);
    } else if (state->count == 2) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        reset_tap_dance(state);
    }
}

void base_switch_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        layer_on(_ADJUST);
        pointing_device_set_cpi(snipe_cpi);
        rgb_matrix_sethsv_noeeprom(43, 255, 50);
    }else if (state->count == 1) {
        tap_code(KC_SCLN);
    } else if (state->count == 2) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        layer_move(_BASE);
        rgb_matrix_sethsv_noeeprom(0, 0, 50);
    }
}

void empty_base_switch_finished(tap_dance_state_t *state, void *user_data) {
    if (state->pressed) {
        register_code(KC_RALT);
    } else if (state->count == 1) {
        tap_code(KC_QUOT);
    } else if (state->count == 2) {
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_2);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        reset_tap_dance(state);
    }
}

void snipe_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        is_sniping = true;
        pointing_device_set_cpi(snipe_cpi);
    }else{
        for (int i = 0; i < state->count; i++) {
            tap_code(KC_X);
        }
    }
}

void carret_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        is_carret_mode = true;
    }else{
        for (int i = 0; i < state->count; i++) {
            tap_code(KC_C);
        }
    }
}

void volume_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        is_volume_mode = true;
        pointing_device_set_cpi(200);
    }else{
        for (int i = 0; i < state->count; i++) {
            tap_code(KC_N);
        }
    }
}

void navigate_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        is_navigate_mode = true;
        pointing_device_set_cpi(200);
    }else{
        for (int i = 0; i < state->count; i++) {
            tap_code(KC_COMM);
        }
    }
}

void scroll_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        is_scrolling = true;
    }else{
        for (int i = 0; i < state->count; i++) {
            tap_code(KC_DOT);
        }
    }
}

void signq_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        layer_on(_SIGN);
        rgb_matrix_sethsv_noeeprom(191, 255, 50);
    }else{
        for (int i = 0; i < state->count; i++) {
            tap_code(KC_Q);
        }
    }
}

void sign_finished(tap_dance_state_t *state, void *user_data) {
    if(state->pressed){
        register_code(KC_LCTL);
        register_code(KC_LALT);
        register_code(KC_LSFT);
        tap_code(KC_1);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
        layer_on(_SIGN);
        rgb_matrix_sethsv_noeeprom(191, 255, 50);
    }else{
        for (int i = 0; i < state->count; i++) {
            tap_code(KC_LBRC);
        }
    }
}

void dance_e_yo_reset(tap_dance_state_t *state, void *user_data) {}
void dance_sh_sch_reset(tap_dance_state_t *state, void *user_data) {}
void dance_so_ho_reset(tap_dance_state_t *state, void *user_data) {}
void dance_j_n_reset(tap_dance_state_t *state, void *user_data) {}
void dance_i_b_reset(tap_dance_state_t *state, void *user_data) {}
void dance_5_6_reset(tap_dance_state_t *state, void *user_data) {}

void cyr_switch_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_RALT);
}
void base_switch_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(_ADJUST);
    pointing_device_set_cpi(base_cpi);
}
void empty_cyr_switch_reset(tap_dance_state_t *state, void *user_data) {
    layer_off(_ADJUST);
    pointing_device_set_cpi(base_cpi);
}
void empty_base_switch_reset(tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_RALT);
}
void snipe_reset(tap_dance_state_t *state, void *user_data) {
    is_sniping = false;
    pointing_device_set_cpi(normal_cpi);
}
void carret_reset(tap_dance_state_t *state, void *user_data) {
    is_carret_mode = false;
}
void volume_reset(tap_dance_state_t *state, void *user_data) {
    is_volume_mode = false;
    pointing_device_set_cpi(normal_cpi);
}
void navigate_reset(tap_dance_state_t *state, void *user_data) {
    is_navigate_mode = false;
    pointing_device_set_cpi(normal_cpi);
}
void scroll_reset(tap_dance_state_t *state, void *user_data) {
    is_scrolling = false;
}
void signq_reset(tap_dance_state_t *state, void *user_data) {
    register_code(KC_LCTL);
    register_code(KC_LALT);
    register_code(KC_LSFT);
    tap_code(KC_2);
    unregister_code(KC_LSFT);
    unregister_code(KC_LALT);
    unregister_code(KC_LCTL);
    layer_off(_SIGN);
}
void sign_reset(tap_dance_state_t *state, void *user_data) {
    register_code(KC_LCTL);
    register_code(KC_LALT);
    register_code(KC_LSFT);
    tap_code(KC_2);
    unregister_code(KC_LSFT);
    unregister_code(KC_LALT);
    unregister_code(KC_LCTL);
    layer_off(_SIGN);
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_CYR_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_e_yo_finished, dance_e_yo_reset),
    [TD_CYR_SH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sh_sch_finished, dance_sh_sch_reset),
    [TD_CYR_SO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_so_ho_finished, dance_so_ho_reset),
    [TD_US_J] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_j_n_finished, dance_j_n_reset),
    [TD_US_I] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_i_b_finished, dance_i_b_reset),
    [TD_5] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_5_6_finished, dance_5_6_reset),
    [TD_CYR_SWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cyr_switch_finished, cyr_switch_reset),
    [TD_BASE_SWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, base_switch_finished, base_switch_reset),
    [TD_EMPTY_CYR_SWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, empty_cyr_switch_finished, empty_cyr_switch_reset),
    [TD_EMPTY_BASE_SWITCH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, empty_base_switch_finished, empty_base_switch_reset),
    [TD_SNIPE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, snipe_finished, snipe_reset),
    [TD_CARRET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, carret_finished, carret_reset),
    [TD_VOLUME] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, volume_finished, volume_reset),
    [TD_NAVIGATE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, navigate_finished, navigate_reset),
    [TD_SCROLL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scroll_finished, scroll_reset),
    [TD_SIGNQ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, signq_finished, signq_reset),
    [TD_SIGN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sign_finished, sign_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        LT(5,KC_Q),    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    LT(5,KC_P),
        LT(4,KC_A),    LCTL_T(KC_S),    LGUI_T(KC_D),    LSFT_T(KC_F),    KC_G,       KC_H,    RSFT_T(KC_J),    RGUI_T(KC_K),    RCTL_T(KC_L),    TD(TD_EMPTY_CYR_SWITCH),
        LALT_T(KC_Z),    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM, KC_DOT,  TD(TD_CYR_SWITCH),
                          KC_DEL,   KC_SPC,  KC_TAB,      KC_ENT, KC_BSPC
    ),

    [_CYRILLIC] = LAYOUT(
        TD(TD_SIGNQ), KC_W, KC_E, KC_R, TD(TD_CYR_E),  KC_Y, KC_U, TD(TD_CYR_SH), KC_P, TD(TD_SIGN),
        LT(4,KC_A), LCTL_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,     KC_H, RSFT_T(KC_J), RGUI_T(KC_K),  RCTL_T(KC_L),   TD(TD_BASE_SWITCH),
        LALT_T(KC_Z),KC_X, KC_C, KC_V, KC_B,     KC_N, TD(TD_CYR_SO),KC_COMM,  KC_DOT,  TD(TD_EMPTY_BASE_SWITCH),
                                 KC_DEL,      KC_SPC,     KC_TAB,         KC_ENT,   KC_BSPC
    ),

    [_LOWER] = LAYOUT(
        KC_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,       KC_1,    KC_2,    KC_3,    KC_4,    TD(TD_5),
        KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,       TD(TD_US_J),    KC_BTN1,    KC_BTN2,    KC_SNIPE,    LT(4,KC_K),
        KC_LCTL,   KC_Z,    KC_X    ,KC_C,    KC_V,       KC_G,    KC_SCROLL_UP,    KC_SCROLL_DOWN,    KC_H,    TD(TD_US_I),
                          KC_TAB, KC_SPC, KC_LALT,        KC_ESC,    KC_M
    ),

    [_RAISE] = LAYOUT(
        KC_Q, KC_W,   KC_E, KC_R,  KC_T,                          KC_1, KC_2, KC_3, KC_4, KC_5,
        KC_A,  KC_S, KC_D, KC_F,  KC_G,   KC_BTN3, KC_BTN1, KC_BTN2, KC_SNIPE, LT(4,KC_ENT),
        KC_Z, TD(TD_SNIPE), TD(TD_CARRET), KC_V, KC_B,            KC_6, KC_7,  KC_8, KC_9, KC_0,

                                  LCTL_T(KC_TAB), LALT_T(KC_SPC), LSFT_T(KC_H),           KC_ESC, KC_F2
    ),

    [_ADJUST] = LAYOUT(
        KC_ESC, KC_0, KC_1, KC_2, KC_3,    KC_US, KC_RU, KC_CARRET, KC_MMO, KC_RTS,
        _______, KC_LCTL, LGUI_T(KC_4), LSFT_T(KC_5),KC_6,    KC_NAVIGATE, KC_BTN1, KC_BTN2, KC_SCROLL, _______,
        KC_LALT, _______, KC_7, KC_8, KC_9,    KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,
                         KC_VOLD, KC_MUTE, KC_VOLU,    KC_BTN3, KC_BSPC
    ),

    [_SIGN] = LAYOUT(
        _______, KC_CNUM, KC_CCIRC, KC_CEXLM, KC_CCOMM,    KC_CDOT, KC_CQUES, KC_CASTR, KC_CHASH, _______,
        KC_CTILD, KC_CLABK, KC_CLCBR, KC_CLBRC,KC_CLPRN,    KC_CRPRN, KC_CRBRC, KC_RCBR, KC_CRABK, KC_CGRV,
        KC_CSLSH, KC_CEQL, KC_CAMPR, KC_CQUOT, KC_CCOLN,   KC_CSCLN, KC_CDQUO, KC_CPIPE, KC_CPLUS, KC_CBSLS,
                         KC_CAT, KC_CPERC, KC_CDLR,    KC_CUNDS, KC_CMINS
    )
};

void keyboard_post_init_user(void) {
    wait_ms(500);
    pointing_device_set_cpi(400);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);  // Отключаем анимацию
    rgb_matrix_sethsv_noeeprom(0, 0, 128);             // Белый по умолчанию
}

// При каждом нажатии - только меняем цвет
void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(_SIGN)) {
        rgb_matrix_sethsv_noeeprom(191, 255, 50);
    } else if (IS_LAYER_ON(_ADJUST)) {
        rgb_matrix_sethsv_noeeprom(43, 255, 50);
    } else if (IS_LAYER_ON(_RAISE)) {
        rgb_matrix_sethsv_noeeprom(85, 255, 50);
    } else if (IS_LAYER_ON(_LOWER)) {
        rgb_matrix_sethsv_noeeprom(0, 255, 50);
    } else if (IS_LAYER_ON(_CYRILLIC)) {
        rgb_matrix_sethsv_noeeprom(170, 255, 50);
    } else {
        rgb_matrix_sethsv_noeeprom(0, 0, 50);
    }
}
