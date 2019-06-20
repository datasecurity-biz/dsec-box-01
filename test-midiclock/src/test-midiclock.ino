#include <Arduino.h>
#include <MIDI.h>
#include "dsec-box-01.h"

#include "dsec-midinote.h"

// @todomove this all to box / ifndef etc for defaults
#define MIDI_CLOCK_PPQ 24

DSecBox01 box;

unsigned long lastClockMS = 0;
uint8_t BPM = 120;
uint8_t currentTick = 0;
uint8_t currentStep = 0;
uint8_t ticksPerStep = MIDI_CLOCK_PPQ / 4; // four steps per quarter


DSecMidiNote bork;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI);
// midi::MidiInterface&

/**
 * Initial setup
 */
void setup() {

	box = DSecBox01();

	// @todo make this more configurable
	// box01 thingie needs some boiler plate to set up which pins do what
	// thingie.setup( blah blah )

	box.setup(); // .begin maybe is better ? more standardsy ?
	box.setDumpInterfaceState( false );

	lastClockMS = millis();

	Serial.begin(9600);
	while (!Serial);

	MIDI.begin(); // MIDI_CHANNEL_OMNI

	// Don't necciscarily send clock etc out ... unless we want to do that ( switch or button on boot maybe )
	MIDI.turnThruOff();

	MIDI.setHandleNoteOn(handleNoteOn);
	MIDI.setHandleNoteOff(handleNoteOff);
	MIDI.setHandleClock(handleClock);

	MIDI.setHandleStart(handleStart);
	MIDI.setHandleStop(handleStop);
	MIDI.setHandleContinue(handleContinue);

	Serial.println("Arduino ready.");



	bork = DSecMidiNote( MIDI, 10, 127, 1, 1000 );
	bork.play();

}


bool lastButtonState[4] = {false,false,false,false};

/**
 *
 */
void loop() {



	bork.update();



	// this can be moved into box.loop i believe
	MIDI.read();
	box.loop(); // maybe .read too ? hm




	// Test sending midi with the buttons

	for(uint8_t i = 0; i < 4; i++) {
		if (box.buttons[i].getState() == true && !lastButtonState[i]) {
			MIDI.sendNoteOn(42 + i, 127, 1);
			lastButtonState[i] = true;
		} else if (box.buttons[i].getState() == false && lastButtonState[i]) {
			MIDI.sendNoteOff(42 + i, 127, 1);
			lastButtonState[i] = false;
		}
	}

}

void handleClock() {


	// 60000 / (BPM * MIDI_CLOCK_PPQ) = TICKMS

	// long diff = millis() - lastClockMS;
	// lastClockMS = millis();

	for(uint8_t i = 0; i < 8; i++) {
		if (i != currentStep) {
			box.seqLEDs[i].setRGB(0,0,0,1);
		}
	}
	//
	box.seqLEDs[currentStep].setRGB(255,0,0,1);

	// if (currentTick % )
	currentTick = (currentTick + 1) % MIDI_CLOCK_PPQ;

	if (currentTick % ticksPerStep == 0) {
		currentStep = (currentStep + 1) % 8;
	}

	// @todo -- figure out an onChange onStep onStep ( stepNum ) type thing
	// // if (currentStep == 0 && currentTick == 0) {
	// if (currentStep % 2 == 0 && currentTick == 0) {
	// 	MIDI.sendNoteOn(42, 127, 1);
	// // } else if (currentStep == 1) {
	// } else if (currentStep % 2 == 1 && currentTick == MIDI_CLOCK_PPQ / 2) {
	// 	MIDI.sendNoteOff(42, 127, 1);
	// }

	// Serial.print(currentStep);
	// Serial.print(" clock ");
	// Serial.println( currentTick );

	/*
	currentTick++;
	if (currentTick >= MIDI_CLOCK_PPQ) {
		currentTick = 0;
		// long beatMS = diff * MIDI_CLOCK_PPQ;
		// float bpm = 60000 / (((float) beatMS) * 60);
		// Serial.println(bpm);
	}
	*/

}

void handleNoteOn(byte channel, byte pitch, byte velocity) {
	// Do whatever you want when a note is pressed.
	// Try to keep your callbacks short (no delays ect)
	// otherwise it would slow down the loop() and have a bad impact
	// on real-time performance.
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
	// Do something when the note is released.
	// Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
}

void handleStart() {
	currentTick = 0;
	currentStep = 0;
	box.topLEDs[0].setRGB(0,255,0);
}

void handleStop() {
	box.topLEDs[0].setRGB(0,0,0);
}

void handleContinue() {

}
