#pragma once

#include "quantum.h"
#include "tap-hold.h"
#include "zalgo.h"
#include "mocking-sponge.h"
#include "print.h"

#define SCRGB LCTL( LSFT( LGUI( KC_4 ) ) ) /* Mac Screen Area Grab shortcut (Puts into Clipboard) */
#define SLEEP LALT( LGUI( KC_SYSTEM_POWER ) ) /* Instant sleep on Mac, rather than having to hold down the button */

enum custom_keycodes {
  _GRAVE_ESC = SAFE_RANGE, /* Prefixed with underscore to prevent conflicts */
  PHPOPEN, /* <?php */
  PHPCLSE, /* ?> */
  AMENO, 
  MAGIC,
  LENNY,
  DISFACE,
  TFLIP,
  TPUT,
  SHRUG,
  ZALGO,
  SPONGE,
  NEW_SAFE_RANGE
};

bool after_windows_mode( uint16_t keycode, keyrecord_t *record );