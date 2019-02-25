/**
 * Name: Data Security DUALTOGGLE control
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for interfacing with a two way momentary toggle switch
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-dualtoggle.h
 * File description: Definitions and methods for the dsec-dualtoggle library
 */
#ifndef DSecDualToggle_h
#define DSecDualToggle_h

#include <Arduino.h>

class DSecDualToggle {

	public:

		DSecDualToggle();

		void    setUpState(uint8_t newState);
		void    setDownState(uint8_t newState);
		void    setUpPin(uint8_t pin);
		void    setDownPin(uint8_t pin);

		uint8_t getUpPin();
		uint8_t getDownPin();
		int8_t  getState();

		static int8_t UP;
		static int8_t OFF;
		static int8_t DOWN;

		// void setStateChangedHandler(); // stateChangedHandler(int newState)
		// ^ note to self: http://www.gammon.com.au/callbacks -- need to figure this thingie out

	private:
		/**
		 * Toggle states
		 * .UP   ->  1: - currently held up
		 * .OFF  ->  0: - off
		 * .DOWN -> -1: - currently held down
		 */
		int8_t _upState;
		int8_t _downState;
		int8_t _previousUpState;
		int8_t _previousDownState;

		unsigned long _lastChangedUpStateMS; // last millis read time for debounce
		unsigned long _lastChangedDownStateMS; // last millis read time for debounce

		uint8_t _upPin;
		uint8_t _downPin;

};

#endif  // DSecDualToggle_h
