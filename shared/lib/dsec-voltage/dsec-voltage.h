/**
 * Name: Data Security VOLTAGE utility
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for checking the source voltage supplied to the arduino
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-voltage.h
 * File description: dsec-voltage library
 */
#ifndef DSecVoltage_h
#define DSecVoltage_h

#include <Arduino.h>

class DSecVoltage {

	public:

		DSecVoltage();
		long read ();

	private:

		long _reading;

};

#endif  // DSecVoltage_h
