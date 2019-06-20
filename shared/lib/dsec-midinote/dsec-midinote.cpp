/**
 * Name: Data Security MidiNote
 * Author: Avery Brooks
 * Version: 0.0
 * Description: A library for sending a one off MIDI note message with a pre-
 *              determined lifetime MS
 * License: Copyright (c) 2019 Avery Brooks
 *          This library is licensed under the MIT license
 *          http://www.opensource.org/licenses/mit-license.php
 *
 * Filename: dsec-midinote.cpp
 * File description: dsec-midinote library
 */
#ifndef DSecMidiNote_cpp
#define DSecMidiNote_cpp

#include <dsec-midinote.h>

// is this a performant way to do this ?  shouldn't we pass the instance here by reference or similar ???
// MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI);

DSecMidiNote::DSecMidiNote() {
	// dummy empty note
	_pitch = 0;
	_velocity = 0;
	_channel = 0;
	_deathMillis = 0;
	_durationMS = 0;
	_dead = true;
}

DSecMidiNote::DSecMidiNote((midi::MidiInterface)& midiInterfaceInstance, uint8_t pitch, uint8_t velocity, uint8_t channel, long durationMS) {

	MIDI = midiInterfaceInstance;

	_dead = true;
	_pitch = pitch;
	_velocity = velocity;
	_channel = channel;
	_deathMillis = 0;
	_durationMS = durationMS;
	// a DSecMidiNote defines a one off note, which we send along with the assumption that it has a definite end time
	// this is intended for things like sequencers or drum patterns, where we can realistically know durations ahead of time
}

void DSecMidiNote::update() {
	if (!_dead && millis() >= _deathMillis) {
		stop();
	}
}

void DSecMidiNote::play() {
	MIDI.sendNoteOn( _pitch, _velocity, _channel );
	_deathMillis = millis() + _durationMS;
	_dead = false;
}

void DSecMidiNote::stop() {
	// immediately send note-off
	MIDI.sendNoteOff( _pitch, _velocity, _channel );
	_dead = true;
}

#endif // DSecMidiNote_cpp
