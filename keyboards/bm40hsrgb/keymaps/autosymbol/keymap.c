/* Copyright 2021 gerhard-h
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "rgb.c"
enum layers { _L0, _L1, _L2, _L3, _L4 };
#include "customkeys.c"
#include "tapdance.c"
/*static bool is_alt_tab_active = false;
static uint16_t alt_tab_timer = 0;*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* ESC           PSCR          NO            ESC Home      1                    2                         3                    4                  5             6             7                        8             9                 0             DEL
*  TO(L0)        TO(L1)        NO            ESC Home      Q End                W                         E                    R                  J             Z             U Ü                      I             O Ö               P             Backspc
*  PgUp          VOLU          NO            TAB/Ctrl      A Ä                  S ß                       D                    F                  G             H             N                        T             L                 k/Alt atab    Enter/Ctrl
*  PgDn          VOLD          NO            HOME/Shift    Z                    X                         C                    V                  B             M             ,                        . : *         - _ /             Up            END/Shift
*  CTL           ALT           NO            PgUp/Ctrl     PgDn/WIN             Del/Alt                   Tab/L2               Enter/L1           Space/Shift   Space/Shift   Space/L2                 OSL L4        Left              Down          Right
*/       
[0] = LAYOUT_planck_mit(    
                                         TD(TD_ESC),          TD(TD_Q),        TD(TD_W),          TD(TD_E),              KC_R,          KC_J,      TD(TD_Z),      TD(TD_U_UML),              KC_I,    TD(TD_O_UML),               KC_P,             TD(TD_BSP),
                               MT(MOD_LCTL ,KC_TAB),      TD(TD_A_UML),   TD(TD_SS_UML), MT(MOD_LCTL,KC_D), MT(MOD_LSFT,KC_F),          KC_G,          KC_H, MT(MOD_LSFT,KC_N), MT(MOD_LCTL,KC_T),        TD(TD_L), MT(MOD_LALT, KC_K),    MT(MOD_LCTL,KC_ENT),
                                      OSM(MOD_LSFT),          TD(TD_Y),        TD(TD_X),          TD(TD_C),          TD(TD_V),          KC_B,      TD(TD_M),       TD(TD_COMM),        TD(TD_DOT),     TD(TD_DASH),              KC_UP,    MT(MOD_LSFT,KC_DEL),
                              MT(MOD_LCTL, KC_PGUP),           KC_LGUI,
                                                                     MT(MOD_LALT,KC_DEL),
                                                                                 TD(TD_TAB_ENT),
                                                                                                 OSL(_L1),
                                                                                                                 MT(MOD_LSFT,KC_SPC),
                                                                                                                                          OSL(_L2),        OSL(_L4),         KC_LEFT,            KC_DOWN,                KC_RGHT
 ),
/*            ________      ________      ________      F12           F1            F2            F3            F4            F5            F6            F7            F8            F9            F10           F11
*             ________      TO(_L2)       ________      ________      1             2             3           DEL           BSP             !             ü            ä\             ö             ß~            ________
*             ________      ________      ________      ________      4             5             6             0             .             ?             (             )             '             #             ________
*             ________      ________      ________      ________      7             8             9             1             ,             =             <             >             /             ________      ________
*             ________      ________      ________      ________      ________      0/Alt         TO(2)      ________      ________      ________      ________      TG(_L2)          ________      ________      ________
*/
[1] = LAYOUT_planck_mit(

                                                         KC_TRNS,         TD(TD_1),             TD(TD_2),                    TD(TD_3),          TD(TD_DEL10),       KC_BSPC,     DE_AMPR,    KC_LBRC,        DE_BSLS,       KC_SCLN,        DE_QUES,       KC_TRNS,
                                                         KC_TRNS,         TD(TD_4),             TD(TD_5),                    TD(TD_6),              TD(TD_0),    TD(TD_DOT),     DE_SLSH, TD(TD_PAR),        KC_LPRN,   TD(TD_QUOT),        DE_TILD,       KC_TRNS,
                                                         KC_TRNS,         TD(TD_7),              TD(TD_8),                   TD(TD_9),             TD(TD_12),   TD(TD_COMM),  S(KC_RBRC), TD(TD_ANG),     S(KC_NUBS),       KC_AMPR,          KC_UP,       KC_TRNS,
                                                         KC_TRNS,          KC_TRNS,     MT(MOD_LALT,KC_0),                    KC_TRNS,               KC_TRNS,       KC_TRNS,                 MO(_L2),        KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS
  ),
