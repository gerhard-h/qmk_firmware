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

#include "print.h"
#include QMK_KEYBOARD_H
//#include "muse.h"
#include "keymap_german.h"
// only here because of intellisense
//include "rev6/config.h"
#include "rgb.c"
enum layers { _L0, _GAME, _SWAP, _LNAV, _LSYM, _L3, _L4};
#include "customkeys.c"
#include "tapdance.c"

const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{11, 1}, {10, 1}, {9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{11, 2}, {10, 2}, {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {5, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
*  TO(L0)   TO(L1)   NO  ESC/Home  ^    Q ! @      W " ""  E [ []     R  ]      J %      Z &      U Ü       I \      O Ö     P ?      Backspc/End
*  PgUp     VOLU     NO  TAB/Ctrl  A Ä   S ß     D Ctl      F  Sft    G =      H /      N Sft     T Ctl    L ' ''  k Alt    Enter/Ctrl
*  PgDn     VOLD     NO  OSM-Shift     Y Ctl+Y     X | Ctl+X    C { {} Ctl+C    V } Ctl+V B +      M *      , ; <     . : >    - _ ~   Up  END/Shift
*  CTL      ALT      NO  PgUp/Ctrl      WIN   Del/Alt      Tab/Ctl    L1    Space/Shift   Space/Shift    L2     OSL L4   Left    Down     Right
*/  
[_L0] = LAYOUT_planck_mit(    

                          TD(TD_ESC),      TD(TD_Q),       TD(TD_W),  TD(TD_E),    TD(TD_R),  TD(TD_J), TD(TD_Z), TD(TD_U),       TD(TD_I),     TD(TD_O),    TD(TD_P),        KC_BSPC,
                       CTL_T(KC_TAB),      TD(TD_A),      TD(TD_SS), CTL_T(KC_D),   F_LSHFT,  TD(TD_G), TD(TD_H),  N_RSHFT,    CTL_T(KC_T),  ALT_T(KC_L), GUI_T(KC_K), RCTL_T(KC_ENT),
                       OSM(MOD_LSFT),      TD(TD_Y),       TD(TD_X),  TD(TD_C),    TD(TD_V),  TD(TD_B), TD(TD_M),  TD(TD_COMM), TD(TD_DOT),  TD(TD_DASH),       KC_UP, RSFT_T(KC_DEL),
                       OSM(MOD_LCTL), OSM(MOD_LGUI),  OSM(MOD_LALT),  OSL(_L4),  OSL(_LNAV),
                                                                                                LT(_LNAV,KC_SPC),
                                                                                                                   OSL(_LSYM),   OSL(_LNAV),      KC_LEFT,     KC_DOWN,        KC_RGHT
 ),
[_GAME] = LAYOUT_planck_mit(    

                             KC_ESC,          KC_Q,           KC_W,       KC_E,        KC_R,    KC_J,     KC_Y,          KC_U,         KC_I,        KC_O,     KC_P,           KC_BSPC,
                             KC_TAB,          KC_A,           KC_S,       KC_D,        KC_F,    KC_G,     KC_H,          KC_N,         KC_T,        KC_L,     KC_K,           KC_ENT,
                            KC_LSFT,          KC_Z,           KC_X,       KC_C,        KC_V,    KC_B,     KC_M,       KC_COMM,       KC_DOT,    KC_SLASH,    KC_UP,           KC_RSFT,
                            KC_LCTL,       KC_LALT,        KC_LSFT,     KC_SPC,  OSL(_LNAV),  LT(_LSYM,KC_SPC),    OSL(_LNAV),     OSL(_L4),     KC_LEFT,  KC_DOWN,           KC_RGHT
 ),

[_SWAP] = LAYOUT_planck_mit(

                          TD(TD_ESC),      TD(TD_Q),      TD(TD_W),   TD(TD_E),    TD(TD_R),  TD(TD_J), TD(TD_Z), TD(TD_U),    TD(TD_I), TD(TD_O),     TD(TD_P),        KC_BSPC,
                       CTL_T(KC_TAB),      TD(TD_A),     TD(TD_SS), LCTL_T(KC_D),    F_LSHFT,  TD(TD_G), TD(TD_H),      N_RSHFT,     CTL_T(KC_T),  ALT_T(KC_L),  GUI_T(KC_K), RCTL_T(KC_ENT),
                       OSM(MOD_LSFT),      TD(TD_Y),      TD(TD_X),   TD(TD_C),    TD(TD_V),  TD(TD_B), TD(TD_M),  TD(TD_COMM),  TD(TD_DOT),  TD(TD_DASH),        KC_UP, RSFT_T(KC_DEL),
                       OSM(MOD_LCTL), OSM(MOD_LGUI), OSM(MOD_LALT),      SH_OS,  OSL(_LNAV),
                                                                                                LT(_LSYM,KC_SPC),
                                                                                                                     MO(_LNAV),       SH_OS, LT(_L4,KC_DEL), OSM(MOD_LGUI), OSM(MOD_LCTL)
 ),
 
/*           
*             ________      TO(_LSYM)     ________      ________             -                   1                  2                3              INS                 A(TAB)        HOME          UP            END        PGUP          ________
*             ________      ________      ________      ________             .                   4alt               5ctl             6sft           0win                AS(TAB)       LEFT          DOWN          RGHT       PGD           ________
*             ________      ________      ________      ________             ,                   7                  8                9              ENT           S(RBRC)                  ESC           BSP           DEL           ENT        ________      ________
*             ________      ________      ________      ________          ________             _______         ________           ________        ________       ________      TG(_LSYM)          ________        ________      ________
* NUM NAV*/
[_LNAV] = LAYOUT_planck_mit(

                            KC_TRNS,    TD(TD_DASH),         KC_1,         KC_2,         KC_3,   DF(_LNAV),       KC_ESC, KC_HOME,    KC_UP,       KC_END, LGUI_T(KC_PGUP),     KC_BSPC,
                            KC_TRNS,     TD(TD_DOT), LALT_T(KC_4), LCTL_T(KC_5), LSFT_T(KC_6), GUI_T(KC_0),       KC_TAB, KC_LEFT,  KC_DOWN,      KC_RGHT, LALT_T(KC_PGDN),     KC_TRNS,
                            KC_TRNS,    TD(TD_COMM),         KC_7,         KC_8,         KC_9,     DF(_L0),       KC_ENT, KC_BSPC,   KC_DEL,       KC_ENT,         KC_TRNS,     KC_TRNS,
                            KC_TRNS,        KC_TRNS,      KC_TRNS,      KC_TRNS,      TO(_L3),     KC_TRNS,               TO(_L3),  KC_TRNS,      KC_TRNS,         KC_TRNS,     KC_TRNS
  ),
/* 
*                                ^             @             "          [            ]                 %           &        ü             \             ö        ?            ________
*                         ________             `             ß          #            $                 =           /        (             )             '        €            ________
*                         ________             ´             |          {            }                 +           *        <             >             ~       ________      ________
* SYMBOL*/
[_LSYM] = LAYOUT_planck_mit(

                          CIRCUMFL,         DE_EXLM, TD(TD_DQUOT),   TD(TD_SQU),  ALGR(KC_9),        KC_DLR,   DE_AMPR,    KC_NUHS,    DE_BSLS,      KC_PERC,      DE_QUES,     KC_TRNS,
                           KC_TRNS,       STICKTICK,  TD(TD_QUOT),   TD(TD_CUR),  ALGR(KC_0),       KC_RPRN,   DE_SLSH,    KC_BSPC,     KC_DEL,       KC_ENT,   ALGR(KC_E),     KC_TRNS,
                           KC_LSFT,        TICKTICK,      DE_PIPE,   TD(TD_PAR),     KC_LPRN,       KC_RBRC,   DE_ASTR, TD(TD_ANG), S(KC_NUBS),      DE_TILD,        KC_UP,     KC_TRNS,
                           KC_TRNS,         KC_LGUI,      KC_LALT,      KC_TRNS,     TO(_L3),       KC_TRNS,               TO(_L3),    KC_TRNS,      KC_TRNS,      KC_TRNS,     KC_TRNS
  ),

/* L3
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * | GAME | Reset|DEBUG | RGB  |RGBMOD| HUE+ | HUE- |lclick| ms-u |rclick|ms-w+ | BACKLIT/L0
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SWAP |      |ACCEL0|ACCEL1|ACCEL2| SAT+ | SAT- | ms-l | ms-d | ms-r |ms-w- |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  NUM |      |      |      |      |BRGTH+|BRGTH-|lclick|rclick|mclick|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  L0  |      |      |      |      |             |      |      |      |      | ALT  |
 * `-----------------------------------------------------------------------------------'
 * 
 */
[_L3] = LAYOUT_planck_mit(

                        TO(_GAME),          RESET,        DEBUG,       RGB_TOG,    TG(_SWAP),  RGB_HUI, RGB_HUD, KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,   KC_MS_WH_UP,    TO(_L0),
                        TO(_SWAP),        RGB_MOD, KC_MS_ACCEL0,  KC_MS_ACCEL1, KC_MS_ACCEL2,  RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT, KC_MS_WH_DOWN,    KC_TRNS,
                        TO(_LSYM),        KC_TRNS,   KC_MS_BTN3,    KC_MS_BTN2,   KC_MS_BTN1,  RGB_VAI, RGB_VAD, KC_MS_BTN1,  KC_MS_BTN2,   KC_MS_BTN3,       _______,    _______,
                        TO(_L0),          KC_TRNS,      _______,       _______,      KC_LCTL,  TO(_L0),             KC_LSFT,     _______,      _______,       _______,    _______
),


/* L4
 * ,-----------------------------------------------------------------------------------.
 * |      | 1 F1 | 2 F2 | 3 F3 | € F10|  ALT | PGUP |  APP | C+S+F| RALT | PSCR |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | 4 F4 | 5 F5 | 6 F6 | 0 F11|  WIN | PGDN |  1st |  2nd | 3rd  | LALT |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | 7 F7 | 8 F8 | 9 F9 | 1 F12|  CTL | ESC  |  BSP |rclick|  WIN | VOL+ |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | [L4] |      |             |      | [L4] |      | VOL- |      |
 * `-----------------------------------------------------------------------------------'
 */
[_L4] = LAYOUT_planck_mit(
                         KC_TRNS,         KC_F1,        KC_F2,        KC_F3,        KC_F4,     KC_INS, A(S(KC_TAB)),     KC_APP,   KC_MS_BTN2,  KC_RALT,        KC_PSCR,       KC_TRNS,
                         KC_TRNS,         KC_F5,        KC_F6,        KC_F7,        KC_F8,     KC_LALT,   A(KC_TAB),  PICKFIRST,      PICK2ND,  PICK3RD,        KC_LALT,       KC_TRNS,
                         KC_TRNS,         KC_F9,       KC_F10,       KC_F11,       KC_F12,     KC_LCTL,      KC_ESC,    KC_LSFT,      KC_LCTL,  KC_LALT,        KC_LGUI,       KC_TRNS,
                         KC_TRNS,       KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,                  KC_TRNS,    KC_TRNS,      KC_TRNS,  KC_TRNS,        KC_VOLD,       KC_VOLU
  )    

};
/*
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _LNAV:
        // this code fail
        if ((IS_HOST_LED_ON(USB_LED_NUM_LOCK) != true) && get_highest_layer(default_layer_state) > 0) {
                tap_code(KC_NUMLOCK);
        }
        break;
    case _L0:
        // this code clears the num lock flag on layer 0 but is not needed
        if (IS_HOST_LED_ON(USB_LED_NUM_LOCK) == true  && get_highest_layer(default_layer_state) == _L0) {
                tap_code(KC_NUMLOCK);
        }
        break;
    }
    return state;
}
*/
//layer_state_t layer_state_set_user(layer_state_t state) {
    /*switch (get_highest_layer(state)) {
    case _L0:
        hold_feature_active = 1;
        break;
    case _GAME:
        hold_feature_active = 0;
        break;
    }*/
//  return update_tri_layer_state(state, _LNAV, _LSYM, _L3);
// }
