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
#ifndef DSecRGBLED_cpp
#define DSecRGBLED_cpp

#include <dsec-rgbled.h>

//. @todo see .h and write this
// needs to do some interpolatioj thing
// also we need a notion of if the LEDs are changed / should be written to

DSecRGBLED::DSecRGBLED() {

	_R = 0;
	_G = 0;
	_B = 0;

	_lastR = 0;
	_lastG = 0;
	_lastB = 0;

	_targetR = 0;
	_targetG = 0;
	_targetB = 0;

	_changeRMS = 0;
	_changeGMS = 0;
	_changeBMS = 0;

	_forceChange = false;

	_lastMS = millis();
	_targetMillis = millis();

}

uint8_t DSecRGBLED::getR() {
	return this->to8bit(_R);
}

uint8_t DSecRGBLED::getG() {
	return this->to8bit(_G);
}

uint8_t DSecRGBLED::getB() {
	return this->to8bit(_B);
}

/**
 * Jump instantly to a new R/G/B
 * this doesn't work somehow -- doesn't appear 'changed' -- needs update
 */
void DSecRGBLED::setRGB( uint8_t R, uint8_t G, uint8_t B ) {
	_R = this->to16bit(R);
	_G = this->to16bit(G);
	_B = this->to16bit(B);

	// no change after this force
	_changeRMS = 0;
	_changeGMS = 0;
	_changeBMS = 0;

	_targetMillis = millis();

	// next update cycle in box must receive this via ::receiveForceChange()
	_forceChange = true;
}

/**
 * Ramp to a new R/G/B over {rampTime} MS
 */
void DSecRGBLED::setRGB( uint8_t R, uint8_t G, uint8_t B, long rampTime ) {

	int16_t R16 = this->to16bit(R);
	int16_t G16 = this->to16bit(G);
	int16_t B16 = this->to16bit(B);

	_targetR = R16;
	_targetG = G16;
	_targetB = B16;

	// figure out change per MS
	_changeRMS = (R16 - _R) / rampTime;
	_changeGMS = (G16 - _G) / rampTime;
	_changeBMS = (B16 - _B) / rampTime;

	// set future arrival time of this pup
	_targetMillis = millis() + rampTime;
}

/**
 * Get the 'number' of the LED
 */
uint8_t DSecRGBLED::getNumber() {
	return _number;
}

void DSecRGBLED::setNumber(uint8_t number) {
	_number = number;
}

void DSecRGBLED::update() {

	long elapsedMS = millis() - _lastMS;

	_lastR = _R;
	_lastG = _G;
	_lastB = _B;

	_R += _changeRMS * elapsedMS;
	_G += _changeGMS * elapsedMS;
	_B += _changeBMS * elapsedMS;

	if (millis() >= _targetMillis) {
		_changeRMS = 0;
		_changeGMS = 0;
		_changeBMS = 0;
		_R = _targetR;
		_G = _targetG;
		_B = _targetB;
	}

	_lastMS = millis();

}

uint8_t DSecRGBLED::to8bit(int16_t rangedValue) {
	float rv = (float) rangedValue;
	return (uint8_t) ((rv / 32768) * 255);
}

int16_t DSecRGBLED::to16bit(uint8_t rangedValue) {
	float rv = (float) rangedValue;
	return (int16_t) ((rv / 255) * 32768);
}

boolean DSecRGBLED::isChanged() {
	return _R != _lastR || _G != _lastG || _B != _lastB;
}

boolean DSecRGBLED::receiveForceChange() {
	if (_forceChange) {
		_forceChange = false;
		return true;
	}
	return false;
}

#endif // DSecRGBLED_cpp