/*  ________      ________      ________      ________      ________                 ________              ________                ________                  ________                 ________      ________      ________      ________   ________      ________
*   ________      TG(_L1)       ________      ^             @                        "                     [                       ]                         %                        A(TAB)             HOME          UP            END        ________      ________
*   ________      ________      ________      ________      ä                        ß/alt                 |/Shift                 $/Ctrl                    +                        HOME          LEFT          DOWN          RGHT       END           ________
*   ________      ________      ________      ________      TD(TD_TICK)              CIRC                  TD(TD_CUR)              ALGR(0)                   S(RBRC)                  ESC           ENT           DEL           BSP        ________      Home/Shift
*   ________      ________      ________      ________      WIN                      Del/Alt                  TG(1)                ________                  ________                 ________      ________      ________      ________   ________      ________
*/
[2] = LAYOUT_planck_mit(
                                                CIRCUMFL,     DE_EXLM,            TD(TD_DQUOT),            TD(TD_SQU),             ALGR(KC_9),              KC_PERC,                A(KC_TAB),      KC_HOME,        KC_UP,    KC_END,        KC_PGUP,     KC_BSPC,
                                                 KC_TRNS,     KC_QUOT,    MT(MOD_LALT,KC_MINS),  MT(MOD_LCTL,KC_NUHS),         TD(TD_DOL_SFT),              KC_RPRN,             A(S(KC_TAB)),      KC_LEFT,      KC_DOWN,    KC_RGHT,       KC_PGDN,     KC_TRNS,
                                                 KC_TRNS,    TICKTICK,                 DE_PIPE,            TD(TD_CUR),             ALGR(KC_0),              KC_RBRC,                   KC_ESC,      KC_ENT,        KC_DEL,    KC_BSPC,       KC_TRNS,     KC_TRNS,
                                                 KC_TRNS,     KC_LGUI,     MT(MOD_LALT,KC_DEL),               KC_TRNS,                MO(_L1),              KC_TRNS,                                KC_TRNS,      KC_TRNS,    KC_TRNS,       KC_TRNS,     KC_TRNS
  ),

/* L3
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |  F1  | Reset|AutoS | RGB  |RGBMOD| HUE+ | HUE- |lclick| ms-u |rclick|ms-w+ | ASTG |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F2  |  F5  |ACCEL0|ACCEL1|ACCEL2| SAT+ | SAT- | ms-l | ms-d | ms-r |ms-w- |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F3  |  F6  |  F8  |  F10 |  F12 |BRGTH+|BRGTH-|lclick|mclick|rclick|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F4  |  F7  |  F9  |  F11 |      |             |      |      |      |      | ALT  |
 * `-----------------------------------------------------------------------------------'
 * 
 */
[3] = LAYOUT_planck_mit(
    KC_F1, RESET,             DEBUG,      RGB_TOG,       RGB_MOD, RGB_HUI, RGB_HUD, KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,   KC_MS_WH_UP,               CMB_TOG,
    KC_F2, KC_F5,      KC_MS_ACCEL0, KC_MS_ACCEL1,  KC_MS_ACCEL2, RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT, KC_MS_WH_DOWN,               KC_TRNS,
    KC_F3, KC_F6,             KC_F8,       KC_F10,        KC_F12, RGB_VAI, RGB_VAD, KC_MS_BTN1,  KC_MS_BTN2,   KC_MS_BTN3,       _______,               _______,
    KC_F4, KC_F7,MT(MOD_LALT,KC_F9),       KC_F11,       _______, _______,             _______,     _______,      _______,       _______,  MT(MOD_RALT, KC_RGHT)
)
,

/* L4
 */
[_L4] = LAYOUT_planck_mit(
    KC_TRNS,         TD(TD_1),               TD(TD_2),       TD(TD_3),              TD(TD_10),   TD(TD_DASH),     KC_PGUP,     KC_MENU,        CTLSFTF,       KC_RALT,        KC_PSCR,       KC_TRNS,
    KC_TRNS,         TD(TD_4),               TD(TD_5),       TD(TD_6),               TD(TD_0),    TD(TD_DOT),     KC_PGDN,   PICKFIRST,        PICK2ND,       PICK3RD,        KC_LALT,       KC_TRNS,
    KC_TRNS,         TD(TD_7),               TD(TD_8),       TD(TD_9),              TD(TD_12),   TD(TD_COMM),  S(KC_RBRC),      KC_APP,     KC_MS_BTN2,       KC_LGUI,        KC_VOLU,       KC_TRNS,
    KC_TRNS,          KC_TRNS,      MT(MOD_LALT,KC_0),        KC_TRNS,                KC_TRNS,       KC_TRNS,                  KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_VOLD,       KC_TRNS
  ),    

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _L1, _L2, _L3);
}

