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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
*  TO(L0)        TO(L1)        NO            ESC/Home  ^         Q ! @                W " ""            E [ []               R  ]           J %           Z &           U Ü                      I \           O Ö               P ?           Backspc/End
*  PgUp          VOLU          NO            TAB/Ctrl            A Ä                  S ß               D Ctl                F  Sft         G =           H /           N Sft                    T Ctl         L ' ''            k Alt         Enter/Ctrl
*  PgDn          VOLD          NO            OSM-Shift          Y Ctl+Y               X | Ctl+X         C { {} Ctl+C         V } Ctl+V      B +           M *           , ; <                    . : >         - _ ~             Up            END/Shift
*  CTL           ALT           NO            PgUp/Ctrl           WIN                  Del/Alt           Tab/Ctl              L1         Space/Shift   Space/Shift         L2                    OSL L4        Left              Down          Right
*/       
[0] = LAYOUT_planck_mit(    
                                             TD(TD_ESC),          TD(TD_Q),        TD(TD_W),          TD(TD_E),              KC_R,          KC_J,      TD(TD_Z),      TD(TD_U_UML),               KC_I,    TD(TD_O_UML),               KC_P,                KC_BSPC,
                                   MT(MOD_LCTL ,KC_TAB),      TD(TD_A_UML),   TD(TD_SS_UML), MT(MOD_LCTL,KC_D), MT(MOD_LSFT,KC_F),          KC_G,          KC_H, MT(MOD_LSFT,KC_N),  MT(MOD_LCTL,KC_T),        TD(TD_L), MT(MOD_LALT, KC_K),    MT(MOD_LCTL,KC_ENT),
                                          OSM(MOD_LSFT),          TD(TD_Y),        TD(TD_X),          TD(TD_C),          TD(TD_V),          KC_B,      TD(TD_M),       TD(TD_COMM),         TD(TD_DOT),     TD(TD_DASH),              KC_UP,    MT(MOD_LSFT,KC_DEL),
                                  MT(MOD_LCTL, KC_PGUP),           KC_LGUI,
                                                                         MT(MOD_LALT,KC_DEL),
                                                                                    OSL(_L4),
                                                                                                     OSL(_L1),
                                                                                                                     LT(_L2,KC_SPC),
                                                                                                                                                                         OSL(_L1),            OSL(_L4),         KC_LEFT,              KC_DOWN,                KC_RGHT
 ),
/*           
*             ________      TO(_L2)       ________      ________          1                     2                            3                     DEL             BSP            &             ü             \             ö               ?            ________
*             ________      ________      ________      ________          4                     5                            6                      0               .             /             (             )             '               ~            ________
*             ________      ________      ________      ________          7                     8                            9                      1               ,             *             <             >             /              ________      ________
*             ________      ________      ________      ________          ________              0/Alt                    ________               ________        ________      ________      !________      TG(_L2)          ________        ________      ________
* NUM NAV*/
[1] = LAYOUT_planck_mit(

                                                         KC_TRNS,         KC_1,             KC_2,                  KC_3,                KC_DEL,       KC_BSPC,     A(S(KC_TAB)),      KC_HOME,        KC_UP,    KC_END,  MT(MOD_LGUI,KC_PGUP),     KC_BSPC,
                                                         KC_TRNS,         KC_4,             KC_5,     MT(MOD_LCTL,KC_6),     MT(MOD_LSFT,KC_0),    TD(TD_DOT),        A(KC_TAB),      KC_LEFT,      KC_DOWN,    KC_RGHT, MT(MOD_LALT,KC_PGDN),     KC_TRNS,
                                                         KC_TRNS,         KC_7,             KC_8,                  KC_9,                KC_ENT,   TD(TD_COMM),           KC_ESC,      KC_BSPC,        KC_DEL,    KC_ENT,       KC_TRNS,     KC_TRNS,
                                                         KC_TRNS,      KC_TRNS, MT(MOD_LALT,KC_0),              KC_TRNS,               KC_TRNS,       KC_TRNS,                        MO(_L2),       KC_TRNS,   KC_TRNS,       KC_TRNS,     KC_TRNS
  ),
