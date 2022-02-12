# An autosymbol keymap for bm40hsrgb  
uses key_hold to produce an alternativ key(symbol) - similar to the autoshift concept  
 
## qmk options
  * no VIA because of unknown incomptibilities
  * tap dance
  * rgb key highlighting per layer
  * KEY_LOCK_ENABLE
  * SWAP_HANDS_ENABLE
  * MOUSEKEY_ENABLE
 
## features
  * for use with German keyboard layout
  * diacrits on symbol layer
  * symbol layer partly inspired by NEO and shifted numbers
  * Phone like numpad
  * custom keycodes
  * gaming layer  
    must be a lower number than NAV and SYM-Layer,
    process_record_user ignore alphas on gaming layer,
    don 't uses TapDance on gaming layer,
    find goog keys for shift and space for WASD
    DF() doesn't do the trick if you want an callback, so I just use TG() on _L3
  * tap dance in one shot layers  
    WARNING this is currently not supported by QMK.  
    solution `quantum/action.c` must be modified to not clear the one shot status when pressing a custom keycode  
```  
        void process_action(  
        ...  
            if (is_oneshot_layer_active() && event.pressed && (action.kind.id == ACT_USAGE || !IS_MOD(action.key.code))  
            #    ifdef SWAP_HANDS_ENABLE  
                    && !(action.kind.id == ACT_SWAP_HANDS && action.swap.code == OP_SH_ONESHOT)  
            #    endif  
                    && !keymap_config.oneshot_disable) {  
+                       // let's restrict osl clear globally to standard keys (e.g. A-F24 or whatever you need), and clear it manually in the keymap (tapdances/process_record_user/...)                   
+                       switch (action.key.code) {  
+                           case KC_A ... KC_F24:  
                              clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);  
+                             break;                 
+                        }  
            do_release_oneshot = !is_oneshot_layer_active();  
        ...  
```  
        after disabling clear_oneshot it can/must be called in custom keycodes (process_record_user) and tapdances  
        for example in all your _dance_reset callbacks  
        ACTION_TAP_DANCE_FN_ADVANCED_USER(..._each_tap, ..._dance_finished, ..._dance_reset, user_user_data)  
