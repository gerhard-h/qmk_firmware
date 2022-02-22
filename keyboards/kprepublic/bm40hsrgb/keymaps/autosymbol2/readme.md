# An autosymbol keymap for bm40hsrgb
 ## Highlights
 * uses KEY_HOLD pseudo layer to produce an alternativ key (a symbol) without the need of an layer activiation key - similar to the autoshift concept  
 * uses SHIFT + KEY_HOLD to create an additional pseudo layer (can also be achived by dbl_tap_hold)
 * because pseudo layers don't require additional layer activiation keys, this concept is promising for any keyboard 
 * uses Shift and Ctrl home row mods (prefering stronger fingers)
 * Thumb symetry (high compfort and easy to learn)
 * combined Numpad(phone like) and Navigation layer
 * proper arranged cursor keys
 * option to use tapdance on one shot layers (sounds usefull when imlementig a one hand layout) 
 * for german keyboard layout (when only useing US keys the symbol arrangement could be further improved )
 * slightly improved QUERTY (NT and interpunctuation mod)
 
## qmk options
  * no VIA because of unknown incomptibilities and size limitations
  * tap dance
  * rgb key highlighting per layer
  * custom keycodes (macros)
  * KEY_LOCK_ENABLE
  * SWAP_HANDS_ENABLE
  * MOUSEKEY_ENABLE
 
## features in detail
  ### gaming layer  
    must be a lower number than NAV and SYM-Layer,
    process_record_user ignores alphas (key hold feature) on gaming layer,
    no use of TapDance on gaming layer,
    locate good keys for shift and space in combination with WASD
    DF() doesn't do the trick if you want an callback => TG(_GAME) is used
    
  ### SINGLE_HOLD symbol pseudo layer / AUTOSYMBOL layer
    _instead of pressing a layer key just hold a key longer_
    key arrangemenet partly inspired by NEO, AltGr symbols, and shifted number symbols 
    
 16x q w e u o a s d t l c m , . - esc :tapdance hold (autosymbol),  
 10x r j (z) i p g h (x) (v) b         :custom key hold feature (reconsider using tapdance instead, but there is a bug with having to many tapdances)
  3x f n bsp                           :custom key (reconsider using MT() giving up SFT_HOLD pseudo layer for this keys)       
  
    
  ### SFT_HOLD pseudo layer
    gives the ability to map Shift(SINGLE_HOLD) to any key
    this is alternative/additional approach to using Tapdance DOUBLE_TAP_HOLD feature
    this is way to map symbols on home row mod keys
    this requires the skill not to Hold a upper case letter longer than a lower case letters f
    current exsamples when holding Shift and holding key 
        * activation            output  is shifted       implemented by
        * rsft + hold(F)         -> $   S                custom keycode  lsft + hold(F) -> sft + ctl
        * lsft + hold(N)         -> (   S                custom keycode  rsft + hold(N) -> sft + ctl
        * lsft + hold(T)         -> )   S                tapdance        also dbl_tap_hold (if super fast)
        * rsft + hold(D)         -> #   N                tapdance        also dbl_tap_hold (if super fast)
        * sft + hold(,)          -> <   N                tapdance        also dbl_tap
        * sft + hold(.)          -> >   S                tapdance        also dbl_tap_hold
        * sft + hold(-)          -> ~   N                tapdance        also dbl_tap_hold
        * sft + hold(Q)          -> @   N                tapdance        also dbl_tap    
        * sft + hold(E)          -> []  N                tapdance        also dbl_tap_hold   
        * sft + hold(W)          -> ""  S                tapdance        also dbl_tap_hold
        * sft + hold(C)          -> {}  N                tapdance        also dbl_tap_hold
        * sft + hold(L)          -> ''  S                tapdance        also dbl_tap_hold
        * sft + hold(A)          -> Ä   S                tapdance   
        * sft + hold(U)          -> Ü   S                tapdance
        * sft + hold(O)          -> Ö   S                tapdance       
        * unused keys  
                rjz i p  
                s  gh  
                x  bm  
    
    info for home row shifts ( rsft+hold(F), lsft+hold(N))  $ and ( are only shown after key release. todo test for timeouts  in matrix_scan_user 
    
    reconsider dbl_tap_hold(i or h) sft_hold(i or h) -> \\ or //  
    
    TapDance currently does not support modifier deactivation inside _dance_finished() functions  
    wich is necessary for the is shifted = N cases.
    solution: `quantum/process_tap_dance.c` must be modified to stop enforcing mods.
  ```
      static inline void process_tap_dance_action_on_dance_finished(qk_tap_dance_action_t *action) {
          if (action->state.finished) return;
          action->state.finished = true;
          add_mods(action->state.oneshot_mods);
      // Deactivating the following line will allow for clear_mods, del_mods,... inside _dance_finished functions
      // this is essential to implement a SFT_HOLD_Layer (pseudo layer) that can produce non shifted keycodes since $() are shifted swapping # with % is an option   
      //  add_weak_mods(action->state.weak_mods);
          send_keyboard_report();
          _process_tap_dance_action_fn(&action->state, action->user_data, action->fn.on_dance_finished);
      }
        
  ```
  ### tap dance in one shot layers  
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
                       // let's restrict osl clear globally to standard keys (e.g. A-F24 or whatever you need), and clear it manually in the keymap (tapdances/process_record_user/...)                   
                       switch (action.key.code) {  
                           case KC_A ... KC_F24:  
                              clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);  
                              break;                 
                        }  
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
          

