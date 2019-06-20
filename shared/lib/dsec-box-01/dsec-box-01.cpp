
#include "dsec-box-01.h"

#include "dsec-singletoggle.h"
#include "dsec-dualtoggle.h"
#include "dsec-knob.h"
#include "dsec-rgbled.h"
#include "dsec-led.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <MIDI.h>
#include "MUX74HC4067.h"

// Set SIG Pin from MUX74HC4067
#define SIG 2

MUX74HC4067 mux(7, 6, 5, 4, 3);
Adafruit_NeoPixel strip(10, 8, NEO_GRB + NEO_KHZ800);

DSecBox01::DSecBox01() {

}

void DSecBox01::setup() {

	// box01 thingie needs some boiler plate to set up which pins do what
	// thingie.init( blah blha )

	Serial.begin(9600);
	while ( !Serial ) ;

	mux.signalPin(SIG, INPUT, DIGITAL);

	// Initialize all NeoPixels to 'off'
	strip.begin();
	strip.show();

	for(int loops = 0; loops < 3; loops++) {
		for(int i = 0; i < 1; i++) {
			strip.setPixelColor(i,255,0,0);
		}
		strip.show();
		delay(50);
		for(int i = 0; i < 10; i++) {
			strip.setPixelColor(i,0,0,0);
		}
		strip.show();
		delay(50);
	}

	// MIDDLE 8 TOGGLES:
	// UP, DOWN pins switches from 0-7 --- @ 5,4 | 3,2 | 1,0 | 11,10 | 9,8 | 7,6 | 13,12 | 15,14

	for(uint8_t i = 0; i < 8; i++)
		mainToggles[i] = DSecDualToggle();

	// these are all over the place, so setting them manually outside of the loop

	mainToggles[0].setUpPin(5);
	mainToggles[0].setDownPin(4);
	mainToggles[1].setUpPin(3);
	mainToggles[1].setDownPin(2);
	mainToggles[2].setUpPin(1);
	mainToggles[2].setDownPin(0);
	mainToggles[3].setUpPin(11);
	mainToggles[3].setDownPin(10);
	mainToggles[4].setUpPin(9);
	mainToggles[4].setDownPin(8);
	mainToggles[5].setUpPin(7);
	mainToggles[5].setDownPin(6);
	mainToggles[6].setUpPin(13);
	mainToggles[6].setDownPin(12);
	mainToggles[7].setUpPin(15);
	mainToggles[7].setDownPin(14);

	// TOP RIGHT TOGGLE SWITCH:

	pinMode(9, INPUT);
	pinMode(10, INPUT);

	topToggle = DSecDualToggle();
	topToggle.setUpPin(9);
	topToggle.setDownPin(10);

	// BUTTONS

	for (uint8_t i = 0; i < 4; i++) {
		buttons[i] = DSecSingleToggle();
		buttons[i].setPin(22 + i);
		pinMode(buttons[i].getPin(), INPUT);

	}

	// KNOBS

	for (uint8_t i = 0; i < 4; i++)
		knobs[i] = DSecKnob();

	knobs[0].setPin(A3);
	knobs[1].setPin(A2);
	knobs[2].setPin(A1);
	knobs[3].setPin(A0);

	// LEDs

	for (uint8_t i = 0; i < 8; i++) {
		seqLEDs[i] = DSecRGBLED();
		seqLEDs[i].setNumber(9 - i); // pixels 9-2, left to right
	}

	for (uint8_t i = 0; i < 2; i++) {
		topLEDs[i] = DSecRGBLED();
		topLEDs[i].setNumber(i); // pixels 0-1, left to right
	}

	for (uint8_t i = 0; i < 4; i++) {
		buttonLEDs[i] = DSecLED();
		buttonLEDs[i].setPin(34 + i); // pins 34-37
		pinMode(buttonLEDs[i].getPin(), OUTPUT); // INPUT_PULLUP); ? not sure
		delay(10);
		digitalWrite(buttonLEDs[i].getPin(), HIGH);
	}

}

void DSecBox01::_sendMidi() {}

void DSecBox01::_readMidi() {}

