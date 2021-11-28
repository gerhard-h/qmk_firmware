/* COMBOS will deactivate Autoshift complex Tapdances also break COMBOS it - tap dance callbacks fireing on default might be the problem
{KC_LEFT, KC_RGHT, COMBO_END} works
{TD(TD_COMM), TD(TD_A_UML), COMBO_END}; , > k, ,a > ,fa comma_hold > ;kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
TD(TD_H), KC_R  > 4hr  4 = unsc4hift F$
TD(TD_U_UML), TD(TD_O_UML) uao 

interesting:
With #define COMBO_ONLY_FROM_LAYER _LAYER_A the combos' keys are always checked from layer _LAYER_A even though the active layer would be _LAYER_B.

using autohotkey
; eventmethode (se) plus raw()) (ist compatible mit qmk firmware
#Hotstring se
:*:,a::ä
:*:;A::Ä
:*:,s::ß
:*:,u::ü
:*:,o::ö
:*:,f::$

const uint16_t PROGMEM altf4_combo[] = {TD(TD_KOE_ALT), TD(TD_A_UML), COMBO_END};
const uint16_t PROGMEM re_combo[] = {TD(TD_U_UML), TD(TD_O_UML), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
    COMBO(altf4_combo, KC_F),
    COMBO(re_combo, KC_A)
}; */