###  one hand typing (todo: find a strategy):
        is currenly activated on layer _L3 (lsft), wich is not onehand itself maybe put it on V too  
        
        maybe use an optimized layout, because that emphazises the benefits of OSL() 
                fdnig   jkm'-  
                stheo   ypl.q  
                cwrau   xbv,z  
                
                - problem existing layer and diacrits clash  
                - combo feature might cause problems  
                - SH_OS onshot fails for  I, P and H  
        more likely by using the swap hand or new layer qmk feature  
                        - new base layer _SWAP necessary
                        - without home row mods  
                        - not having , on the main layer makes Comma makros less attractiv ... swap v and , maybe (use q combos?!)
                        - no _LSYM layer all symbols are done by HOLD or DBL_TAP_HOLD
                        - one_shot_swap and tapdance do not work out - main reason I want to go for individual layers  
                        - mirroring cursor keys is pointless  
                        - mirroring cursor keys in NAV layer is also pointless  
                        - LOWER becomes OSL MIRROR,
                        - SPACE_HOLD can be reused as Shift (implemented as tapdance to work with OSL)
                        - (L4 can also be used as Shift, because it is easier to hold together with other mods OR)
                        - maybe CTL ALT mods should be available as one shot mods OSM(sft) ... ?ctl OSM(win) OSM(alt) OSM(ctl) OSL(mirr) SPC/shift
                        - OSM lock should happen after just 2 taps
                        - SPACE_HOLD could be _LNAV instead of Shift
                        - _NAV is maybe more important now, because BSP ENTER DEL HOME are only there?
                        - esc > bsp S(esc) > del because escape is not so relevant?
                        - bottom left ctl could become TO(_NUM) or OSL(_NUM); additional qw>1, qe>2,... 
                        - TAB can become TO(NAV) ...   
                        - or TAB (L4) can cycle TO(Num) TO(Macro) TO(FKEY) TO(NAV)?  
                        - Shift can become TO(???) and TO(0)  
                        - alt is only on the mouse ... ctrl too?  

## todos, reminders, ideas 

reconsider RAISE and right side Layer4 keys Tap function: Tab? Del?

todo light_control if OSM(modifier) is locked  (may be check osm status in matrix user)
  
todo light intensity controls are inactive -> search solution in oryx keymap code   
  
info tapdance usage before custom process_record_user (there have been serious errors on bm40rgb if the dbl_tap array got too big)  
  
info L3 ADJUST/Mouse-Layer is reached directly by Space + NAV  and also by  Lower + Raise (but not by  Raise_before_Lower) 
  
(reconsider) a basic consideration was that using the cursor keys is a "one hand" operation thus RAISE must activate NAV layer  
(reconsider) but having dedicated cursorkeys makes this unnecessary and LOWER -> NAV is more comfortable
(reconsider) a basic consideration was that LOWER activates numpad to do onhanded number input
(reconsider) by having thumb symetry this is achieved   
  
