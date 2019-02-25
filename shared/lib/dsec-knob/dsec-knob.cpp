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
#ifndef DSecKnob_cpp
#define DSecKnob_cpp

#include <dsec-knob.h>

DSecKnob::DSecKnob() {

	// delay(10);
	// DSecVoltage voltage = DSecVoltage();
	// long result = voltage.read();
	// USB is ~ 563200   5.6 / ?

	// find max based on returned voltage
	// if (result > 0)
	_maxValue = 893;

}

uint8_t DSecKnob::getPin() {
	return _pin;
}

void DSecKnob::setPin(uint8_t pin) {
	_pin = pin;
}

uint16_t DSecKnob::getValue() {
	return _value;
}

/**
 * Get the "position" of the knob, from furthest to the left 0
 * to all the way up, at 1.  If out of range, return the expected min or max
 * 0 or 1
 */
float DSecKnob::getPosition() {
	float posValue = (float) _value / (float) _maxValue;
	// if (posValue > 1)
	// 	return 1;
	// else if (posValue < 0)
	// 	return 0;
	// else return posValue;
	return posValue;
}

void DSecKnob::setValue(uint16_t value) {

	// debounce here
	if (_value != value) {
		_value = value;
		_lastValue = _value;
		_lastChangedStateMS = millis();
	}

};

void DSecKnob::setMaxValue(uint16_t maxValue) {
	_maxValue = maxValue;
}

#endif // DSecKnob_cpp
