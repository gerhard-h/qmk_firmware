# An autosymbol keymap for planck rev6
 ## Highlights
 * uses KEY_HOLD pseudo layer to produce an alternativ key (a symbol) without the need of an layer activiation key - similar to the autoshift concept  
 * uses SHIFT + KEY_HOLD to create an additional pseudo layer (can also be achived by dbl_tap_hold)
 * Homerow mod early Shift - allows too release shift keys early as most people will do when typing fast
 * because pseudo layers don't require additional layer activiation keys, this concept is promising for any keyboard 
 * uses Shift and Ctrl home row mods (prefering stronger fingers)
 * Thumb symetry (high compfort and easy to learn)
 * combined (phone like)Numpad and Navigation layer
 * proper arranged cursor keys on a 40% keyboard
 * option to use tapdance on one shot layers (sounds usefull when imlementig a one hand layout) 
 * for german keyboard layout (when only useing US keys the symbol arrangement could be further improved )
 * slightly improved QUERTY (NT and interpunctuation mod)
 * Shift quot -> dquote / shift dquote -> quot ... usefull???
 
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

### Homerow mod early/osm Shift

Home row shifts are implemeted as custom keys because
 * mod tap don't offer DBL_TAP_HOLD or SHIFT_HOLD features
 * tapdance has a very long time frame were simaltanous HOLDs would not work (frist HOLD becomming a TAP)
 * inconsistent tapdance behaviour when typing fast
```
instead of TAPPING_TERM-Start F-Down TAPPING_TERM-End I-Down F-Up   I-Up -> U(I) wich mod tap will handle properly
now also   TAPPING_TERM-Start F-Down TAPPING_TERM-End F-Up   I-Down I-Up -> U(I) is handled 
```
OSM like when releaseing the home row shift to early (in anticipation of preventing two uppercase letters)  
only the first letters becomes uppercased. This System knows about wich key is located on wich side of the keboard and  
thus is able to anticipate the expected correct SHIFT behavior: `fu` can mean `F` or `fu` but `nu` always means `nu`  
following imponderabities had to be tackled
* avoid Nf/Fn instead of nf/fn when typing very fast
* nn/ff in favor of Shift
* tapdance integration, see handle_force_shift_tap(keycode...
* mod tap integraton, see MT(MOD_LALT, KC_K)  
* N and F are not early shifted themselves F-Hold-Up + n -> $n seem to be an irrelevant (bug)

  #### timings
  ```
  homerow shift:        120ms
  homerow ctrl:         140ms
  homerow alt:          250ms
  TAPPING_TERM:         250ms
  fn over F:             80ms - if N (rsft) was pressed after F-down but before F-up don't shift F
  Force Upper Rate:     300ms - maximum of one Uppercased key without shift being down
  Force Upper timeout:  300ms - how much time can pass between Shift-Up and Tap-Up
  ```
  #### Home row shift issues

  Using custom key home row shift leads to 
  * when pressing the ctl sft at the same time (short timespan) there is an asymetric behavior
        * df -> d 
        * nt -> ctl + sft
        * but because the middle finger is longer t will be down faster: tn -> t ()
        * inward fingeractivation always produces d or t
   workaround: Always Using Outward Finger Activation
   info combinations of mod tap (alt) have no timing issues but may send the MT() key after releasing solution: disable retro tapping 
   !reconsider! using MT() instead of home row CONTROL but that means implementig the SFT_HOLD symbols for D and T  but
  
  (bug that never happens) Upper case F only possible with RShift or one shot modifiers tap, also LShift+F unregisters LShift even if Shift/F is held down, same with N and LShift
  
  ##### home row mods timeing checklist

   pressing n and e 
   * simaltanously gives E                        > ok
   * simaltanously holding both gives e           > bad handling
   * in succsession gives ne                      > ok
   * in superfast wrong order gives e             > ok (fixed)
   * in superfast succsession gives e             > ok (fixed)


### SINGLE_HOLD symbol pseudo layer / AUTOSYMBOL layer
  _instead of pressing a layer key just hold a key longer_  
  key arrangement partly inspired by
  * NEO ( place open/close bracets on adjacent index finger, middle finger keys)
  * Place symbols below there shifted number symbols or in proximity to there former location
  * keep basic keys for shell navigation _-\/.* all on the right hand  
  
  implemented using tapdance 

  
### Custom SINGLE_HOLD feature (UNUSED)
there is a bug with having to many tapdances (not tried to reproduce on planck)  
to work around it customhold.c contains a custom autosymbol funtionality realized matrix_scan_user and process_record_user.
But removing the 'HOLD_NUMBER -> F-KEY' was enough to get rid of the tap_dance array overflow
last 5 keys that used the feature were r j p g b
The feature didn't allow for early shift and keeping it for just 5 keys wasted memory
info TAP_HOLD autocorreted as SINGLE_TAP if modifiers are active e.g. SHIFT + r_hold > R instead of S(])
  