info backtick ` is only available as Shift(tick) on LSYM  (or as ahk macro: ,y)  
info # $ () <> ~ ´ are also easyly available on SYMBOL-Layer (or as ahk macros)  
info < and @ are available per double_tap , or q even without _hold 
info € is only available per ctl+alt+e €   
info {} and [] are not working in windows terminal when done as CTL(ALT()) always use ALGR()  
info i, h and u will not use dbl_tap any more to allow words like: Auufer, Buchhalter, nachher,...   
info TAPPING_TERM 140 is good for typing diacrits äöüß but most keys should have longer timeouts, fixed by using TAPPING_TERM per key  
  
info about custom autosymbol funtionality:  
info single_tap_hold for r i p j b s g h  is not realized by tap dance, but instead in matrix_scan_user and process_record_user because of tap_dance array overflow,  
     after removal of NumToFKey-dbltaps this is maybe not necessary anymore  
  
### AUTOCORRCET (reconsider)
info TAP_HOLD is autocorreted as SINGLE_TAP if modifiers are active e.g. SHIFT + r_hold > R instead of S(])  
info DBL_TAP_HOLD is autocorreted to bb pp rr tt  instead of b+ p~ r] t)  
info AHK does additional aä > ä ... autocorrection, but that is not very usefull  
  
### TAP Dance Problems/Inconsistencies/specialties 

#### autorepeat
autorepeat is of for almost all keys  
special         TAP_HOLD m has autorepeats `****...` but DBL_TAP_HOLD m -> * has no autorepeat
special         Backspace and shift(Backspace) -> DEL  have autorepeat>
inconsistent    shift + DBL_TAP KOMMA gives S(<) = > instead of < (maybe correct)  
inconsistent    shift + DBL_TAP_HOLD dash  gives nothing
inconsistent    shift + DBL_TAP_HOLD q     gives nothing  
inconsistent    shift + DBL_TAP      q     gives nothing  

info shift + non shiftable key (e.g. A(C(KC_E))) outputs shift+€=nothing instead of ignoring the shift, but ignoring the shift in general does not work either  
special Ä Ü Ö only mod shift neeeds to be passed through 
  
special dbl_tap_hold ESC sends ^ as dead key + SPACE - dance_esc_finished checks for ==KC_GRAVE (immitating custom key CIRCUMFL) - workaround: use combo ,q > ^  
special ESC/Home (ESC/End) needs all mods passed through  
  
info _each and _reset funtions are often the same and therefore shared between declarations  

### COMBO ideas  
info qmk-COMBOS - conflict with tap dance / autosymbol - autohotkey can be used instead 
can for exsmple OSL(1) MT(1) be a combo?
good combo starters:
                ,<alpha>
                q<alpha minus u, l, t, m>
                cv
                jf jz 
                vc vz vd 
                wt wd wf wz  
    qw = esc - to get rid of the esc key
    comma - combos, q > 1, w > 2...,j > 5 ,a > 6 ,...

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
      
### autohotkey QMK compatibility
    Hotstring problems if the final/activation character of a hotstring  
    a) has modifiers(these are not always released);  
    b) is the result of tapdance or onhold feature;  
    c) is on a different layer;  
    qmk has additional problems with notepad++and {  
        Enter  
    };  
    solution: use komma to fire hotstrings
  
reevaluate one shot layer - at least right hand _NAV and _FKEY seem to be never used as OSL
reevaluate alt - (shift) - tab: L1h / L1z  
reevaluate enter key positions? 
reevaluate del key positions? RSFT R_LT_L4 L1_DOT LALT  autohotkey ,r  
reevaluate SYM-Layer + k > KC_Lock
reevaluate F-Key layout being different to number layout  
reevaluate Shift + BSP = DEL
reevaluate DBL_TAP ESC = END   

#### feature idea: single key alt tab
 {  
    KC_LCTL,  
    KC_LALT,  
    KC_TAB  
 }  
    single hold & modus == OFF: alt + ctrl + tab & modus = ON  
        tap & modus == ON: tab  
        single hold & modus == ON: modus == ON & Space  
  
#### feature idea: numberpad 2.0  
        €456-  
        3210.  
        /789,  
  
#### leader key idea:
always send KC_LEAD after ESC or up ? Does it work? Are there usecases?  

# home row mods timeing issues

CTL and ALT need long activation presses, so they don't conflict with fast typing
(timeing issue) pressing f and i (not a tapdance) 
 * simaltanously gives I                        > ok
 * simaltanously holding both gives I           > ok
 * in succsession gives fi,                     > ok
 * in superfast wrong order gives I or If       > problem! if 'if' is what you wanted 
 * in fast wrong order hold gives ẞ             > bad handling invoking shift during hold 
 * in supersuperfast succsession gives i        > problem
(timeing issue) pressing f and e (is  a tapdance)
 * simaltanously gives E                        > ok
 * simaltanously holding both gives e           > bad handling
 * in succsession gives fe,                     > ok
 * in superfast wrong order gives e,            > problem because e_down f_down f_up ep_up all within TAPPING_TERM
 * in superfast succsession gives e             > problem! f is missing: f_down e_down f_up ep_up all within TAPPING_TERM
todos
 * make this tests with MT()
 * try retro tapping 
 * reduce TAPPING_TERM
 * use Tapdance for all cases  
 
# Alternativ layout/typing ideas
instead of the hold feature it may be faster to just activate the symbol layer (to type diacrits)
and use MT(shift, space) instead of homerow mod shift, but personaly I found autosymbol to be faster to learn and TYP
I tested this 
        LOWER > right symbols
        RAISE > left symbols
        SPACE > shift
but didn't like cases like 
 * Fä where the thumb has to be faster than the fingers to not became the bottleneck
 * Ä where you have to shift with the other thumb than usual  
solution 1: use classical shift keys, but these would force my whole hand outwards ~ half a key
solution 2: LOWER = RAISE > all symbols, allows to shift as normal but requires diacrits to be pressed one handed or two handed in respect to the preceding letter 
solution 3: have homerow SHIFT on the Symbol-Layer
solution 4: have OSL(SYM) and make sure Space/Shift does not clear the osl status
solution 5: tapdance diacrits on the OSL layer to get shifted versions