/**
 * Name: Data Security RGB led
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for abstract 'state' of a single RGB LED and animation
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-knob.cpp
 * File description: dsec-knob library
 */
#ifndef DSecRGBLED_h
#define DSecRGBLED_h

#include <Arduino.h>
#include <stdint.h>

//. @todo see .h and write this
// needs to do some interpolatioj thing
// also we need a notion of if the LEDs are changed / should be written to
// internally we use a 16 bit number for resolution w/o floating point
// set and get 8 bit number as is used by the STRIPS

class DSecRGBLED {

	public:

		DSecRGBLED();

		uint8_t getR();
		uint8_t getG();
		uint8_t getB();

		void setRGB( uint8_t R, uint8_t G, uint8_t B );
		void setRGB( uint8_t R, uint8_t G, uint8_t B, long rampTime );

		// Convert a number in range 0-65,536 to position in 0-255
		uint8_t to8bit(int16_t rangedValue);

		// Convert a number in range 0-255 to position in 0-32768 ?
		int16_t to16bit(uint8_t rangedValue);

		/**
		 * Convenience storage to keep implementation simpler - which number in
		 * a strip is this?  Eg: 4th LED in parent strip
		 */
		uint8_t getNumber();

		/**
		 * Convenience storage to keep implementation simpler - which number in
		 * a strip is this?  Eg: 4th LED in parent strip
		 */
		void setNumber(uint8_t number);

		/**
		 * call to see if a write to the LED is needed since the last
		 */
		boolean isChanged();

		/**
		 * if we are not interpolating a fade on an LED - the host must also check
		 * this method to see if an LED write is required on that cycle (eg: hard on / off)
		 */
		boolean receiveForceChange();

		/**
		 * Called once per loop - update 'current' state / changedness
		 */
		void update();

	private:

		// i think i may be overcomplicating this but basically we need a R/G/V change amount per MS and when things happened

		uint8_t _number;

		// These are the current values which will be returned (scaled down to 8bit)
		// -32768 to 32768
		int16_t _R;
		int16_t _G;
		int16_t _B;

		// the last value of R/G/B -- determine if a change is required ?
		int16_t _lastR;
		int16_t _lastG;
		int16_t _lastB;

		int16_t _targetR;
		int16_t _targetG;
		int16_t _targetB;

		int16_t _changeRMS;
		int16_t _changeGMS;
		int16_t _changeBMS;

		bool _forceChange;

		unsigned long _lastMS;
		unsigned long _targetMillis;

};

#endif // DSecRGBLED_h
