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
//#include "rgb.c"
enum layers { _L0, _GAME, _SWAP, _LNAV, _LSYM, _L3, _L4};
#include "customkeys.c"
#include "tapdance.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
*  ESC    Prtscreen Rdesk-    ESC/Home ^  1           2          3         4              5          6          7           8             9             0             DEL
*  TO(L0) TO(L3)    AMulti    Home        Q End @     W " ""     E { {}    R  } atab      J $        Z & &&     U Ü         I \ \\        O Ö           P ?           Backspc
*  VOLU   PgUp      PGMulti   TAB/Ctrl    A Ä         S ß '      D Ctl     F  Sft         G = ==     H / //     N Sft       T Ctl         L Alt         K WIN         Enter/Ctrl
*  VOLD   PgDn          NO    OSM-Shift   Y Ctl+Y     X | ||     C ( ()    V ) Enter      B + ++     M *        , ; <       . : >         - _ ~         Up            DEL/Shift
*  CTL    ALT           NO    OSM-Ctrl    WIN         OSM-Alt    OSL-Sym   OS-TGL-Num     SPC/L4     SPC/Num    OSL-Sym     OS-TGL-L4     Left          Down          Right
*/       
[_L0] = LAYOUT_ortho_5x15(

KC_ESC,  KC_PSCR, C(A(KC_PAUSE)),
                          TD(TD_ESC),     KC_1,         KC_2,        KC_3,       KC_4,      KC_5,     KC_6,        KC_7,        KC_8,         KC_9,        KC_0,         KC_DEL,
TO(_L0), TO(_L3), TD(TD_ATAB),
                             KC_HOME, TD(TD_Q),     TD(TD_W),    TD(TD_E),   TD(TD_R),  TD(TD_J), TD(TD_Z),    TD(TD_U),    TD(TD_I),     TD(TD_O),    TD(TD_P),        KC_BSPC,
KC_VOLU, KC_PGUP, TD(TD_APUP),
                       HYPR_T(KC_TAB), TD(TD_A),    TD(TD_SS), CTL_T(KC_D),    F_LSHFT,  TD(TD_G), TD(TD_H),     N_RSHFT, CTL_T(KC_T),  ALT_T(KC_L), GUI_T(KC_K), RCTL_T(KC_ENT),
KC_VOLD, KC_PGDN, KC_NO,
                       OSM(MOD_LSFT), TD(TD_Y),     TD(TD_X),    TD(TD_C),   TD(TD_V),  TD(TD_B), TD(TD_M), TD(TD_COMM),  TD(TD_DOT),  TD(TD_DASH),       KC_UP, RSFT_T(KC_DEL),
KC_LCTL, KC_LALT, KC_NO,
                       OSM(MOD_LCTL),  KC_LGUI, OSM(MOD_LALT), OSL(_LSYM), OSL(_LNAV),
                                                                                       LT(_L4,KC_SPC),LT(_LNAV,KC_SPC),
                                                                                                         LT(_LSYM, KC_F24),    OSL(_L4),      KC_LEFT,     KC_DOWN,        KC_RGHT    
),

[_GAME] = LAYOUT_ortho_5x15(
	    
KC_ESC,  KC_TRNS,   KC_NO,    KC_ESC,     KC_1,         KC_2,       KC_3,       KC_4,      KC_5,     KC_6,              KC_7,       KC_8,       KC_9,    KC_0,    KC_DEL,
TO(_L0),  TO(_L0),  KC_NO,
                              KC_TAB,     KC_Q,         KC_W,       KC_E,       KC_R,      KC_J,     KC_Y,              KC_U,       KC_I,       KC_O,    KC_P,    KC_BSPC,
KC_TRNS,  KC_TRNS,  KC_NO,
                              KC_TAB,     KC_A,         KC_S,       KC_D,       KC_F,      KC_G,     KC_H,              KC_N,       KC_T,       KC_L,    KC_K,    KC_ENT,
KC_TRNS,  KC_TRNS,  KC_NO,
                             KC_LSFT,     KC_Z,         KC_X,       KC_C,       KC_V,      KC_B,     KC_M,           KC_COMM,     KC_DOT,    KC_SLASH,   KC_UP,    KC_RSFT,
KC_TRNS,  KC_TRNS,  KC_NO,
                             KC_LCTL,  KC_LALT,      KC_LSFT,     KC_SPC,     KC_SPC, LT(_L4,KC_SPC), LT(_LSYM,KC_SPC), OSL(_LNAV), OSL(_L4),    KC_LEFT, KC_DOWN,    KC_RGHT
 ),
