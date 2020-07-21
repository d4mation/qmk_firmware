#include "d4mation.h"
#include "tap-hold.h"
#include "zalgo.h"
#include "mocking-sponge.h"
#include "macros.h"

bool zalgo_enabled = false;
bool mocking_sponge_enabled = false;
bool mocking_sponge_uppercase = false;

extern bool windows_cmd_overlay;
extern bool windows_mode;

bool ctrl_pressed = false;
bool gui_pressed = false;
bool shift_pressed = false;

bool ctrl_to_alt = false;
bool gui_to_ctrl = false;
bool ctrl_f5 = false;

bool ctrl_and_any_key = false;
bool gui_and_any_key = false;

bool process_record_user( uint16_t keycode, keyrecord_t *record ) {

  switch ( keycode ) {

    case CG_SWAP:

      if ( record->event.pressed ) {

        if ( WINDOWS_LAYOUT_IS_DEFAULT ) {
          windows_mode = false;
        }
        else {
          windows_mode = true;
        }

      }

      if ( ! CMD_WINDOWS_ENABLE ) return true;

      if ( record->event.pressed ) {

        /** This helps ensure that the saved state of the keyboard is taken into account */
        if ( CMD_WINDOWS_DEFAULT_CTRL ) {
          windows_cmd_overlay = false;
        }
        else {
          windows_cmd_overlay = true;
        }

      }

      return true;
      break;

    case CG_NORM:

      if ( record->event.pressed ) {

        if ( WINDOWS_LAYOUT_IS_DEFAULT ) {
          windows_mode = true;
        }
        else {
          windows_mode = false;
        }

      }

      if ( ! CMD_WINDOWS_ENABLE ) return true;

      if ( record->event.pressed ) {

        if ( CMD_WINDOWS_DEFAULT_CTRL ) {
          windows_cmd_overlay = true;
        }
        else {
          windows_cmd_overlay = false;
        }

      }

      return true;
      break;

    case TD(SHIFT_CAPS):
    case KC_LSHIFT:

      if ( ! windows_cmd_overlay ) return true;

      shift_pressed = record->event.pressed;

      // We do output Shift each time
      return true;
      break;

    case KC_LCTRL:

      if ( ! windows_cmd_overlay ) return true;

      ctrl_pressed = record->event.pressed;

      /* On keyup, either restore normal functionality or remove the held key */
      if ( ! record->event.pressed ) {
        
        if ( ctrl_to_alt ) {
          unregister_code( KC_RALT );
          ctrl_to_alt = false;
          return false;
        }
        else if ( ctrl_f5 ) {
          tap_code16( C( KC_F5 ) );
          ctrl_f5 = false;
          return false;
        }
        else if ( ctrl_and_any_key ) {
          unregister_code( KC_LCTRL );
          ctrl_and_any_key = false;
          return false;
        }
        else if ( ! ctrl_to_alt ) {
          tap_code( KC_LCTRL );
          return false;
        }

      }

      /* Do not output CTRL. This interferes with our remapped command by sending it and CTRL. If CTRL should be output, it will be done via after_windows_cmd_overlay() */
      return false;
      break;

    case KC_LGUI:

      if ( ! windows_cmd_overlay ) return true;

      gui_pressed = record->event.pressed;

      /* On keyup, either restore normal functionality or remove the held key */
      if ( ! record->event.pressed ) {
        
        if ( gui_to_ctrl ) {
          unregister_code( KC_RCTRL );
          gui_to_ctrl = false;
          return false;
        }
        else if ( gui_and_any_key ) {
          unregister_code( KC_LGUI );
          gui_and_any_key = false;
          return false;
        }
        else if ( ! gui_to_ctrl ) {
          tap_code( KC_LGUI );
          return false;
        }

      }

      /* Do not output GUI. This interferes with our remapped command by sending it and GUI. If GUI should be output, it will be done via after_windows_cmd_overlay() */
      return false;
      break;

    case KC_TAB:

      if ( ! windows_cmd_overlay ) return true;

      /* Tab Keydown */
      if ( record->event.pressed ) {

        if ( ctrl_pressed ) {

          ctrl_to_alt = true;

          /* Hold Alt */
          register_code( KC_RALT );

        }

        if ( gui_pressed ) {

          gui_to_ctrl = true;

          /* Hold CTRL */
          register_code( KC_RCTRL );

        }

      }

      return true;
      break;

    case KC_R:

      if ( ! windows_cmd_overlay ) return true;

      if ( record->event.pressed ) {

        if ( ctrl_pressed && shift_pressed ) {

          ctrl_f5 = true;
          unregister_code( KC_LSHIFT );
          return false;

        }

      }

      return true;
      break;

    case SLEEP:

      if ( windows_mode ) {
        tap_code16( G( KC_L ) );
      }
      else {
        tap_code16( LALT( LGUI( KC_SYSTEM_POWER ) ) ); /* Instant sleep on Mac, rather than having to hold down the button */
      }

      return false;

    case SCGRB: 

      if ( windows_mode ) {
        tap_code16( G( S( KC_S ) ) ); /* New Windows 10 screen grab tool */
      }
      else {
        tap_code16( LCTL( LSFT( LGUI( KC_4 ) ) ) ); /* Mac Screen Area Grab shortcut (Puts into Clipboard) */
      }

      return false;

    case _GRAVE_ESC:

      /* Send ` on Tap, Esc on Hold */
      tap_or_hold( record, KC_GRAVE, KC_ESC );

      if ( windows_cmd_overlay ) after_windows_cmd_overlay( keycode, record );

      return false;
      break;

    case PHPOPEN:

      if ( record->event.pressed ) {

        tap_code16( S( KC_COMMA ) );
        tap_code16( S( KC_SLASH ) );

        tap_code( KC_P );
        tap_code( KC_H );
        tap_code( KC_P );

      }

      return false;
      break;

    case PHPCLSE:

      if ( record->event.pressed ) {
        tap_code16( S( KC_SLASH ) );
        tap_code16( S( KC_DOT ) );
      }

      return false;
      break;

    #ifdef UNICODE_ENABLE

      case AMENO:  /* ༼ つ ◕_◕ ༽つ */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "0F3C 0020 3064 0020 25D5 005F 25D5 0020 0F3D 3064" );

        }

        return false;
        break;

      case MAGIC:  /* (∩ ͡° ͜ʖ ͡°)⊃━☆ﾟ. * */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "0028 2229 0020 0361 00B0 0020 035C 0296 0020 0361 00B0 0029 2283 2501 2606 FF9F 002E 0020 002A" );

        }

        return false;
        break;

      case LENNY:  /* ( ͡° ͜ʖ ͡°) */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "0028 0020 0361 00B0 0020 035C 0296 0020 0361 00b0 0029" );

        }

        return false;
        break;

      case DISFACE:  /* ಠ_ಠ */

        if ( record->event.pressed ) {
          send_unicode_hex_string( "0CA0 005F 0CA0" );
        }

        return false;
        break;

      case TFLIP:  /* (╯°□°)╯ ︵ ┻━┻ */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "0028 256F 00b0 25A1 00B0 0029 256F FE35 253B 2501 253B" );

        }

        return false;
        break;

      case TPUT:  /* ┬──┬ ノ( ゜-゜ノ) */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "252C 2500 2500 252C 0020 30CE 0028 0020 309C 002D 309C 30CE 0029" );

        }

        return false;
        break;

      case SHRUG:  /* ¯\_(ツ)_/¯ */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "00AF 005C 005F 0028 30C4 0029 005F 002F 00AF" );

        }

        return false;
        break;

      case ZALGO:  /* Toggles Zalgo Text mode */

        if ( record->event.pressed ) {
          zalgo_enabled = ! zalgo_enabled;
        }

        return false;
        break;

    #endif

    case SPONGE: /* Toggles mOcKiNg sPoNgE mode */

      if ( record->event.pressed ) {
        mocking_sponge_enabled = ! mocking_sponge_enabled;
        /* Ensure we reset to lowercase */
        mocking_sponge_uppercase = false;
      }

      return false;
      break;

    default:

      #ifdef UNICODE_ENABLE

        if ( zalgo_enabled ) {

          if ( keycode < KC_A || ( keycode > KC_0 && keycode < KC_MINUS ) || keycode > KC_SLASH ) {
            process_record_keymap( keycode, record );
            return true;
          }

          if ( record->event.pressed ) {
            zalgo_text( keycode );
          }

          return false;
        }

      #endif

      if ( mocking_sponge_enabled ) {

        if ( keycode < KC_A || keycode > KC_Z ) {

          /* On Spaces, revert to lowercase */
          if ( keycode == KC_SPACE ) {
            mocking_sponge_uppercase = false;
          }

          process_record_keymap( keycode, record );
          return true;

        }

        if ( record->event.pressed ) {
          mocking_sponge_text( keycode, mocking_sponge_uppercase );
          mocking_sponge_uppercase = ! mocking_sponge_uppercase;
        }

        return false;

      }

      break;

  }

  if ( windows_cmd_overlay ) after_windows_cmd_overlay( keycode, record );

  process_record_keymap( keycode, record );
  return true;

};

bool after_windows_cmd_overlay( uint16_t keycode, keyrecord_t *record ) {

  if ( ctrl_pressed ) {

    if ( keycode == KC_LCTRL ) return false;

    if ( record->event.pressed ) {

      /* Hold CTRL */
      register_code( KC_LCTRL );

      register_code( keycode );

      /* Let CTRL Keyup know to release it */
      ctrl_and_any_key = true;

    }
    else {
      unregister_code( keycode );
    }

    return true;

  }

  if ( gui_pressed ) {

    if ( keycode == KC_LGUI ) return false;

    if ( record->event.pressed ) {

      /* Hold GUI */
      register_code( KC_LGUI );

      register_code( keycode );

      /* Let GUI Keyup know to release it */
      gui_and_any_key = true;

    }
    else {
      unregister_code( keycode );
    }

    return true;

  }

  return true;

};