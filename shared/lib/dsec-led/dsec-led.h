/**
 * Name: Data Security LED control
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for abstract 'state' of a single LED
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-led.cpp
 * File description: dsec-led library
 */
#ifndef DSecLED_h
#define DSecLED_h

#include <Arduino.h>
#include <stdint.h>

//. @todo see .h and write this
// needs to do some interpolatioj thing
// also we need a notion of if the LEDs are changed / should be written to
// internally we use a 16 bit number for resolution w/o floating point
// set and get 8 bit number as is used by the STRIPS

class DSecLED {

	public:

		DSecLED();

		boolean getState();

		void setState(boolean state);
		void setState(boolean state, long onTime ); // how long to maintain this state ?

		// maybe we need setOn / setOff w/ delay ?  is that more clear ?

		/**
		 * Convenience storage to keep implementation simpler - which pin
		 * is this LED attached to?  Eg: digital PIN 4
		 */
		uint8_t getPin();

		/**
		* Convenience storage to keep implementation simpler - which pin
		* is this LED attached to?  Eg: digital PIN 4
		 */
		void setPin(uint8_t pin);

		/**
		 * call to see if a write to the LED is needed since the last
		 */
		boolean isChanged();

		/**
		 * Called once per loop - update 'current' state / changedness
		 */
		void update();

	private:

		// i think i may be overcomplicating this but basically we need a R/G/V change amount per MS and when things happened

		uint8_t _pin;

		// Is on / turn off or on
		boolean _state;
		boolean _lastState;
		boolean _targetState;

		// when was the last time we did stuff
		// when will targetState happen
		unsigned long _lastMS;
		unsigned long _targetMillis;

};

#endif // DSecLED_h
