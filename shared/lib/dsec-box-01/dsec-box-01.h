/**
 * Name: Data Security BOX01 library
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for interfacing with a spooky box of wires
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-box01.h
 * File description: Definitions and methods for the dsec-box01 library
 */
#ifndef DSEC_BOX01_h
#define DSEC_BOX01_h

#include "dsec-singletoggle.h"
#include "dsec-dualtoggle.h"
#include "dsec-knob.h"
#include "dsec-rgbled.h"
#include "dsec-led.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <MIDI.h>
#include "MUX74HC4067.h"

// Class for interfacing the 74HC4067 multiplexers/demultiplexers
class DSecBox01
{
	public:

		/**
		 * Indicator RGB LEDs
		 */
		DSecRGBLED seqLEDs[8];
		DSecRGBLED topLEDs[2];

		/**
		 * On/Off button LEDs
		 */
		DSecLED    buttonLEDs[4];

		// One toggle up top right
		DSecDualToggle topToggle;

		// 8 toggles left to right
		DSecDualToggle mainToggles[8];// = DSecDualToggle();

		// 4 buttons along the bottom
		DSecSingleToggle buttons[4];

		// 4 knobs along the bottom by the buttons
		DSecKnob knobs[4];

		// MUX!
		MUX74HC4067 mux(7, 6, 5, 4, 3);
		// Set SIG Pin from MUX74HC4067
		//

		/**
		 * Call this to initialize the whole deal
		 * @todo maybe have a long ass string of numbers representing every pin ?????????? or better idea how about a couple of grouped arrays of pins
		 */
		void setup();
		void loop();

	private:
		/**
		 * Anything interally used which should never be called externally ?
		 */
		void readInterfaceState();
		void readMidi();
		void updateDisplay();
		void sendMidi();

};

#endif  // MUX74HC4067