/* 
*   ________      TG(_L1)       ________      ^             @                        "                     [                       ]                         %                        A(TAB)        HOME          UP            END        PGUP          ________
*   ________      ________      ________      ________      ä                        ß/alt                 |/Shift                 $/Ctrl                    +                        AS(TAB)       LEFT          DOWN          RGHT       PGD           ________
*   ________      ________      ________      ________      TD(TD_TICK)              CIRC                  TD(TD_CUR)              ALGR(0)                   S(RBRC)                  ESC           BSP           DEL           ENT        ________      ________
*   ________      ________      ________      ________      WIN                      Del/Alt                  TG(1)                ________                  ________                 ________      ________      ________      ________   ________      ________
* SYMBOL*/
[2] = LAYOUT_planck_mit(
                                                CIRCUMFL,     DE_EXLM,            TD(TD_DQUOT),            TD(TD_SQU),             ALGR(KC_9),              KC_PERC,               DE_AMPR,     DE_UDIA,        DE_BSLS,       DE_ODIA,        DE_QUES,       KC_TRNS,
                                                 KC_TRNS,     DE_ADIA,    MT(MOD_LALT,KC_MINS),  MT(MOD_LCTL,KC_NUHS),         TD(TD_DOL_SFT),              KC_RPRN,               DE_SLSH,  TD(TD_PAR),        KC_LPRN,   TD(TD_QUOT),        DE_TILD,       KC_TRNS,
                                                 KC_TRNS,    TICKTICK,                 DE_PIPE,            TD(TD_CUR),             ALGR(KC_0),              KC_RBRC,               DE_ASTR,  TD(TD_ANG),     S(KC_NUBS),       DE_TILD,          KC_UP,       KC_TRNS,
                                                 KC_TRNS,     KC_LGUI,     MT(MOD_LALT,KC_DEL),               KC_TRNS,                MO(_L1),              KC_TRNS,                            KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS
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
    KC_F4, KC_F7,MT(MOD_LALT,KC_F9),       KC_F11,       _______, _______,             _______,     _______,      _______,       _______,  MT(MOD_LALT, KC_RGHT)
),


/* L4
 * ,-----------------------------------------------------------------------------------.
 * |      | 1 F1 | 2 F2 | 3 F3 | € F10|  - _ | PGUP |  F24 | C+S+F| RALT | PSCR |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | 4 F4 | 5 F5 | 6 F6 | 0 F11|  . : | PGDN |  1st |  2nd | 3rd  | LALT |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | 7 F7 | 8 F8 | 9 F9 | 1 F12|  , ; | ESC  |  APP |rclick|  WIN | VOL+ |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  0Alt|      |      |             |      | [L4] |      | VOL- |      |
 * `-----------------------------------------------------------------------------------'
 */
[_L4] = LAYOUT_planck_mit(
    KC_TRNS,         KC_F1,               KC_F2,       KC_F3,              KC_F10,   TD(TD_DASH),     KC_PGUP,      KC_APP,        CTLSFTF,       KC_RALT,        KC_PSCR,       KC_TRNS,
    KC_TRNS,         KC_F4,               KC_F5,       KC_F6,              KC_F11,    TD(TD_DOT),     KC_PGDN,   PICKFIRST,        PICK2ND,       PICK3RD,        KC_LALT,       KC_TRNS,
    KC_TRNS,         KC_F7,               KC_F8,       KC_F9,              KC_F12,   TD(TD_COMM),      KC_ESC,     KC_BSPC,     KC_MS_BTN2,       KC_LGUI,        KC_VOLU,       KC_TRNS,
    KC_TRNS,       KC_TRNS,             KC_TRNS,     KC_TRNS,             KC_TRNS,       KC_TRNS,                  KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_VOLD,       KC_TRNS
  ),    

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _L1, _L2, _L3);
}

