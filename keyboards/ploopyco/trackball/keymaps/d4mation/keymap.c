/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN4, KC_BTN5 ),
    [1] = LAYOUT( _______, _______, _______, _______, _______ ),
    [2] = LAYOUT( _______, _______, _______, _______, _______ ),
    [3] = LAYOUT( _______, _______, _______, _______, _______ ),
    [4] = LAYOUT( _______, _______, _______, _______, _______ ),
    [5] = LAYOUT( _______, _______, _______, _______, _______ ),
    [6] = LAYOUT( _______, _______, _______, _______, _______ ),
    [7] = LAYOUT( _______, _______, _______, _______, _______ )
};

extern bool is_drag_scroll;

void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {

    mouse_report->x = x;
    mouse_report->y = y;

    if ( is_drag_scroll ) {

        // pointing_device_task() in trackball.c will take these and set them correctly
        mouse_report->y = - y;

    }

}

void process_wheel_user(report_mouse_t* mouse_report, int16_t h, int16_t v) {

    uint16_t p1 = adc_read(OPT_ENC1_MUX);
    uint16_t p2 = adc_read(OPT_ENC2_MUX);

    uint8_t dir = opt_encoder_handler(p1, p2);

    int8_t scalar_factor = round((float) dir * PLOOPY_SCROLLWHEEL_MULTIPLIER);

    mouse_report->h = h;
    mouse_report->v = (int)(v + scalar_factor);

}