```  
        if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);  
```  
        remember MT() will still clears OSL, but here we mostly use Tapdance as replacement for MT() 
  * todo? Shift+HOLD pseudo layer  
    to replace dbl_tap_hold with shift_hold
    current cases when holding Shift and holding key  
    * a: d,f,n,t -> hold more mods (holds gets replaced)
    * b: a,u,o -> Ä, Ü, Ö (shift and hold gets applied)
    * c: s -> S (shift gets applied, hold gets ignored) optional correction
    * d: q,r,j,... -> Q, R,J  (shift gets applied, hold gets ignored) optional correction
    * e: w,z,m -> ", &, ',* (shift x2 and hold gets applied)
    * f: ,.-q -> ;:_ (shift and hold are the same)
    * g: e,x,c,v -> no output  
    in cases a, e, f, g autocorrection can be added like this  
        * sft + hold(N) -> (      a        << this is the important case
        * sft + hold(,) -> <      f
        * sft + hold(Q) -> @      f
        * sft + hold(E) -> []     g
        * sft + hold(X) -> |      g
        * sft + hold(W) -> ""     e
        * sft + hold(Z) -> &      e        
    * used 3rd funktion  
    @"[]   Ü Ö  
    Ä # $  ()'  
    ` {}   <>~  
    * unused 3rd funktion  
       rjz i p  
     s  gh  
     x  bm  
    * problem case a:  
      will only trigger for two handed operation, that restriction makes no sense for the other cases  
      hold(N) + hold(T) -> ctl + sft instead of )  
      hold(N) + hold(D) -> # instead of ctl + sft      

+ (todo optimize) one hand typing:  
        maybe   fdnig   jkm'-  
                stheo   ypl.q  
                cwrau   xbv,z  
                - problem existing layer and diacrits clash  
                - combo feature might cause problems  
                - SH_OS onshot fails for  I, P and H  
        more likely by using the swap hand or new layer qmk feature  
                - new base layer necessary  
                        - without home row mods  
                        - mirroring cursor keys is pointless  
                        - mirroring cursor keys in NAV layer is also pointless(mirrored)  
                        - LOWER (or SPACE) becomes OSL MIRROR,  
                        - SPACE_HOLD can be reused, but is to slow for mirror maybe Shift  
                        - one shot mirror and tapdance do not work out  
                        - TAB can become TO(NAV) ...   
                        - L4 can cycle TO(Num) TO(Macro) TO(FKEY) TO(NAV)?  
                        - Shift can become TO(???) and TO(0)  
                        - alt is on the mouse .. ctrl too?  

## todos, reminders, ideas 

todo find usecase for right side RAISE and Layer4 keys Layer Tap  ... Tab? Del?

todo light_control if OSM(modifier) is locked  
  
todo light intensity controls are inactive -> search solution in oryx keymap code  
  
todo: Key Overrides may help with shift - backspace / Layer 3  
  
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
  
info L3 ADJUST-Layer is reached directly by Space + NAV  and also by  Lower + Raise (by remapping Lower and Raise on _NAV)  
info if homerow mods eg. N-Shift are to slow compared to F-Shift consider playing with get_tapping_term TD(TD_N) ?!  
  
(reconsider) a basic consideration was that using the cursor keys is a "one hand" operation thus RAISE must activate NAV layer  
(reconsider) but having dedicated cursorkeys makes this unnecessary and LOWER -> NAV is more comfortable  
  
train use numpad blind (onhand  left)  
train use L2 navigation  
  
info backtick ` is only available as Shift(tick) on L2  (or as ahk macro: ,y)  
info # $ () <> ~ are only available on SYMBOL-Layer or per double_tap_hold (or as ahk macros)  
info < and @ are available per double_tap , or q even without _hold  
info € is only available per ctl+alt+e €  
  
info {} and [] are not working in windows terminal when done as CTL(ALT()) always use ALGR()  
info i, h and u will not use dbl_tap any more to allow words like: Auufer, Buchhalter, nachher,...  
  
info TAPPING_TERM 140 is good for typing diacrits äöüß but most keys should have longer timeouts, fixed by using TAPPING_TERM per key  
  
info about custom autosymbol funtionality:  
info single_tap_hold for r i p j b s g h  is not realized by tap dance, but instead in matrix_scan_user and process_record_user because of tap_dance array overflow,  
     after removal of NumToFKey-dbltaps this is maybe not necessary anymore  
  
AUTOCORRET  
info TAP_HOLD is autocorreted as SINGLE_TAP if modifiers are active e.g. SHIFT + r_hold > R instead of S(])  
info DBL_TAP_HOLD is autocorreted to bb pp rr tt  instead of b+ p~ r] t)  
info AHK does additional aä > ä ... autocorrection, but that is not very usefull  
  
TAP Dance Problems/Inconsistencies/specialties  
special         DBL_TAP_HOLD m has autorepeats `****...` but DBL_TAP_HOLD m has no autorepeat  
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
  
info qmk-COMBOS - conflict with tap dance / autosymbol - autohotkey can be used instead 
can for exsmple OSL(1) MT(1) be a combo?
good combo starters: ,<alpha>
                q<alpha_minus_ulm>
                cv
                jf jz 
                vc vz vd 
                wt wd wf wz  
    qw = esc - to get rid of the esc key
    comma - combos, q > 1, w > 2..., . > ,  -  >  

    dot diacrit  
    .,  > ä  
    .n  > ü  
    .l  > ö  
    .-  > ß  
    
    dot mix  
    ., > ü  
    .- > ö  
    ,a > ä  
    ,s > ß  
      
info autohotkey QMK compatibility;  
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
reevaluate Shift + BSP = DEL
reevaluate DBL_TAP ESC = END   
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
