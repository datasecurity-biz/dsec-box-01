
#include "dsec-singletoggle.h"
#include "dsec-dualtoggle.h"
#include "dsec-knob.h"
#include "dsec-rgbled.h"

#include <Adafruit_NeoPixel.h>
#include <MIDI.h>
#include "MUX74HC4067.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 8, NEO_GRB + NEO_KHZ800);

DSecRGBLED seqLEDs[8];

// One toggle up top right
DSecDualToggle topToggle;

// 8 toggles left to right
DSecDualToggle mainToggles[8];// = DSecDualToggle();

// 4 buttons along the bottom
DSecSingleToggle buttons[4];

// 4 knobs along the bottom by the buttons
DSecKnob knobs[4];

// MUX!
MUX74HC4067 mux(7, 6, 5, 4, 3);
// Set SIG Pin from MUX74HC4067
#define SIG 2

void setup() {

	// box01 thingie needs some boiler plate to set up which pins do what
	// thingie.init( blah blha )

	Serial.begin(9600);
	while ( !Serial ) ;

	// Initialize all NeoPixels to 'off'
	strip.begin();
	strip.show();

	for(int loops = 0; loops < 10; loops++) {
		for(int i = 0; i < 10; i++) {
			strip.setPixelColor(i,127,0,0);
		}
		strip.show();
		delay(50);
		for(int i = 0; i < 10; i++) {
			strip.setPixelColor(i,0,0,0);
		}
		strip.show();
		delay(50);
	}

	mux.signalPin(SIG, INPUT, DIGITAL);

	// MIDDLE 8 TOGGLES:
	// UP, DOWN pins switches from 0-7 --- @ 5,4 | 3,2 | 1,0 | 11,10 | 9,8 | 7,6 | 13,12 | 15,14

	for(uint8_t i = 0; i < 8; i++)
		mainToggles[i] = DSecDualToggle();

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

	for (uint8_t i = 0; i < 4; i++)
		buttons[i] = DSecSingleToggle();

	pinMode(22, INPUT);
	pinMode(23, INPUT);
	pinMode(24, INPUT);
	pinMode(25, INPUT);

	buttons[0].setPin(22);
	buttons[1].setPin(23);
	buttons[2].setPin(24);
	buttons[3].setPin(25);

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
		seqLEDs[i].setNumber(9 - i);
	}

}

void loop() {
	// thingie.loop();

	// something like this :

	// do midi things
	// midi midi midi

	// LEDs
	updateDisplay();

	// read knobs and buttons
	readInterfaceState();

}


void readInterfaceState() {

	int8_t data;
	int16_t data16;

	for (uint8_t i = 0; i < 8; ++i) {

		// check the up state
		data = mux.read( mainToggles[i].getUpPin() );
		mainToggles[i].setUpState( data == HIGH );

		uint8_t upPin = mainToggles[i].getUpPin();
		uint8_t downPin = mainToggles[i].getDownPin();

		// check the up state
		data = mux.read( upPin );
		mainToggles[i].setUpState( data == HIGH );

		// check the down state
		data = mux.read( downPin );
		mainToggles[i].setDownState( data == HIGH );

		switch( mainToggles[i].getState() ) {
			case  1 :
				Serial.print("^");

				seqLEDs[i].setRGB(
					knobs[0].getPosition() * 255,
					knobs[1].getPosition() * 255,
					knobs[2].getPosition() * 255,
					knobs[3].getPosition() * 10000);

			break;
			case  0 : Serial.print("-"); break;
			case -1 :
				Serial.print("v");
				seqLEDs[i].setRGB(0,0,0, knobs[3].getPosition() * 10000);
			break;
		}

	}

	Serial.print(" ");

	// check the up state
	data = digitalRead( topToggle.getUpPin() );
	topToggle.setUpState( data == HIGH );

	// check the down state
	data = digitalRead( topToggle.getDownPin() );
	topToggle.setDownState( data == HIGH );

	switch( topToggle.getState() ) {
		case  1 : Serial.print("^"); break;
		case  0 : Serial.print("-"); break;
		case -1 : Serial.print("v"); break;
	}

	Serial.print(" ");

	for (uint8_t i = 0; i < 4; ++i) {
		int8_t data = digitalRead(buttons[i].getPin());
		buttons[i].setState(data);

		switch( buttons[i].getState() ) {
			case  1 : Serial.print("X"); break;
			case  0 : Serial.print("O"); break;
		}
	}

	Serial.print(" ");

	for(uint8_t i = 0; i < 4; i++) {
		data16 = analogRead( knobs[i].getPin() );
		knobs[i].setValue(data16);

		// Serial.print( knobs[i].getValue() );
		Serial.print( knobs[i].getPosition() );
		Serial.print(" ");

	}

	Serial.println("");

	// delay(20);

}

void updateDisplay() {

	boolean needRepaint = false;

	for(uint8_t i = 0; i < 8; i++) {
		seqLEDs[i].update();
		if (seqLEDs[i].isChanged()) {
			needRepaint = true;
			strip.setPixelColor( seqLEDs[i].getNumber(), seqLEDs[i].getR(), seqLEDs[i].getG(), seqLEDs[i].getB() );
		}
	}

	// check top two LEDs

	if (needRepaint) {
		Serial.println("DRAW U");
		strip.show();
	}

	// check bottom four button LEDs
	// deal with those here in a very special and rad way ??? 

}
