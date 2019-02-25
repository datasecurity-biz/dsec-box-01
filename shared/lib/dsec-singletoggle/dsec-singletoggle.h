/**
 * Name: Data Security SINGLETOGGLE control (BUTTON / SPST switch)
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for interfacing with a one way momentary toggle switch or button
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-singletoggle.h
 * File description: dsec-singletoggle library
 */
#ifndef DSecSingleToggle_h
#define DSecSingleToggle_h

#include <Arduino.h>

class DSecSingleToggle {

	public:

		DSecSingleToggle();

		void    setState(uint8_t newState);
		void    setPin(uint8_t pin);

		int8_t  getState();
		uint8_t getPin();

		static int8_t ON;
		static int8_t OFF;

		// void setStateChangedHandler(); // stateChangedHandler(int newState)
		// ^ note to self: http://www.gammon.com.au/callbacks -- need to figure this thingie out

	private:
		/**
		 * Toggle states
		 * .ON   ->  1: - currently pressed / toggled
		 * .OFF  ->  0: - off
		 */
		int8_t _state;
		int8_t _previousState;

		unsigned long _lastChangedStateMS; // last millis read time for debounce

		uint8_t _pin;

};

#endif  // DSecSingleToggle_h
