 # an autosymbol keymap for bm40hsrgb
similar to autoshift uses key_hold to produce an alternativ key -> a symbol
for use with German keyboard layout

features:
no VIA because of unknown incomptibilities
tap dance
custom keycodes
rgb per layer
gaming layer:   must be a lower number than NAV and SYM-Layer, 
                process_record_user ignore alphas on gaming layer,
                don 't uses TapDance on gaming layer, 
                find goog keys for shift and space for WASD
                DF() doesn't do the trick if you want an callback, so I just use TG() on _L3

todo light_control if OSM(modifier) is locked

todo light intensity controls are inactive -> search solution in oryx keymap code

todo: Key Overrides may help with shift - backspace / Layer 3

(todo): get_tapping_term in combination with new custom keycodes TT_PLUS, TT_MINUS, TT_OFF, TT_ON would make TAPPING_TERM configurable on the fly, but try and error seems to be sufficient

todo: cleanup layer 3 from F-keys

info tapdance usage before custom process_record_user (there have been serious errors on bm40rgb if the dbl_tap array got too big)

 23 x hold (autosymbol),
 11 x hold+dbltap,
  3 x hold+dbltap+dblhold,
  5 x hold+dblhold (autoclose),
6(4)x hold (autoclose),
  2 x mod_tap emulation with shifted keycode,
  2 x mod_tap emulation with extra double tap,
***********************************************
 52(50) keys pysical keys 47

RECONSIDER () instead of DBL_TAP_HOLD + n t f could be mapped to DBL_TAP_HOLD + u i r   ; also  DBL_TAP_HOLD u > () + LEFT

reconsider how to aktivate ADJUST-Layer ? Space + NAV  vs L4 + NAV
(reconsider) is N-Shift too slow compared to F-Shift? playing with get_tapping_term TD(TD_N) ?!

(reconsider) a basic consideration was that using the cursor keys is a "one hand" operation thus RAISE must activate NAV layer
(reconsider) but having dedicated cursorkeys makes this unnecessary and LOWER -> NAV is more comfortable

train use numpad blind (onhand  left)
train use L2 navigation

info backtick ` is only available as Shift(tick) on L2  (or as ahk macro: ,y)
info # $ () <> ~ are only available on SYMBOL-Layer or per double_tap_hold (or as ahk macros)
info < and @ are available per double_tap , or q even without _hold
info € is only available per ctl+alt+e €

info [ and { are not working in windows terminal when done as CTL(ALT()) always use ALGR()
info i, h and u will not use dbl_tap any more to allow words like: Auufer, Buchhalter, nachher,...

info TAPPING_TERM 140 is good for typing äöüß but most keys should have longer timeouts, fixed by using TAPPING_TERM per key

info about custom autosymbol funtionality:
info single_tap_hold for r i p j b s g h  is not realized by tap dance, but instead in matrix_scan_user and process_record_user because of tap_dance array overflow,
     after removal of NumToFKey-dbltaps this is maybe not necessary anymore

AUTOCORRET
info TAP_HOLD is autocorreted as SINGLE_TAP if modifiers are active e.g. SHIFT + r_hold > R instead of S(])
info DBL_TAP_HOLD is autocorreted to bb pp rr tt  instead of b+ p~ r] t)
info AHK does additional aä > ä ... autocorrection, but that is not very usefull

TAP Dance Problems/Inconsistencies/specialties
special         DBL_TAP_HOLD m has autorepeat **** but DBL_TAP_HOLD * has no autorepeat
special         DBL_TAP_HOLD bsp has autorepeat
inconsistent    shift + DBL_TAP KOMMA gives S(<) = > instead of < (maybe correct)
inconsistent    shift + DBL_TAP_HOLD dash  gives nothing
inconsistent    shift + DBL_TAP_HOLD q     gives nothing
inconsistent    shift + DBL_TAP      q     gives nothing
inconsistent    shift + TAP_HOLD Q R I P S G H B ; : _          => autocorreted to ignore HOLD 
inconsistent    shift + TAP_HOLD W Z U O A L M> " & Ü Ö Ä ' *   => shifting symbols is necessary for diacrits, but no autocorrection is done for the others        
inconsistent    shift + TAP_HOLD D F N T                        => no output a) mods only, most likley correct this way
inconsistent    shift + TAP_HOLD E Y X C V >                    => no output b) shifted key does not exist, no autocorrection done
info shift + non shiftable key (e.g. A(C(KC_E))) outputs shift+€=nothing instead of ignoring the shift, but ignoring the shift in general does not work either
special Ä Ü Ö only mod shift neeeds to be passed through
special shift + SINGLE_HOLD . > : correct DBL_TAP_HOLD > correct
special shift + SINGLE_HOLD - > _ correct DBL_TAP_HOLD ~ correct
special dbl_tap_hold ESC sends ^ as dead key + SPACE - dance_autorepeat_finished checks for ==KC_GRAVE (immitating custom key CIRCUMFL) - workaround: use ahk ,q > ^
special ESC/Home (BSP/End) needs all mods passed through (see dance_autorepeat_)

info _each and _reset funtions are often the same and therefore shared between declarations

bug tap dance inside OSL only works if OSL key is held down 
 - solution: process_record_user all OSM set status - flag on down and clear status - flag on up
if tap_dance_each senses!status - flag & OSL active: OSL clear, permanent layer move...
...tap dance continues...on tapdance reset layer move 0
 - workarounds: using autosymbol or not using OSL

COMBOS - conflict with tap dance / autosymbol - autohotkey can be used instead
combo starters: ,< alpha >  q< alpha_minus_ulm> jf cv vc vz vd jz wt wd wf wz
qw = esc better than tapdance qq
    comma - combos, q > 1, w > 2..., . > ,  -  >
G = LT(1, KC_G)H = LT(1, KC_H)
    dot diacrit.,  > ä.n > ü.l > ö. -  > ß / alt
    dot mix.,  > ü. -  > ö., ...ä,  -  > ß;
    
autohotkey QMK compatibility;
SP seemed not to work at all use(default ) # Hotstring SI or # Hotstring SE;
    problems if the final chracter of a hotstring;
    a)has modifiers(these are not always released);
    b)is the result of tapdance or onhold feature;
    c)is on a different layer;
    qmk has additional problems with notepad++and {
        Enter
    };
    solution 1:
    try
        a raw() - block use space before CRLF(only usefull if the final character does not obey the rules a - c); solution 2: exsample Send Mit freundlichen Grüßen {
    Enter
}
     - space before {
    enter
}
    and text on the same line as Enters

reevaluate one shot layer - at least right hand _NAV and _FKEY seem to be never used as OSL ... BSP/DEL?
reevaluate alt - shift - tab: L1h / L1z
reevaluate enter = v on numpad1
reevaluate del key positions? RSFT R_LT_L4 L1_DOT LALT  autohotkey ,r
reevaluate SYM-Layer + k > KC_LOck can be reused
reevaluate F-Key layout being different to number layout

feature idea: single key alt tab {
    KC_LCTL,
    KC_LALT,
    KC_TAB
}
    single hold & modus == OFF: alt + ctrl + tab & modus = ON
        tap & modus == ON: tab
        single hold & modus == ON: modus == ON & Space

feature idea: numberpad 2.0
        €456 -
        3210.
        /789,

leader key: always send KC_LEAD after ESC or up ? Does it work? Are there usecases?
