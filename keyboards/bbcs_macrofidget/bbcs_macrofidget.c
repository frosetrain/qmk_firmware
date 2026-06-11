#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_kb(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_sethsv_noeeprom(0, 255, 255);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_RED_ORANGE_WAVE_WHITE_SPLASH);
    keyboard_post_init_user();
}
#endif
