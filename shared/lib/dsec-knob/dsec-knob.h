/**
 * Name: Data Security KNOB control
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for interfacing with a single potentiometer
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-knob.cpp
 * File description: dsec-knob library
 */
#ifndef DSecKnob_h
#define DSecKnob_h

#include <Arduino.h>
#include <dsec-voltage.h>

class DSecKnob {

	public:

		DSecKnob();

		uint8_t getPin();
		void setPin(uint8_t pin);

		/**
		 * Get the raw value read from the pin
		 */
		uint16_t getValue();

		/**
		 * Get knob position from 0-1
		 */
		float getPosition();

		/**
		 * Set the raw value read from the pin
		 */
		void setValue(uint16_t value);

		/**
		 * Set the maximum expected value of the pin - used to return
		 */
		void setMaxValue(uint16_t maxValue);

	private:

		uint8_t _pin;
		uint16_t _value;
		uint16_t _maxValue;
		uint16_t _lastValue;
		long _lastChangedStateMS;

};

#endif  // DSecKnob_h
