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
//#include "rgb.c"
enum layers { _L0, _GAME, _SWAP, _LNAV, _LSYM, _L3, _L4};
#include "customkeys.c"
#include "tapdance.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
*  TO(L0)        TO(L1)        NO            ESC/Home  ^         Q ! @                W " ""            E [ []               R  ]           J %           Z &           U Ü                      I \           O Ö               P ?           Backspc/End
*  PgUp          VOLU          NO            TAB/Ctrl            A Ä                  S ß               D Ctl                F  Sft         G =           H /           N Sft                    T Ctl         L ' ''            k Alt         Enter/Ctrl
*  PgDn          VOLD          NO            OSM-Shift          Y Ctl+Y               X | Ctl+X         C { {} Ctl+C         V } Ctl+V      B +           M *           , ; <                    . : >         - _ ~             Up            END/Shift
*  CTL           ALT           NO            PgUp/Ctrl           WIN                  Del/Alt           Tab/Ctl              L1         Space/Shift   Space/Shift         L2                    OSL L4        Left              Down          Right
*/       
[_L0] = LAYOUT_planck_mit(    
                                             TD(TD_ESC),          TD(TD_Q),        TD(TD_W),          TD(TD_E),              KC_R,          KC_J,      TD(TD_Z),      TD(TD_U_UML),           TD(TD_I),    TD(TD_O_UML),               KC_P,                KC_BSPC,
                                   MT(MOD_LCTL ,KC_TAB),      TD(TD_A_UML),   TD(TD_SS_UML),          TD(TD_D),           F_LSHFT,          KC_G,      TD(TD_H),           N_RSHFT,           TD(TD_T),        TD(TD_L), MT(MOD_LALT, KC_K),    MT(MOD_LCTL,KC_ENT),
                                          OSM(MOD_LSFT),          TD(TD_Y),        TD(TD_X),          TD(TD_C),          TD(TD_V),          KC_B,      TD(TD_M),       TD(TD_COMM),         TD(TD_DOT),     TD(TD_DASH),              KC_UP,    MT(MOD_RSFT,KC_DEL),
                                          OSM(MOD_LCTL),     OSM(MOD_LGUI),   OSM(MOD_LALT),          OSL(_L4),        OSL(_LNAV),
                                                                                                                                            LT(_LSYM,KC_SPC),
                                                                                                                                                                  LT(_LNAV,KC_TAB),     LT(_L4,KC_DEL),         KC_LEFT,             KC_DOWN,                KC_RGHT
 ),
[_GAME] = LAYOUT_planck_mit(    
     KC_ESC,     KC_Q,        KC_W,          KC_E,          KC_R,          KC_J,           KC_Y,              KC_U,           KC_I,        KC_O,               KC_P,    KC_BSPC,
     KC_TAB,     KC_A,        KC_S,          KC_D,          KC_F,          KC_G,           KC_H,              KC_N,           KC_T,        KC_L,               KC_K,    KC_ENT,
    KC_LSFT,     KC_Z,        KC_X,          KC_C,          KC_V,          KC_B,           KC_M,           KC_COMM,         KC_DOT,    KC_SLASH,              KC_UP,    KC_RSFT,
    KC_LCTL,  KC_LALT,     KC_LSFT,        KC_SPC,        OSL(_LNAV), LT(_LSYM,KC_SPC),         OSL(_LNAV),               OSL(_L4),     KC_LEFT,            KC_DOWN,    KC_RGHT
 ),
[_SWAP] = LAYOUT_planck_mit(    
                                             TD(TD_ESC),          TD(TD_Q),        TD(TD_W),          TD(TD_E),              KC_R,          KC_J,      TD(TD_Z),      TD(TD_U_UML),               KC_I,    TD(TD_O_UML),               KC_P,                KC_BSPC,
                                   MT(MOD_LCTL ,KC_TAB),      TD(TD_A_UML),   TD(TD_SS_UML),          TD(TD_D),          TD(TD_F),          KC_G,          KC_H,          TD(TD_N),           TD(TD_T),        TD(TD_L), MT(MOD_LALT, KC_K),    MT(MOD_LCTL,KC_ENT),
                                          OSM(MOD_LSFT),          TD(TD_Y),        TD(TD_X),          TD(TD_C),          TD(TD_V),          KC_B,      TD(TD_M),       TD(TD_COMM),         TD(TD_DOT),     TD(TD_DASH),              KC_UP,    MT(MOD_LSFT,KC_DEL),
                                          OSM(MOD_LCTL),     OSM(MOD_LGUI),   OSM(MOD_LALT),        OSL(_LNAV),        OSL(_LNAV),
                                                                                                                                            LT(_LSYM,KC_SPC),
                                                                                                                                                                          MO(_LNAV),          OSL(_LSYM),     LT(_L4,KC_DEL),         KC_LGUI,                KC_LCTL
 ),
 
