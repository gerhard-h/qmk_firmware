void rgb_matrix_indicators_user(void) {
        switch (biton32(layer_state)) {
        case 0:
                rgb_matrix_set_color_all(0,1,10);
                rgb_matrix_set_color(34, 70, 10, 10); // cursor keys
                rgb_matrix_set_color(44, 70, 10, 10);
                rgb_matrix_set_color(45, 70, 10, 10);
                rgb_matrix_set_color(46, 70, 10, 10);
                break;
        case 1:
        //      rgb_matrix_set_color_all(0,150,55); // all bright
                rgb_matrix_set_color_all(0,1,30); 
                rgb_matrix_set_color(1, 150, 150, 50); // num pad
                rgb_matrix_set_color(2, 150, 150, 50);
                rgb_matrix_set_color(3, 150, 150, 50);
                rgb_matrix_set_color(13, 150, 150, 50);
                rgb_matrix_set_color(14, 150, 150, 50);
                rgb_matrix_set_color(15, 150, 150, 50);
                rgb_matrix_set_color(25, 150, 150, 50);
                rgb_matrix_set_color(26, 150, 150, 50);
                rgb_matrix_set_color(27, 150, 150, 50);
                rgb_matrix_set_color(38, 150, 150, 50);
                rgb_matrix_set_color(7, 1, 150, 50); // ue
                rgb_matrix_set_color(9, 1, 150, 50); // oe
                rgb_matrix_set_color(21, 1, 150, 50); // 1
                rgb_matrix_set_color(33, 1, 150, 50); // 1
                rgb_matrix_set_color(34, 100, 10, 10); // cursor keys
                rgb_matrix_set_color(44, 100, 10, 10);
                rgb_matrix_set_color(45, 100, 10, 10);
                rgb_matrix_set_color(46, 100, 10, 10);
                break;
        case 2:
                rgb_matrix_set_color_all(0,1,60);
                rgb_matrix_set_color(13, 150, 150, 50); // ä
                rgb_matrix_set_color(14, 150, 150, 50); // ß
                rgb_matrix_set_color(8, 150, 150, 50); // nav
                rgb_matrix_set_color(19, 150, 150, 50); // nav
                rgb_matrix_set_color(20, 150, 150, 50); // nav
                rgb_matrix_set_color(21, 150, 150, 50); // nav
                rgb_matrix_set_color(30, 150, 150, 50); // esc
                rgb_matrix_set_color(34, 100, 10, 10); // cursor keys
                rgb_matrix_set_color(44, 100, 10, 10);
                rgb_matrix_set_color(45, 100, 10, 10);
                rgb_matrix_set_color(46, 100, 10, 10);
        break;
        case 3:
                rgb_matrix_set_color_all(0,1,30);
                rgb_matrix_set_color(1, 150, 150, 50); // reset
                rgb_matrix_set_color(8, 150, 150, 50); // I I I
                rgb_matrix_set_color(20, 150, 150, 50);
                rgb_matrix_set_color(32, 150, 150, 50);
                rgb_matrix_set_color(6, 150, 150, 50);
                rgb_matrix_set_color(18, 150, 150, 50);
                rgb_matrix_set_color(30, 150, 150, 50);
                rgb_matrix_set_color(4, 150, 150, 50);
                rgb_matrix_set_color(16, 150, 150, 50);
                rgb_matrix_set_color(28, 150, 150, 50);
                rgb_matrix_set_color(8, 150, 150, 50); // nav
                rgb_matrix_set_color(19, 150, 150, 50); // nav
                rgb_matrix_set_color(20, 150, 150, 50); // nav
                rgb_matrix_set_color(21, 150, 150, 50); // nav
                break;
        case 4:
                rgb_matrix_set_color_all(0,1,60);
                rgb_matrix_set_color(1, 150, 150, 50); // num pad
                rgb_matrix_set_color(2, 150, 150, 50);
                rgb_matrix_set_color(3, 150, 150, 50);
                rgb_matrix_set_color(13, 150, 150, 50);
                rgb_matrix_set_color(14, 150, 150, 50);
                rgb_matrix_set_color(15, 150, 150, 50);
                rgb_matrix_set_color(25, 150, 150, 50);
                rgb_matrix_set_color(26, 150, 150, 50);
                rgb_matrix_set_color(27, 150, 150, 50);
                rgb_matrix_set_color(38, 150, 150, 50);
                rgb_matrix_set_color(19, 150, 150, 50); // makro
                rgb_matrix_set_color(20, 150, 150, 50);
                rgb_matrix_set_color(21, 150, 150, 50);
                rgb_matrix_set_color(7, 150, 150, 50);
                rgb_matrix_set_color(9, 150, 150, 50);
                rgb_matrix_set_color(33, 150, 150, 50);
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
