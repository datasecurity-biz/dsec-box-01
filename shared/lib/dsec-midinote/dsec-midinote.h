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
#ifndef DSecMidiNote_h
#define DSecMidiNote_h

#include <Arduino.h>
#include <MIDI.h>

class DSecMidiNote {

	public:

		DSecMidiNote();
		DSecMidiNote((midi::MidiInterface)& midiInterfaceInstance, uint8_t pitch, uint8_t velocity, uint8_t channel, long durationMS);

		void play();
		void stop();

		/**
		 * Called once per loop - update 'current' state / changedness
		 */
		void update();

	private:

		midi::MidiInterface &MIDI;

		bool _dead;
		uint8_t _pitch;
		uint8_t _velocity;
		uint8_t _channel;
		long _durationMS;
		long _deathMillis;

};

#endif // DSecRGBLED_h
