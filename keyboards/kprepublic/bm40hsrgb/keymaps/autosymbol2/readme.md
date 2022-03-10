# An autosymbol keymap for bm40hsrgb
 ## Highlights
 * uses KEY_HOLD pseudo layer to produce an alternativ key (a symbol) without the need of an layer activiation key - similar to the autoshift concept  
 * uses SHIFT + KEY_HOLD to create an additional pseudo layer (can also be achived by dbl_tap_hold)
 * because pseudo layers don't require additional layer activiation keys, this concept is promising for any keyboard 
 * uses Shift and Ctrl home row mods (prefering stronger fingers)
 * Thumb symetry (high compfort and easy to learn)
 * combined Numpad(phone like) and Navigation layer
 * proper arranged cursor keys on a 40% keyboard
 * option to use tapdance on one shot layers (sounds usefull when imlementig a one hand layout) 
 * for german keyboard layout (when only useing US keys the symbol arrangement could be further improved )
 * slightly improved QUERTY (NT and interpunctuation mod)
 
## qmk options
  * no VIA because of unknown incomptibilities and size limitations using extra layers
  * tap dance
  * rgb key highlighting per layer
  * custom keycodes (macros, autosymbol, home row shift)
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
    
 22x q w e z u i o a s d h t l y x c v m , . - esc      :tapdance hold (autosymbol),  
  5x r j p g b                                          :custom key hold feature (autosymbol)
  2x f n                                                :custom key home row shift   
  1x k                                                  :mod tap
  (reconsider) using tapdance instead of custom key hold feature, but there is a bug with having to many tapdances (not tried to reproduce on planck)
  (reconsider) using MT() instead of 'custom key home row shift' but that looses SFT_HOLD symbols for F and N   
  fixed bug Nf/Fn instead of nf/fn when typing very fast Fn debug output:

  
  here Fn is corrected to fn within process_record_user because because diff < 80ms
  ```
OLKB:Planck:1: N down ft: 62629 nt: 62687 pressed: 1 time: 62687
OLKB:Planck:1: F tap ft: 62629 nt: 62687 pressed: 0 time: 62729
OLKB:Planck:1: F tap diff: 58 ls: 2 rs: 32
OLKB:Planck:1: N tap ft: 62629 nt: 62687 pressed: 0 time: 62783
OLKB:Planck:1: N tap diff: 4294967238 ls: 0 rs: 32
  ```
  
  here Fn is not  corrected within process_record_user maybe because the letters seem to be typed by matrix_scan
  but it only happens if F-up is forcefully delayed 
  ```
OLKB:Planck:1: F down ft: 64111 nt: 62687 pressed: 1 time: 64111
OLKB:Planck:1: N down ft: 64111 nt: 64155 pressed: 1 time: 64155
  ```
  the key down events must be within less than 50ms, so a timer based fix seems possible
  
### SFT_HOLD pseudo layer

gives the ability to map Shift(SINGLE_HOLD) to any key
this is alternative/additional approach to using Tapdance DOUBLE_TAP_HOLD feature
this is way to map symbols on home row mod keys
this requires the skill not to Hold a upper case letter longer than a lower case letters f
current exsamples when holding Shift and holding key  
```
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
 * sft + hold(I)          -> \\  N                tapdance        also dbl_tap_hold
 * sft + hold(H)          -> //  S                tapdance        also dbl_tap_hold
 * sft + hold(A)          -> Ä   S                tapdance   
 * sft + hold(U)          -> Ü   S                tapdance
 * sft + hold(O)          -> Ö   S                tapdance     
  
 * unused keys  
         rjz    p  
         s  g   
         xv bm  
```
info for home row shifts rsft+hold(F) -> '$' and lsft+hold(N) -> ')'  to not only show up after key release they are handeled in matrix_scan_user too

still inconsistent (and unclear what is best):
```
    sft + hold(m,z)         -> *,&             
    sft + hold(r,b,s,p,j,g) -> R,B,S,P,J,G
    sft + hold(x,v)         -> nothing
```
todos  
 * increase Tapping Term for everything not producing a upper case letter
 * favor upper case letter  

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
### Home row mods

Using tapdance for multiple home row mods leads to 
 * not activated mods when pressing the keys at the same time (long timespan)
 * inconsistent behaviour when typing fast
 * combinations of mod tap (alt) and tapdance (ctrl)
 
Using custom key home row shift leads to 
 * when pressing the ctl sft at the same time (short timespan) there is an asymetric behavior
        * df -> d
        * nt -> ctl + sft
        * but because the middle finger is longer t will be down faster: tn -> t
        * inward fingeractivation always produces d or t
   workaround: Always Using Outward Finger Activation
   workaround/todo: use MT() and test if we can process MT in process record user
 * combinations of mod tap (alt) has no timing issues but may send the MT() key after releasing solution: disable retro tapping 

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
After disabling clear_oneshot it can/must be called in custom keycodes (process_record_user) and tapdances  
for example in all your _dance_reset callbacks  
ACTION_TAP_DANCE_FN_ADVANCED_USER(..._each_tap, ..._dance_finished, ..._dance_reset, user_user_data)  
```
if (is_oneshot_layer_active()) clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);  
```
Remember MT() will still clears OSL, but here we mostly use Tapdance as replacement for MT()

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

