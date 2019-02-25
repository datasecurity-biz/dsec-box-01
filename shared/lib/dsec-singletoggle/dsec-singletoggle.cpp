/**
 * Name: Data Security SINGLETOGGLE control (BUTTON / SPST switch)
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for interfacing with a one way momentary toggle switch or button
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-dualtoggle.cpp
 * File description: dsec-dualtoggle library
 */
#ifndef DSecSingleToggle_cpp
#define DSecSingleToggle_cpp

#include <dsec-singletoggle.h>

int8_t DSecSingleToggle::ON   =  1;
int8_t DSecSingleToggle::OFF  =  0;

DSecSingleToggle::DSecSingleToggle() {

	// defaults!
	_previousState = 0;
	_state = 0;
	_lastChangedStateMS = millis();

}

void DSecSingleToggle::setPin(uint8_t pin) {
	_pin = pin;
}

uint8_t DSecSingleToggle::getPin() {
	return _pin;
}

void DSecSingleToggle::setState(uint8_t newState) {

	// @todo debounce here
	if (_state != newState) {
		_previousState = _state;
		_state = newState;
		_lastChangedStateMS = millis();
	}

}

int8_t DSecSingleToggle::getState() {
	if (_state > 0) {
		return DSecSingleToggle::ON;
	} else {
		return DSecSingleToggle::OFF;
	}
}

#endif  // DSecSingleToggle_cpp