### SFT_HOLD pseudo layer

gives the ability to map Shift(SINGLE_HOLD) to any key  
this is alternative/additional approach to using Tapdance DOUBLE_TAP_HOLD feature  
this is also the only way to map symbols on home row shift keys  
this requires the skill not to Hold a upper case letter longer than a lower case letters
current exsamples when holding Shift and holding key  
```
 * activation            output  is shifted       implemented by
 * rsft + hold(F)         -> $   S                custom keycode  lsft + hold(F) -> sft + ctl
 * lsft + hold(N)         -> (   S                custom keycode  rsft + hold(N) -> sft + ctl
 info for home row shifts rsft+hold(F) -> '$' and lsft+hold(N) -> '('  to not only show up after key release they are handeled in matrix_scan_user too
 * lsft + hold(T)         -> )   S                tapdance        also dbl_tap_hold (if super fast)  
 * rsft + hold(D)         -> #   N                tapdance        also dbl_tap_hold (if super fast)
 * sft + hold(,)          -> <   N                tapdance        also dbl_tap
 * sft + hold(.)          -> >   S                tapdance        also dbl_tap_hold
 * sft + hold(-)          -> ~   N                tapdance        also dbl_tap_hold
 * sft + hold(Q)          -> @   N                tapdance        also dbl_tap    
 * sft + hold(E)          -> []  N                tapdance        also dbl_tap_hold   
 * sft + hold(W)          -> ""  S                tapdance        also dbl_tap_hold
 * sft + hold(Z)          -> &&  S                tapdance        also dbl_tap_hold
 * sft + hold(C)          -> {}  N                tapdance        also dbl_tap_hold
 * sft + hold(L)          -> ''  S                tapdance        also dbl_tap_hold
 * sft + hold(I)          -> \\  N                tapdance        also dbl_tap_hold
 * sft + hold(H)          -> //  S                tapdance        also dbl_tap_hold
 * sft + hold(X)          -> ||  N                tapdance        also dbl_tap_hold
 * sft + hold(B)          -> ++  N                tapdance        also dbl_tap_hold
 * sft + hold(G)          -> ==  S                tapdance        also dbl_tap_hold
 * sft + hold(A)          -> �   S                tapdance   
 * sft + hold(U)          -> �   S                tapdance
 * sft + hold(O)          -> �   S                tapdance     
  
 * unused keys  
         rj     p  
         s      
          v  m  
```

inconsistent :
```
    sft + hold(s) -> S autocorrection
    sft + hold(r,v) -> nothing (todo)
```
learnings  
 * high Tapping Term for everything not producing a upper case letter

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
there were no side effects found   

### tap dance in one shot layers  
tap dance in one shot layers allows for OSL(LSYM) wich seems essential for one hand typing
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

info planck doesn't check firmware size 58kb file size was a problem