void DSecBox01::_readInterfaceState() {

	int8_t data;
	int16_t data16;

	for (uint8_t i = 0; i < 8; ++i) {

		// check the up state
		data = mux.read( mainToggles[i].getUpPin() );
		mainToggles[i].setUpState( data == HIGH );

		// check the down state
		data = mux.read( mainToggles[i].getDownPin() );
		mainToggles[i].setDownState( data == HIGH );

		switch( mainToggles[i].getState() ) {
			case  1 :
				if (_dumpInterfaceState)
					Serial.print("^");

				seqLEDs[i].setRGB(
					knobs[0].getPosition() * 255,
					knobs[1].getPosition() * 255,
					knobs[2].getPosition() * 255,
					knobs[3].getPosition() * 10000);

			break;
			case  0 :
				if (_dumpInterfaceState)
					Serial.print("-");
				break;
			case -1 :
				if (_dumpInterfaceState)
					Serial.print("v");
				seqLEDs[i].setRGB(0,0,0, knobs[3].getPosition() * 10000);
			break;
		}

	}

	if (_dumpInterfaceState)
		Serial.print(" ");

	// check the up state
	data = digitalRead( topToggle.getUpPin() );
	topToggle.setUpState( data == HIGH );

	// check the down state
	data = digitalRead( topToggle.getDownPin() );
	topToggle.setDownState( data == HIGH );

	switch( topToggle.getState() ) {
		case  1 :
			if (_dumpInterfaceState)
				Serial.print("^");
			topLEDs[0].setRGB(
				knobs[0].getPosition() * 255,
				knobs[1].getPosition() * 255,
				knobs[2].getPosition() * 255,
				knobs[3].getPosition() * 10000);
		break;
		case  0 :
			if (_dumpInterfaceState)
				Serial.print("-");
		break;
		case -1 :
			if (_dumpInterfaceState)
				Serial.print("v");
			topLEDs[0].setRGB(0,0,0, knobs[3].getPosition() * 10000);
		break;
	}

	if (_dumpInterfaceState)
		Serial.print(" ");

	for (uint8_t i = 0; i < 4; ++i) {
		int8_t data = digitalRead(buttons[i].getPin());
		buttons[i].setState(data);

		switch( buttons[i].getState() ) {
			case  1 :
				if (_dumpInterfaceState)
					Serial.print("X");
				// buttonLEDs[i].setState(false);
				// buttonLEDs[i].setState(true, 1000);
				buttonLEDs[i].setOn(1000);
				break;
			case  0 :
				if (_dumpInterfaceState)
					Serial.print("O");
				// buttonLEDs[i].setState(true);
				break;
		}
	}

	if (_dumpInterfaceState) {
		Serial.print(" ");
	}

	for(uint8_t i = 0; i < 4; i++) {
		data16 = analogRead( knobs[i].getPin() );
		knobs[i].setValue(data16);

		if (_dumpInterfaceState) {
			Serial.print( knobs[i].getPosition() );
			Serial.print(" ");
		}

	}

	if (_dumpInterfaceState) {
		Serial.println("");
	}

}

void DSecBox01::_updateDisplay() {

	boolean needRepaint = false;

	// check 8x indicator LEDs

	for(uint8_t i = 0; i < 8; i++) {
		seqLEDs[i].update();
		if (seqLEDs[i].isChanged()) {
			needRepaint = true;
			strip.setPixelColor( seqLEDs[i].getNumber(), seqLEDs[i].getR(), seqLEDs[i].getG(), seqLEDs[i].getB() );
		}
	}

	// check top two LEDs

	for(uint8_t i = 0; i < 2; i++) {
		topLEDs[i].update();
		if (topLEDs[i].isChanged()) {
			needRepaint = true;
			strip.setPixelColor( topLEDs[i].getNumber(), topLEDs[i].getR(), topLEDs[i].getG(), topLEDs[i].getB() );
		}
	}

	if (needRepaint) {
		strip.show();
	}

	// check bottom four button LEDs

	for(uint8_t i = 0; i < 4; i++) {
		buttonLEDs[i].update();
		// if (buttonLEDs[i].isChanged() ) {
			// digitalWrite( buttonLEDs[i].getPin(), buttonLEDs[i].getState() ? HIGH : LOW );
		// }
		digitalWrite( buttonLEDs[i].getPin(), buttonLEDs[i].getState() ? LOW : HIGH );
	}

}

void DSecBox01::setDumpInterfaceState(bool state) {
	_dumpInterfaceState = state;
}

void DSecBox01::loop() {
	// thingie.loop();

	// something like this :

	// do midi things
	// midi midi midi
	_readMidi();

	// LEDs
	_updateDisplay();

	// read knobs and buttons
	_readInterfaceState();

	// what we do for midi
	_sendMidi();

}