[_SWAP] = LAYOUT_ortho_5x15(    
 KC_ESC,     KC_TRNS,        KC_NO,     KC_ESC,     KC_1,        KC_2,          KC_3,          KC_4,          KC_5,           KC_6,              KC_7,           KC_8,        KC_9,               KC_0,    KC_DEL,
TO(_L0),     TO(_L0),        KC_NO,     KC_TAB,     KC_Q,        KC_W,          KC_E,          KC_R,          KC_J,           KC_Y,              KC_U,           KC_I,        KC_O,               KC_P,    KC_BSPC,
KC_TRNS,     KC_TRNS,        KC_NO,     KC_TAB,     KC_A,        KC_S,          KC_D,          KC_F,          KC_G,           KC_H,              KC_N,           KC_T,        KC_L,               KC_K,    KC_ENT,
KC_TRNS,     KC_TRNS,        KC_NO,    KC_LSFT,     KC_Z,        KC_X,          KC_C,          KC_V,          KC_B,           KC_M,           KC_COMM,         KC_DOT,     KC_SLASH,              KC_UP,    KC_RSFT,
KC_TRNS,     KC_TRNS,        KC_NO,    KC_LCTL,  KC_LALT,     KC_LSFT,        KC_SPC,        KC_SPC, LT(_L4,KC_SPC), LT(_LSYM,KC_SPC),         OSL(_LNAV),       OSL(_L4),     KC_LEFT,            KC_DOWN,    KC_RGHT
 ), 
/*           
*________ TO(_LSYM) ________ ________         -                   1                  2                3              INS                 A(TAB)        HOME          UP            END        PGUP          ________
*________ ________  ________ ________         .                   4alt               5ctl             6sft           0win                AS(TAB)       LEFT          DOWN          RGHT       PGD           ________
*________ ________  ________ ________         ,                   7                  8                9              ENT           S(RBRC)                  ESC           BSP           DEL           ENT        ________      ________
*________ ________  ________ ________      ________             _______         ________           ________        ________       ________      TG(_LSYM)          ________        ________      ________
* NUM NAV*/
[_LNAV] = LAYOUT_ortho_5x15(
KC_TRNS,  KC_TRNS, KC_TRNS,  KC_F12,       KC_F1,        KC_F2,        KC_F3,        KC_F4,       KC_F5,        KC_F6,   KC_F7,    KC_F8,      KC_F9,          KC_F10,      KC_F11,
KC_TRNS, TO(_LSYM), KC_TRNS,                                                                                                               
                            KC_TRNS, TD(TD_DASH),         KC_1,         KC_2,         KC_3,      KC_SPC,       KC_ESC, KC_HOME,    KC_UP,     KC_END, LGUI_T(KC_PGUP),     KC_BSPC,
KC_TRNS,  KC_TRNS, KC_TRNS,                                                                                                                
                            KC_TRNS,  TD(TD_DOT), LALT_T(KC_4), LCTL_T(KC_5), LSFT_T(KC_6), GUI_T(KC_0),       KC_TAB, KC_LEFT,  KC_DOWN,    KC_RGHT, LALT_T(KC_PGDN),     KC_TRNS,
KC_TRNS,  KC_TRNS, KC_TRNS,                                                                                                                
                            KC_TRNS, TD(TD_COMM),         KC_7,         KC_8,         KC_9,        KC_1,       KC_ENT, KC_BSPC,   KC_DEL, KC_MS_BTN2,         KC_TRNS,     KC_TRNS,
KC_TRNS,  KC_TRNS, KC_TRNS,                                                                                                                
                            KC_TRNS,     KC_TRNS,      KC_TRNS,      KC_TRNS,         TG_LNAV,      KC_TRNS,KC_TRNS,   KC_TRNS,  TO(_L3),    KC_TRNS,         KC_TRNS,     KC_TRNS
  ),
