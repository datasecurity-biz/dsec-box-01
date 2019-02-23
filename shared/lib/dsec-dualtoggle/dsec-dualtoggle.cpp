/**
 * Name: Data Security DUALTOGGLE control
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for interfacing with a two way momentary toggle switch
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-dualtoggle.cpp
 * File description: dsec-dualtoggle library
 */
#ifndef DSecDualToggle_cpp
#define DSecDualToggle_cpp

#include <dsec-dualtoggle.h>

DSecDualToggle::DSecDualToggle() {

	// defaults!
	_previousUpState = 0;
	_previousDownState = 0;
	_upState = 0;
	_downState = 0;
	_lastChangedUpStateMS = millis();
	_lastChangedDownStateMS = _lastChangedUpStateMS;

}

void DSecDualToggle::setUpState(uint8_t newState) {

	// @todo debounce here
	if (_upState != newState) {
		_previousUpState = _upState;
		_upState = newState;
		_lastChangedUpStateMS = millis();
	}

}

void DSecDualToggle::setDownState(uint8_t newState) {

	// @todo debounce here
	if (_downState != newState) {
		_previousDownState = _downState;
		_downState = newState;
		_lastChangedDownStateMS = millis();
	}

}

int8_t DSecDualToggle::getState() {
	if (_upState > 0 && _downState == 0) {
		return 1;
	} else if (_upState == 0 && _downState > 0) {
		return -1;
	} else {
		return 0;
	}
}

#endif  // DSecDualToggle_cpp
