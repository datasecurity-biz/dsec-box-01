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
#ifndef DSEC_DUALTOGGLE_h
#define DSEC_DUALTOGGLE_h

#include <Arduino.h>

// some day do dsec-momentary dsec-toggle

#define ANALOG 0
#define DIGITAL 1

#define DISABLED 0
#define ENABLED 1

// Class for interfacing the 74HC4067 multiplexers/demultiplexers
class DSecDualToggle
{
	public:
		DSecDualToggle(uint8_t pinUp, uint8_t pinDown);
			void loop();

	private:
		/**
		 * Toggle states
		 *  1: - currently held up
		 *  0: - off
		 * -1: - currently held down
		 */
		int8_t toggleState;
		int8_t pinUp;
		int8_t pinDown;
};

#endif  // MUX74HC4067
