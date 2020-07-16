#include "mocking-sponge.h"

void mocking_sponge_text( uint16_t keycode, bool uppercase ) {

  if ( uppercase ) {
    tap_code16( S( keycode ) );
  }
  else {
    tap_code( keycode );
  }

}