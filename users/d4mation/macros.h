#pragma once

#include "quantum.h"
#include "tap-hold.h"
#include "zalgo.h"
#include "mocking-sponge.h"
#include "print.h"

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
  SLEEP,
  SCGRB,
  NEW_SAFE_RANGE
};

bool after_windows_cmd_overlay( uint16_t keycode, keyrecord_t *record );