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

/* Whether to remap specific modifiers based on context */
bool windows_cmd_overlay = false;

/* Whether we should be sending Windows-based Macros */
bool windows_mode = false;

void eeconfig_init_user( void ) {

    /* Initialize on boot so that we have the ability to know what the saved Swap CTRL/GUI state is */
    if ( CMD_WINDOWS_ENABLE && CMD_WINDOWS_DEFAULT_CTRL && ! keymap_config.swap_lctl_lgui ) {
        windows_cmd_overlay = true;
    }
    else {
        windows_cmd_overlay = false;
    }

    /* Set Windows Mode for the couple Macros that are not tied to CTRL/GUI/Shift states */
    if ( WINDOWS_LAYOUT_IS_DEFAULT && ! keymap_config.swap_lctl_lgui ) {
        windows_mode = true;
    }

    /* Set the Unicode Input mode */
    #ifdef UNICODE_ENABLE
        if ( windows_mode ) {
            set_unicode_input_mode( UC_WINC );
        }
        else {
            set_unicode_input_mode( UC_OSX );
        }
    #endif

    eeconfig_init_keymap();
    keyboard_init();

}