info L3 ADJUST/Mouse-Layer is reached directly by Space + NAV  and also by  Lower + Raise (but not by  Raise_before_Lower) 
  
(reconsider) a basic consideration was that using the cursor keys is a "one hand" operation thus RAISE must activate NAV layer  
(reconsider) but having dedicated cursorkeys makes this unnecessary and LOWER -> NAV is more comfortable
(reconsider) a basic consideration was that LOWER activates numpad to do onhanded number input
(reconsider) by having thumb symetry this is achieved   
  
info backtick ` is only available as Shift(tick) on LSYM  (or as ahk macro: ,y)  
info # $ () <> ~ � are also easyly available on SYMBOL-Layer or as SHIFT_HOLD (or as ahk macros)  
info < and @ are available per double_tap_without_hold , or q
info � is only available per ctl+alt+e �  or SYMBOL-Layer + k -> �
info {} and [] are not working in windows terminal when done as CTL(ALT()) always use ALGR()  
info i, h and u will not use dbl_tap any more to allow words like: Auufer, Buchhalter, nachher,...   
info short TAPPING_TERM 140 is good for typing diacrits ���� but most keys should have longer timeouts, fixed by using TAPPING_TERM per key  
  
### AUTOCORRCET (reconsider)
info TAP_HOLD is autocorreted as SINGLE_TAP if modifiers are active e.g. CTL + w_hold > C(w) instead of C("), S(s_hold) > S
info DBL_TAP_HOLD is autocorreted to bb pp rr tt  instead of b+ p~ r] t)  
info AHK does additional a� > � ... autocorrection, but that is not very usefull  
  
### Retro Tapping (tested and dismissed)
(reconsider) only listing keycodes we really want it on
Has noeffect on homerow mods d, f, n, t as MT is not used for them
 * does some kind of autocorrection in case of MT(ALT,K) but some applicaions register ALT(K)
 * MT,ACSW,4560  are also unpredictable depending on mod and application
 * OSL keys are excluded because there is strange behavior in notepad++
 * MT(SFT, DEL) is also excluded to avoid unwanted deletes
 
### autorepeat
autorepeat is of for almost all keys  
special         TAP_HOLD m has autorepeats `****...` but DBL_TAP_HOLD m -> * has no autorepeat  
special         Backspace and shift(Backspace)  
special         DBL_TAP_HOLD DEL  has autorepeat  

### TAP Dance Problems/Inconsistencies/specialties 

inconsistent    shift + DBL_TAP KOMMA gives S(<) = > instead of < (maybe correct)  
inconsistent    shift + DBL_TAP_HOLD dash  gives nothing  
inconsistent    shift + DBL_TAP_HOLD q     gives nothing  
inconsistent    shift + DBL_TAP      q     gives nothing  

info shift + non shiftable key (e.g. A(C(KC_E))) outputs shift+�=nothing instead of ignoring the shift, but ignoring the shift in general does not work either  
special � � � only mod shift neeeds to be passed through 
  
special dbl_tap_hold ESC sends ^ as non dead key see dance_esc_finished or use ahk combo ,q > ^  
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
    .,  > �  
    .n  > �  
    .l  > �  
    .-  > �  
    
    dot mix  
    ., > �  
    .- > �  
    ,a > �  
    ,s > �  
      
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
        �456-  
        3210.  
        /789,  
  
#### leader key idea:
always send KC_LEAD after ESC or up ? Does it work? Are there usecases?  
 
# Alternativ layout/typing ideas ... the past
instead of the autosymbol hold feature it may be faster to just activate the symbol layer (to type diacrits)
and use MT(shift, space) instead of homerow mod shift, but personaly I found autosymbol to be faster to learn and to TYPE
I tested this 
        LOWER > right symbols
        RAISE > left symbols
        SPACE > shift
but didn't like (because the thumb gets overworked) in cases like 
 * F� where the thumb has to be faster than the fingers to not became the bottleneck
 * � where you have to shift with the other thumb than usual 
idea 1: use classical shift keys, but these would force my whole hand outwards ~ half a key
idea 2: LOWER = RAISE > all symbols, allows to shift as normal but requires diacrits to be pressed one handed or two handed in respect to the preceding letter 
idea 3a: use homerow SHIFT only on the Symbol-Layer
idea 3b: use homerow SHIFT instead of thumb shift everywhere
idea 4: have OSL(SYM) and make sure Space/Shift does not clear the osl status
idea 5: tapdance diacrits on the OSL layer to get shifted versions

# Alternativ layout/typing ideas ... the future

## ideas
 * home-row-left-shift + RAISE/LOWER could switch to a different layer  
 * if dicrits conflict with home row mods like a/� and s/�  
   consider puttig a complete set of home row mods on the symbol layer (this means keep your symbol-layer-home-row free of symbols you want to tapdance on like LPARAN )

## (no) Autoshift
 * for me Autoshift required an awkward wait at the beginning of a word, but with additional training and more agressiv timings/customizations that might be a non issue
 * Autoshift and Home row mods don't work well together, because it feels wrong to have letters with exceptions to autoshift  
 * consider puttig a complete set of home row mods on the symbol layer (this means keep your symbol-layer-home-row free of symbols you want to tapdance on like LPARAN )
 * Autoshift requires additional customization for uncomfortable/slow letters
 * Autoshift forces diacrits to be mixed onto the symbol layer (or have an own layer)  
 * idea: COMBO-DIACRIT like KOMMA + a/s/d/f -> �/�/�/�
 * idea: Make an *OSL* DIACRIT-NUMBER-(MACRO) and FKEY-NAV layer instead of NAV-NUM and FKEY-MACRO  
 * idea: Make an *OSL* DIACRIT-FKEY-MACRO layer  

## (no) thumb shift
 * space-shift is the fastest and most error free shifting methode, but it will get in your way when combining with autoshift or homerow mods
   and even with other thumb layer keys  
 * using space-shift in conjunction with a thumb activated layer for diacrits gets into thumb overloading problems.
   Typing f�nf or f�r would require swaping the used thumb depending on the letter after '�' for max speed  
   (using alwas the same thumb might be more practical)
   
## no diacrits on extra layer
 * Pressing space and a key at the same time should favor layer activation (wich is what happens)..
 * Also timing for layer deactivation gets an issue  

# learnings
 * After having dealt with all the quirks of homerow SHIFT, its finally the way to go.  
   Using fastest timinig for Shift(index finger), fast timing for ctrl(middle finger) and much slower timings for other mods.
 * using auto diacrit with short timing feel more comfortable than hitting a separate layer key

# flatten the learning curve/simlify this keymap: (asume you have LOWER/RAISE keys)
 1. remove diacrits from the symbol layer to enforce/ease learning  
 2. optimize symbol layer to your likings
 3. only diacrits ����, interpunctuation ,.- and other tripple-symbol-keys like q->@  should be accessible by autosymbol single_hold.  
    That way learning tap vs hold is restricted to  much fewer keys
 3a. We may not need the whole SHIFT_HOLD system
 3b. Maybe we don't need the DBL_TAP_HOLD system either
 3c. Hold(Q) -> END and other options become possible againk 
 4. use symbol layer symbols only by activating the layer by a key(space)

# todos

 * using home row mod k as ALT is makes pressing mod combos difficult => move it to L
 * remove diacrits from the symbol layer
 * Hold(Q) -> END / Hold(esc) -> HOME
 * using autosymbol should make it pointless to bind SPACE_HOLD to Symbol-Layer - remember !�`'� - what else would be better?
 * SHIFT_HOLD s -> ''
 * map BSP DEL to layer buttons vv -> Enter  SHIFT_HOLD D -> TAB ,+d -># ,l ,+l->''
 * or SHIFT_HOLD v -> TAB 
 
combos?
, q -> !
, w -> '
, s -> '