todo add light_control if OSM(modifier) is locked  (may be check osm status in matrix user)
  
todo bm40rgb light intensity controls are inactive -> search solution in oryx keymap code   
todo planck has the Backlit key any purpose?  
info tapdance usage: there have been serious errors on bm40rgb/idobo and maybe all amtel if the dbl_tap array got too big, so far not reproduced on planck 
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
info single_tap_hold for r p j b g is not realized by tap dance, but instead in matrix_scan_user and process_record_user because of tap_dance array overflow,  
     after removal of NumToFKey-dbltaps this is maybe not necessary anymore  
  
### AUTOCORRCET (reconsider)
info TAP_HOLD is autocorreted as SINGLE_TAP if modifiers are active e.g. SHIFT + r_hold > R instead of S(])  
info DBL_TAP_HOLD is autocorreted to bb pp rr tt  instead of b+ p~ r] t)  
info AHK does additional aä > ä ... autocorrection, but that is not very usefull  
  
### Retro Tapping 
(reconsider) only listing keycodes we really want it on
Has noeffect on homerow mods d, f, n, t as MT is not used for them
 * does some kind of autocorrection in case of MT(ALT,K) but some applicaions register ALT(K)
 * MT,ACSW,4560  are also unpredictable depending on mod and application
 * OSL keys are excluded because there is strange behavior in notepad++
 * MT(SFT, DEL) is also excluded to avoid unwanted deletes
 
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

CTL and ALT have long activation presses, so they don't conflict with fast typing
(timeing issue) pressing f and p or (r, j ,g, b) (not using tapdance) 
 * simaltanously gives P                        > ok
 * simaltanously holding both gives P           > ok
 * in succsession gives fp,                     > ok
 * in superfast wrong order gives Pf or P       > problem? Pf  'pf' is what you wanted (unlikely to happen in pratice)
 * in fast wrong order hold gives ?             > ok - bad handling invoking shift during hold 
 * in supersuperfast succsession gives fp or P  > ok
(timeing issue) pressing f and e (is  a tapdance)
 * simaltanously gives E                        > ok
 * simaltanously holding both gives e           > bad handling
 * in succsession gives fe,                     > ok
 * in superfast wrong order gives e,            > ok (fixed) 
 * in superfast succsession gives e             > ok (fixed)
todos
 * make this tests with MT()
 * try retro tapping 
 * reduce/enlarge TAPPING_TERM
 * use Tapdance for all cases  
 
(bug) Upper case F only possible with RShift or one shot modifiers tap, also LShift+F unregisters LShift even if held down
      same with N and LShift ... who cares
 
# Alternativ layout/typing ideas ... the past
instead of the autosymbol hold feature it may be faster to just activate the symbol layer (to type diacrits)
and use MT(shift, space) instead of homerow mod shift, but personaly I found autosymbol to be faster to learn and to TYPE
I tested this 
        LOWER > right symbols
        RAISE > left symbols
        SPACE > shift
but didn't like (because the thumb gets overworked) in cases like 
 * Fä where the thumb has to be faster than the fingers to not became the bottleneck
 * Ä where you have to shift with the other thumb than usual 
idea 1: use classical shift keys, but these would force my whole hand outwards ~ half a key
idea 2: LOWER = RAISE > all symbols, allows to shift as normal but requires diacrits to be pressed one handed or two handed in respect to the preceding letter 
idea 3a: use homerow SHIFT only on the Symbol-Layer
idea 3b: use homerow SHIFT instead of thumb shift everywhere
idea 4: have OSL(SYM) and make sure Space/Shift does not clear the osl status
idea 5: tapdance diacrits on the OSL layer to get shifted versions

# Alternativ layout/typing ideas ... the future
After having dealt with all the quirks of homerow SHIFT, its finally the way to go.  
Using fast timinig for Shift and slower timings for other mods.  
Not using diacrit-autosymbol but having a layer key (eg. space) to the symbol layer has problems.
 * Typing fünf or für would require swaping the used thumb depending on the letter after 'ü'
   (using alwas the same thumb might be more practical)
 * Pressing space and a key at the same time should favor layer activation 
 * Also timing for layer deactivation gets an issue
learnings:
 * use symbol layer activated by a layer key
 * only diacrits should be accessible by autosymbol hold. - so learning tap vs hold is restricted to only some keys
 * diacrits must not be on the symbol layer - meaning symbols can be otimized freely ... but
 * if dicrits conflict with home row mods like a/ä and s/ß  
   consider puttig the complete set of home row mods on the symbol layer
   (this means keep your symbol-home-row free of symbols you want to tapdance/autosymbol² on)
  