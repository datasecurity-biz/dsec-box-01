#include <Arduino.h>
#include <MIDI.h>
#include "dsec-box-01.h"

DSecBox01 box;

unsigned long lastClockMS = 0;
uint8_t BPM = 120;

MIDI_CREATE_DEFAULT_INSTANCE();

/**
 * Initial setup
 */
void setup() {

	box = DSecBox01();

	// @todo make this more configurable
	// box01 thingie needs some boiler plate to set up which pins do what
	// thingie.setup( blah blah )

	box.setup();
	lastClockMS = millis();

	// Serial.begin(115200);
	// while (!Serial);
	MIDI.begin();
	// MIDI.setHandleNoteOn(handleNoteOn);
	// MIDI.setHandleNoteOff(handleNoteOff);
	MIDI.setHandleClock(handleClock);

	Serial.println("Arduino ready.");

}

/**
 *
 */
void loop() {

	// this can be moved into box.loop i believe
	MIDI.read();
	box.loop();

}

void handleClock() {

	long diff = millis() - lastClockMS;
	lastClockMS = millis();

	box.buttonLEDs[0].setOn(5);

}
