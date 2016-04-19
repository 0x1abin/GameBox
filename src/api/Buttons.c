/*
 * (C) Copyright 2014 Aurélien Rodot. All rights reserved.
 *
 * This file is part of the Gamebuino Library (http://gamebuino.com)
 *
 * The Gamebuino Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "Buttons.h"

typedef enum
{
  BTN_LEFT = 0,  //!< KEY01
  BTN_UP,        //!< KEY02
  BTN_RIGHT,     //!< KEY03
  BTN_DOWN,      //!< KEY04
  BTN_A,         //!< KEY05
  BTN_B,         //!< KEY06
  NUM_BTN        //!< NUMBER_OF_KEYS
}BTN_NAME_T;

static uint8_t pins[NUMBER_OF_KEYS];
static uint8_t states[NUMBER_OF_KEYS];

void Buttons_Init() {
    pins[BTN_LEFT]  = BTN_LEFT_PIN;
    pins[BTN_UP]    = BTN_UP_PIN;
    pins[BTN_RIGHT] = BTN_RIGHT_PIN;
    pins[BTN_DOWN]  = BTN_DOWN_PIN;
    pins[BTN_A]     = BTN_A_PIN;
    pins[BTN_B]     = BTN_B_PIN;

    states[BTN_LEFT] = 0;
    states[BTN_UP] = 0;
    states[BTN_RIGHT] = 0;
    states[BTN_DOWN] = 0;
    states[BTN_A] = 0;
    states[BTN_B] = 0;
    states[BTN_C] = 0;
}

/*
 * reads each button states and store it
 */
void Buttons_update() {
    for (uint8_t thisButton = 0; thisButton < NUM_BTN; thisButton++) {
        pinMode(pins[thisButton], INPUT_PULLUP); //enable internal pull up resistors
        if (digitalRead(pins[thisButton]) == LOW) { //if button pressed
            states[thisButton]++; //increase button hold time
        } else {
            if (states[thisButton] == 0)//button idle
                continue;
            if (states[thisButton] == 0xFF)//if previously released
                states[thisButton] = 0; //set to idle
            else
                states[thisButton] = 0xFF; //button just released
        }
        pinMode(pins[thisButton], INPUT); //disable internal pull up resistors to save power
    }
	

}

/*
 * Returns true when 'button' is pressed.
 * The button has to be released for it to be triggered again.
 */
boolean Buttons_pressed(uint8_t button) {
    if (states[button] == 1)
        return true;
    else
        return false;
}

/*
 * return true if 'button' is released
 */
boolean Buttons_released(uint8_t button) {
    if (states[button] == 0xFF)
        return true;
    else
        return false;
}

/**
 * returns true ONCE when 'button' is held for 'time' frames
 * @param button The button's ID
 * @param time How much frames button must be held, between 1 and 254.
 * @return true when 'button' is held for 'time' frames
 */
boolean Buttons_held(uint8_t button, uint8_t time){
    if(states[button] == (time+1))
        return true;
    else
        return false;
}

/**
 * returns true every 'period' frames when 'button' is held
 * @param button The button's ID
 * @param period How much frames button must be held, between 1 and 254.
 * @return true if the button is held for the given time
 */
boolean Buttons_repeat(uint8_t button, uint8_t period) {
    if (period <= 1) {
        if ((states[button] != 0xFF) && (states[button]))
            return true;
    } else {
        if ((states[button] != 0xFF) && ((states[button] % period) == 1))
            return true;
    }
    return false;
}

/**
 * 
 * @param button The button's ID
 * @return The number of frames during which the button has been held.
 */
uint8_t Buttons_timeHeld(uint8_t button){
    if(states[button] != 0xFF)
        return states[button];
    else
        return 0;
    
}