/*           
*             ________      TO(_LSYM)     ________      ________             -                   1                  2                3              INS                 A(TAB)        HOME          UP            END        PGUP          ________
*             ________      ________      ________      ________             .                   4alt               5ctl             6sft           0win                AS(TAB)       LEFT          DOWN          RGHT       PGD           ________
*             ________      ________      ________      ________             ,                   7                  8                9              ENT           S(RBRC)                  ESC           BSP           DEL           ENT        ________      ________
*             ________      ________      ________      ________          ________             _______         ________           ________        ________       ________      TG(_LSYM)          ________        ________      ________
* NUM NAV*/
[_LNAV] = LAYOUT_planck_mit(

                                                         KC_TRNS,    TD(TD_DASH),              KC_1,              KC_2,              KC_3,            KC_INS, A(S(KC_TAB)),      KC_HOME,        KC_UP,     KC_END,  MT(MOD_LGUI,KC_PGUP),     KC_BSPC,
                                                         KC_TRNS,     TD(TD_DOT), MT(MOD_LALT,KC_4), MT(MOD_LCTL,KC_5), MT(MOD_LSFT,KC_6), MT(MOD_LGUI,KC_0),    A(KC_TAB),      KC_LEFT,      KC_DOWN,    KC_RGHT,  MT(MOD_LALT,KC_PGDN),     KC_TRNS,
                                                         KC_TRNS,    TD(TD_COMM),              KC_7,              KC_8,              KC_9,            KC_ENT,       KC_ESC,      KC_BSPC,       KC_DEL,     KC_ENT,               KC_TRNS,     KC_TRNS,
                                                         KC_TRNS,        KC_TRNS,           KC_TRNS,           KC_TRNS,           KC_TRNS,           KC_TRNS,                  MO(_LSYM),      KC_TRNS,    KC_TRNS,               KC_TRNS,     KC_TRNS
  ),
/* 
*   ________      TG(_LNAV)       ________      ^             @                        "                     [                       ]                        %               &             ü             \             ö               ?            ________
*   ________      ________      ________      ________        ä                        ß                     #                       $                        =               /             (             )             '                        ________
*   ________      ________      ________      ________        ´                        |                     {                       }                        +               *             <             >             ~              ________      ________
*   ________      ________      ________      ________       WIN                       Alt                  ________                MouseLayer             ________        ________      ________      ________      ________          ________      ________
* SYMBOL*/
[_LSYM] = LAYOUT_planck_mit(
                                                CIRCUMFL,     DE_EXLM,            TD(TD_DQUOT),            TD(TD_SQU),             ALGR(KC_9),              KC_PERC,       DE_AMPR,     DE_UDIA,        DE_BSLS,       DE_ODIA,        DE_QUES,       KC_TRNS,
                                                 KC_TRNS,     DE_ADIA,                 KC_MINS,               KC_NUHS,                 KC_DLR,              KC_RPRN,       DE_SLSH,  TD(TD_PAR),        KC_LPRN,   TD(TD_QUOT),     ALGR(KC_E),       KC_TRNS,
                                                 KC_LSFT,    TICKTICK,                 DE_PIPE,            TD(TD_CUR),             ALGR(KC_0),              KC_RBRC,       DE_ASTR,  TD(TD_ANG),     S(KC_NUBS),       DE_TILD,          KC_UP,       KC_TRNS,
                                                 KC_TRNS,     KC_LGUI,                 KC_LALT,               KC_TRNS,              MO(_LNAV),              KC_TRNS,                    KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS
  ),

/* L3
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * | GAME | Reset|DEBUG | RGB  |RGBMOD| HUE+ | HUE- |lclick| ms-u |rclick|ms-w+ | BACKLIT |
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
    TG(_GAME),     RESET,             DEBUG,      RGB_TOG,       RGB_MOD, RGB_HUI, RGB_HUD, KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,   KC_MS_WH_UP,    BACKLIT,
    TG(_SWAP),     KC_NO,      KC_MS_ACCEL0, KC_MS_ACCEL1,  KC_MS_ACCEL2, RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT, KC_MS_WH_DOWN,    KC_TRNS,
    TG(_LNAV), TG(_LSYM),             KC_NO,        KC_NO,     TG(_SWAP), RGB_VAI, RGB_VAD, KC_MS_BTN1,  KC_MS_BTN2,   KC_MS_BTN3,       _______,    _______,
    TO(_L0),     _______,           _______,      _______,       _______, _______,             _______,     _______,      _______,       _______,    _______
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
    KC_TRNS,         KC_F1,               KC_F2,       KC_F3,               KC_F4,       KC_LALT,     KC_PGUP,      KC_APP,        CTLSFTF,       KC_RALT,        KC_PSCR,       KC_TRNS,
    KC_TRNS,         KC_F5,               KC_F6,       KC_F7,               KC_F8,       KC_LGUI,     KC_PGDN,   PICKFIRST,        PICK2ND,       PICK3RD,        KC_LALT,       KC_TRNS,
    KC_TRNS,         KC_F9,              KC_F10,      KC_F11,              KC_F12,       KC_LCTL,      KC_ESC,     KC_BSPC,     KC_MS_BTN2,       KC_LGUI,        KC_VOLU,       KC_TRNS,
    KC_TRNS,       KC_TRNS,             KC_TRNS,     KC_TRNS,             KC_TRNS,       KC_TRNS,                  KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_VOLD,       KC_TRNS
  )    

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _L0:
        hold_feature_active = 1;
        break;
    case _GAME:
        hold_feature_active = 0;
        break;
    }
  return update_tri_layer_state(state, _LNAV, _LSYM, _L3);
}