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

class DSecLED {

	public:

		DSecLED();

		boolean getState();

		void setState(boolean state); // jump to state immediately
		void setState(boolean state, long onTime ); // how long to maintain this state ?
		void setOn(long onTime ); // how long to maintain this state ?

		// void blink() // flash 4x quickly, default behavior
		// void blink(int times) // blink at default rate
		// void blink(int times, long duration) // blink at a particular rate
		// void blink(int times, long initialDuration, finalDuration) // ramped blink (eg: start fast to slow)

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

		// true = on / false = off
		boolean _state;

		// the state during the previous update() call
		boolean _lastState;

		// the desired state after _targetMillis is now or past
		boolean _targetState;

		// when was the last time update was called?
		unsigned long _lastMillis;

		// when will _state become _targetState ?
		unsigned long _targetMillis;

};

#endif // DSecLED_h
