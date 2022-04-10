void rgb_matrix_indicators_user(void) {
        switch (biton32(layer_state) | biton32(default_layer_state)) {
        case 0:
        //_L0:
                rgb_matrix_set_color_all(0,1,10);
                rgb_matrix_set_color(34, 70, 10, 10); // cursor keys
                rgb_matrix_set_color(44, 70, 10, 10);
                rgb_matrix_set_color(45, 70, 10, 10);
                rgb_matrix_set_color(46, 70, 10, 10);
                break;
        case 1:
        //_GAME:
                rgb_matrix_set_color_all(0,1,10);
                
                rgb_matrix_set_color(2, 150, 150, 50); // wasd
                rgb_matrix_set_color(14, 150, 150, 50);
                rgb_matrix_set_color(15, 150, 150, 50);
                rgb_matrix_set_color(13, 150, 150, 50);
                
                rgb_matrix_set_color(34, 70, 10, 10); // cursor keys
                rgb_matrix_set_color(44, 70, 10, 10);
                rgb_matrix_set_color(45, 70, 10, 10);
                rgb_matrix_set_color(46, 70, 10, 10);
                break;
         case 2:        
        //_SWAP
                rgb_matrix_set_color_all(0,1,10);
                rgb_matrix_set_color(34, 70, 10, 10); // cursor keys
                rgb_matrix_set_color(44, 70, 10, 10);
                rgb_matrix_set_color(45, 70, 10, 10);
                rgb_matrix_set_color(46, 70, 10, 10);
                
                rgb_matrix_set_color(1, 150, 150, 50); // left keys
                rgb_matrix_set_color(2, 150, 150, 50);
                rgb_matrix_set_color(3, 150, 150, 50);
                rgb_matrix_set_color(4, 150, 150, 50);
                 rgb_matrix_set_color(5, 150, 150, 50);
                rgb_matrix_set_color(13, 150, 150, 50);
                rgb_matrix_set_color(14, 150, 150, 50);
                rgb_matrix_set_color(15, 150, 150, 50);
                rgb_matrix_set_color(16, 150, 150, 50);
                rgb_matrix_set_color(17, 150, 150, 50);
                rgb_matrix_set_color(25, 150, 150, 50);
                rgb_matrix_set_color(26, 150, 150, 50);
                rgb_matrix_set_color(27, 150, 150, 50);
                rgb_matrix_set_color(28, 150, 150, 50);
                 rgb_matrix_set_color(29, 150, 150, 50);
                break;
        case 3:
        //_LNAV:
        //      rgb_matrix_set_color_all(0,150,55); // all bright
                rgb_matrix_set_color_all(0,1,30); 
                rgb_matrix_set_color(4, 150, 150, 50); // num pad
                rgb_matrix_set_color(2, 150, 150, 50);
                rgb_matrix_set_color(3, 150, 150, 50);
                rgb_matrix_set_color(14, 150, 150, 50);
                rgb_matrix_set_color(15, 150, 150, 50);
                rgb_matrix_set_color(16, 150, 150, 50);
                rgb_matrix_set_color(17, 150, 150, 50);
                rgb_matrix_set_color(26, 150, 150, 50);
                rgb_matrix_set_color(27, 150, 150, 50);
                rgb_matrix_set_color(28, 150, 150, 50);
                rgb_matrix_set_color(8, 1, 150, 50); // i inline nav(\)'
                rgb_matrix_set_color(19, 1, 150, 50); // n
                rgb_matrix_set_color(20, 1, 150, 50); // t 
                rgb_matrix_set_color(21, 1, 150, 50); // l
                rgb_matrix_set_color(34, 100, 10, 10); // cursor keys
                rgb_matrix_set_color(44, 100, 10, 10);
                rgb_matrix_set_color(45, 100, 10, 10);
                rgb_matrix_set_color(46, 100, 10, 10);
                break;
        case 4:
        //_LSYM:
                rgb_matrix_set_color_all(0,1,60);
                rgb_matrix_set_color(13, 150, 150, 50); // ä
                rgb_matrix_set_color(14, 150, 150, 50); // ß
                rgb_matrix_set_color(7, 150, 150, 50); // ü
                rgb_matrix_set_color(9, 150, 150, 50); // ö
                rgb_matrix_set_color(34, 100, 10, 10); // cursor keys
                rgb_matrix_set_color(44, 100, 10, 10);
                rgb_matrix_set_color(45, 100, 10, 10);
                rgb_matrix_set_color(46, 100, 10, 10);
        break;
        case 5:
//        _L3:
                rgb_matrix_set_color_all(0,1,30);
                rgb_matrix_set_color(1, 150, 150, 50); // reset
                rgb_matrix_set_color(14, 150, 150, 50); // s
                rgb_matrix_set_color(15, 150, 150, 50); // d
                rgb_matrix_set_color(16, 150, 150, 50); // f
                rgb_matrix_set_color(8, 1, 150, 50); // i mouse
                rgb_matrix_set_color(19, 1, 150, 50); // n
                rgb_matrix_set_color(20, 1, 150, 50); // t 
                rgb_matrix_set_color(21, 1, 150, 50); // l
                rgb_matrix_set_color(8, 150, 150, 50); // nav
                rgb_matrix_set_color(19, 150, 150, 50); // nav
                rgb_matrix_set_color(20, 150, 150, 50); // nav
                rgb_matrix_set_color(21, 150, 150, 50); // nav
                break;
        case 6:
        //_L4:
                rgb_matrix_set_color_all(0,1,60);
                rgb_matrix_set_color(1, 150, 150, 50); // num pad
                rgb_matrix_set_color(2, 150, 150, 50);
                rgb_matrix_set_color(3, 150, 150, 50);
                rgb_matrix_set_color(4, 150, 150, 50);
                rgb_matrix_set_color(13, 150, 150, 50);
                rgb_matrix_set_color(14, 150, 150, 50);
                rgb_matrix_set_color(15, 150, 150, 50);
                rgb_matrix_set_color(16, 150, 150, 50);
                rgb_matrix_set_color(25, 150, 150, 50);
                rgb_matrix_set_color(26, 150, 150, 50);
                rgb_matrix_set_color(27, 150, 150, 50);
                rgb_matrix_set_color(28, 150, 150, 50);
                rgb_matrix_set_color(19, 150, 150, 50); // makro
                rgb_matrix_set_color(20, 150, 150, 50);
                rgb_matrix_set_color(21, 150, 150, 50);
                rgb_matrix_set_color(45, 50, 10, 10); // volume
                rgb_matrix_set_color(34, 50, 10, 10);
                break;
        }
}

void oneshot_locked_mods_changed_user(uint8_t mods) {
  //if (mods & MOD_MASK_SHIFT) {
  rgb_matrix_set_color_all(RGB_YELLOW);
  //}
//  if (!mods) {
//    println("Oneshot locked mods off");
//  }
}
