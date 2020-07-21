#include "d4mation.h"

__attribute__ ((weak))
bool process_record_keymap( uint16_t keycode, keyrecord_t *record ) {
    /* If you want macros specific to your keymap, you need to define this function in your keymap */
    return true;
}

__attribute__ ((weak))
void matrix_init_keymap() {
    /* If you want a matrix init specific to your keymap, you need to define this function in your keymap */
}

__attribute__ ((weak))
void matrix_scan_keymap() {
    /* If you want a matrix scan specific to your keymap, you need to define this function in your keymap */
}

__attribute__((weak))
void eeconfig_init_keymap( void ) {}

/* process_record_user() is called in macros.c */

void matrix_init_user( void ) {
    matrix_init_keymap();
}

void matrix_scan_user( void ) {
    matrix_scan_keymap();
}

extern keymap_config_t keymap_config;
bool windows_mode = false;

void eeconfig_init_user( void ) {

    /* Initialize on boot so that we have the ability to know what the saved Swap CTRL/GUI state is */
    if ( CMD_WINDOWS_ENABLE && CMD_WINDOWS_DEFAULT_CTRL && ! keymap_config.swap_lctl_lgui ) {
        windows_mode = true;
    }
    else {
        windows_mode = false;
    }

    eeconfig_init_keymap();
    keyboard_init();

}