/**
 * Name: Data Security VOLTAGE utility
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for checking the source voltage supplied to the arduino
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-voltage.cpp
 * File description: dsec-voltage library
 */
#ifndef DSecVoltage_cpp
#define DSecVoltage_cpp

#include <dsec-voltage.h>

DSecVoltage::DSecVoltage() {

	_reading = 0;

}

/**
 * return the current voltage supplied in mV
 */
long DSecVoltage::read() {

	if (_reading > 0)
		return _reading;

	long result;
	// Read 1.1V reference against AVcc
	ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
	delay(2); // Wait for Vref to settle
	ADCSRA |= _BV(ADSC); // Convert
	while (bit_is_set(ADCSRA,ADSC));
	result = ADCL;
	result |= ADCH<<8;
	result = 1126400L / result; // Back-calculate AVcc in mV

	_reading = result;

	return _reading;

}

#endif  // DSecVoltage_cpp
