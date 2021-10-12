# an autosymbol keymap for bm40hsrgb
similar to autoshift uses key_hold to produce an alternativ key
for use with German keyboard layout 

features:
VIA
tap dance
custom keycodes 
rgb per layer

todo Holding Numbers for F key is suboptimal: own Layer activated by L1/L2+L4, L1/L4+V, L4+O  

info tapdance usage before custom   
 23 x hold (autosymbol),  
 11 x hold+dbltap,  
  3 x hold+dbltap+dblhold,  
  5 x hold+dblhold (autoclose),  
6(4)x hold (autoclose),  
  2 x mod_tap emulation with shifted keycode,  
  2 x mod_tap emulation with extra double tap,  
***********************************************
 52(50) keys pysical keys 47  

backtick \` is only available as Shift(tick) on L2  or ahk ,y  

info # $ () ~ are only available on L1, L2 or per double taps  

info [ and { are not working in windows terminal when done as CTL(ALT()) always use ALGR()  

(bug) shift + backspace > delete not working (sends SFT(KC_DEL))  

info h and u will not use dbl_tap to allow words like: Auufer, Buchhalter, nachher,...   

info slash / was the most inconvinient frequent symbol: idea 1: remap h=/ p=? --hold=~ 

info tap and single-hold for r p j b t s d f g h  is not realized by tap dance, but in matrix_scan_user and process_record_user because of tap_dance array overflows d,f,t are now used for home row mods
info some numbers 1234__7891 could also get a custom solution with different modifier handling 
info äüö behave similar to these numbers
info DBL_TAP_HOLD is handled as SINGLE_TAP if modifiers are active SHIFT + r_hold > R instead of S(])
info DBL_TAP_HOLD is autocorreted to bb pp rr tt  instead of b+ p~ r] t)
info AHK does aä > ä ... autocorrection

TAP Dance Problems/Inconsistencies
DBL_TAP_HOLD m has autorepeat **** but DBL_TAP_HOLD * has no autorepeat
@ only per dbl_tap q
DBL_TAP_HOLD bsp has autorepeat
shift + SINGLE_HOLD n > (  vs N - not an issue if N~SFT
shift + DBL_TAP KOMMA > gives S(<) = > instead of < (maybe correct)
BUT shift + SINGLE_HOLD i > I, shift + DBL_HOLD i > /
dbl_tap i > / unecessary revert to ii
Ä Ü Ö  works only shift neeeds to be passed through
shift + SINGLE_HOLD . > : correct DBL_TAP_HOLD > correct
shift + SINGLE_HOLD - > _ correct DBL_TAP_HOLD / correct
F10-12 only on L4 not L1 hold r = F10 instead of DELETE/€, F11 instead of 0  is sometimes confusing
dbl_tap_hold ESC sends ^ as dead key (instead of custom key CIRCUMFL) dance_dbltap_ could check "is keycode element of enum custom_keycodes?" than call that code
or put it on q @ ^

info ESC/Home BSP/End needs all mods passed through 

info _each and _reset funtions are often the same and therefore shared between declarations

todo light_control if OSM(modifier) is locked
todo light intensity controls are inactive -> search solution in oryx keymap code

info shift + non shiftable key (e.g. A(C(KC_E))) outputs shift+€=nothing instead of ignoring the shift, but ignoring the shift in general does not work either
  

bug dance_mod_finished mods must be pressed one after the other 
else first key registers a tap instead of hold
> workaround swap + and | because + is a not shifted key wich could use MT

(bug) modifier_dbldance_finished when interupted outputs the modifier instead of key (only with ALT). workaround: use MT 

bug tap dance inside OSL only works if OSL key is held down | process_record_user  all OSM set status-flag on down and clear status-flag on up 
if tap_dance_each senses !status-flag & OSL active: OSL clear, permanent layer move...
...tap dance continues ... on tapdance reset layer move 0
  

COMBOS - are there use cases? do combos conflict with tap dance ... yes they do but autohotkey can be used
combo starters: ,<alpha> q<alpha_minus_ulm> jf cv vc vz vd jz wt wd wf wz tricky: .<alpha> uu ii uv 
c + L1 > enter
qw = esc better than tapdance qq? ,k > # 
comma - combos ,q > 1 ,w > 2 ... ,. >  ,- > 
,esc > F1 ,q > F2 ,bsp > F12 
comma diacrit opposit ,a > ä ,s > ß ,d > ö ,f > ü
G = LT(1,KC_G)  H = LT(1,KC_H) 
dot diacrit ., > ä .n > ü .l > ö .- > ß/alt
dot mix ., > ü .- > ö. ,. .. ä ,- > ß

speed test: räte käfig Räte Käfig düfte Düfte röhre Röhre
comma           a       o       u
thumb layer     a       o       u
hold 150ms      a       o       u
dot                     ,       -

;autohotkey QMK compatibility
;SP seemed not to work at all use(default) #Hotstring SI  or #Hotstring SE
;problems if the final chracter of a hotstring 
; a) has modifiers (these are not always released)
; b) is the result of tapdance or onhold feature
; c) is on a different layer
;qmk has additional problems with notepad++ and {Enter} 
;solution 1: try a raw ()-block  use space before CRLF (only usefull if the final character does not obey the rules a-c )
;solution 2: exsample Send Mit freundlichen Grüßen {Enter} - space before {enter}  and text on the same line  as Enters

(re)evaluate home row mods? F, N ~ SFT ... D, T ~ CTL ... G, H ~ L2/L1
  

reevaluate u h have will have no dbltap enabling:  Auufer Buchhalter nachher
reevaluate copy paste undo: xx cc vv zz
-reevaluate alt-tab: kk vs L2z ->. removed kk in favor of MT()
reevaluate alt-shift-tab: L2p
reevaluate 1=v on numpad1
reevaluate del key positioin RSFT L2DOT L1R LALT ,r
reevaluate q > END qq > @
*
feature idea: single key alt tab {KC_LCTL,KC_LALT,KC_TAB}
single hold & modus==OFF: alt + ctrl + tab & modus=ON 
tap & modus==ON: tab
single hold & modus==ON: modus==ON & Space  
      
Alt+F4: Ctl+(W+W) or (C+W)+W or C+(W+Q) or wq currenly L4 + K + A
*
*numberpad 2.0
€456-
3210.
/789,
*
leader key  combos? are they compatible with tapdance keys? F keys
always send KC_LEAD after ESC or up ?
*