/* 
*                                ^             !             "          {            }                 $           &        %             \             #        ?            ________
*                         ________             `             '          [            ]                 =           /        "             '             !        €            ________
*                         ________             ´             |          (            )                 +           *        <             >             ~       ________      ________
* SYMBOL*/
[_LSYM] = LAYOUT_ortho_5x15(
KC_TRNS, KC_TRNS, KC_TRNS,        KC_F12,         KC_F1,          KC_F2,          KC_F3,            KC_F4,         KC_F5,           KC_F6,      KC_F7,          KC_F8,         KC_F9,         KC_F10,        KC_F11,
    KC_TRNS, TG(_L4), KC_TRNS,
                          CIRCUMFL,         DE_EXLM, TD(TD_DQUOT),   TD(TD_CUR),  ALGR(KC_0),        KC_DLR,   DE_AMPR,    KC_PERC,    DE_BSLS,      KC_NUHS,      DE_QUES,     KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,
                           KC_TRNS,       STICKTICK,  TD(TD_QUOT),   TD(TD_SQU),  ALGR(KC_9),       KC_RPRN,   DE_SLSH, TD(TD_DQUOT), TD(TD_QUOT),   DE_EXLM,   ALGR(KC_E),     KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,
                           KC_LSFT,        TICKTICK,      DE_PIPE,   TD(TD_PAR),     KC_LPRN,       KC_RBRC,   DE_ASTR, TD(TD_ANG), S(KC_NUBS),      DE_TILD,        KC_UP,     KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,
          KC_TRNS,     KC_LGUI,     KC_LALT,               KC_TRNS,                TO(_L3),              KC_TRNS,KC_TRNS,                            KC_TRNS,        KC_TRNS,       KC_TRNS,        KC_TRNS,       KC_TRNS
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
[_L3] = LAYOUT_ortho_5x15(
    RESET,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,     KC_TRNS,      KC_TRNS,       KC_TRNS,              KC_TRNS,
    KC_TRNS,    TO(_LNAV), KC_TRNS,
                        TO(_GAME),          RGB_TOG,        DEBUG,       RGB_TOG,    TG(_SWAP),  RGB_HUI, RGB_HUD, KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,   KC_MS_WH_UP,    TO(_L0),
    KC_TRNS,    KC_TRNS, KC_TRNS,
                        TO(_SWAP),        RGB_MOD, KC_MS_BTN3,  KC_MS_BTN2, KC_MS_BTN1,  RGB_SAI, RGB_SAD, KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT, KC_MS_WH_DOWN,    KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS,
                        TO(_LSYM),        KC_TRNS,   KC_MS_ACCEL0,    KC_MS_ACCEL1,   KC_MS_ACCEL2,  RGB_VAI, RGB_VAD, KC_MS_BTN1,  KC_MS_BTN2,   KC_MS_BTN3,       _______,    _______,
    KC_TRNS,    KC_TRNS, KC_TRNS,
     TO(_L0),     KC_TRNS,           _______,      _______,        KC_LCTL, TO(_L0), TO(_L0),     KC_LSFT,     _______,      _______,       _______,  _______
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
[_L4] = LAYOUT_ortho_5x15(
    KC_TRNS,     KC_TRNS,        KC_TRNS,       KC_F12,         KC_F1,          KC_F2,          KC_F3,            KC_F4,         KC_F5,           KC_F6,      KC_F7,          KC_F8,         KC_F9,         KC_F10,        KC_F11,
    KC_TRNS,     TO(_GAME),      KC_TRNS,
                         KC_TRNS,         KC_F1,        KC_F2,        KC_F3,        KC_F4,     KC_INS,         KC_ESC,     KC_APP,   C(S(KC_F)),  KC_RALT,        KC_PSCR,       KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,
                         KC_TRNS,         KC_F5,        KC_F6,        KC_F7,        KC_F8,     KC_LALT,     A(KC_TAB),  PICKFIRST,      PICK2ND,  PICK3RD,        KC_LALT,       KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,
                         KC_TRNS,         KC_F9,       KC_F10,       KC_F11,       KC_F12,     KC_LCTL,  A(S(KC_TAB)),    KC_LSFT,      KC_LCTL,  KC_LALT,        KC_LGUI,       KC_TRNS,
    KC_TRNS,     KC_TRNS,        KC_TRNS,
          KC_TRNS,       KC_TRNS,             KC_TRNS,     KC_TRNS,             KC_TRNS,       KC_TRNS,      KC_TRNS,      KC_TRNS,       TG_L4,  KC_TRNS,        KC_VOLD,       KC_VOLU
  )    

};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _L0:
        if (caps_lock_on_key == KC_CAPS){
                tap_code(KC_CAPS);
                caps_lock_on_key = KC_NO;
        }
        if (default_layer_moved) {
                rgblight_sethsv_noeeprom(HSV_RED);
                rgblight_mode_noeeprom(6);
        } else if (default_layer_movedl4) {
                rgblight_sethsv_noeeprom(HSV_GREEN);
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        } else {
                rgblight_sethsv_noeeprom(HSV_PURPLE);
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        }
        break;
    case _LNAV:
        rgblight_sethsv_noeeprom(HSV_RED);
        rgblight_mode_noeeprom(6);
        if (caps_state){
                tap_code(KC_CAPS);
                caps_state = 0;
                caps_lock_on_key = KC_CAPS;
        }        
        break;
    case _LSYM:
        /*todo  if switch (biton32(default_layer_state)) {
        case _LNAV:
                 (default_layer_moved && ){
                        return state;             
                else 
                    default_layer_moved = false;           
                    default_layer_set( ((layer_state_t)1 << _L0));
                    return ((layer_state_t)1 << _L3);  
               }
        };*/
    
        rgblight_sethsv_noeeprom(HSV_WHITE);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        if (caps_state){
                tap_code(KC_CAPS);
                caps_state = 0;
                caps_lock_on_key = KC_CAPS;
        }
        break;
    case _L3:
    	//from locked _LNAV don't go to _L3     todo is this code needed with TG_LNAV?
        rgblight_sethsv_noeeprom(HSV_RED);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        switch (biton32(default_layer_state)) {
                case _LNAV:
                            default_layer_moved = false;
                            default_layer_set( ((layer_state_t)1 << _L0));
                            tap_code(KC_NUMLOCK);
                            rgblight_sethsv_noeeprom(HSV_PURPLE);
                            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                            return ((layer_state_t)1 << _L0);
        };
        break;
    case _L4:
        rgblight_sethsv_noeeprom(HSV_GREEN);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        break;
    case _GAME:
        rgblight_sethsv_noeeprom(HSV_WHITE);
        rgblight_mode_noeeprom(2);
        break;
    default:
        rgblight_sethsv_noeeprom(HSV_PURPLE);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        break;
    }
    return state;
}
#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom(); // Enables RGB, without saving settings
  rgblight_sethsv_noeeprom(HSV_GREEN);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  default_layer_movedl4 = false;
  default_layer_moved = false;
}
#endif