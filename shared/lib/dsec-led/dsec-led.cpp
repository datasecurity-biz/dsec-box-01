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
#ifndef DSecLED_cpp
#define DSecLED_cpp

#include <dsec-led.h>

//. @todo see .h and write this
// needs to do some interpolatioj thing
// also we need a notion of if the LEDs are changed / should be written to

DSecLED::DSecLED() {

	_state = false;
	_lastState = false;

	_lastMillis = millis();
	_targetMillis = millis();

}

/**
 * Change _state instantly to new state
 */
void DSecLED::setState( boolean state ) {
	_state = state;
	_targetState = state;
	_targetMillis = millis();
}

/**
 * Change _state to state for {lifetimeMS} MS, before switching back to last
 */
void DSecLED::setState( boolean state, long lifetimeMS ) {

	// flip target to be current state
	_targetState = _state;
	// _lastState = // this happens in this->update()

	// set current state to be desired state
	_state = state;

	// set future arrival time of previous state
	_targetMillis = millis() + lifetimeMS;
}

/**
 * Change _state to state for {lifetimeMS} MS, before switching back to last
 */
void DSecLED::setOn( long lifetimeMS ) {

	// flip target to be current state
	_targetState = false;
	// _lastState = // this happens in this->update()

	// set current state to be desired state
	_state = true;

	// set future arrival time of previous state
	_targetMillis = millis() + lifetimeMS;
}

boolean DSecLED::getState() {
	return _state;
}

/**
 * Get the 'number' of the LED
 */
uint8_t DSecLED::getPin() {
	return _pin;
}

void DSecLED::setPin(uint8_t pin) {
	_pin = pin;
}

void DSecLED::update() {

	// store last state
	_lastState = _state;

	// long elapsedMS = millis() - _lastMillis;

	// check for state change needed
	if (millis() >= _targetMillis && _state != _targetState) {
		_state = _targetState;
		// changed!
	}

	// store last time we did ms
	_lastMillis = millis();

}

boolean DSecLED::isChanged() {
	return _state != _lastState;
}

#endif // DSecLED_cpp
