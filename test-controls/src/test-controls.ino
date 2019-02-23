
#include "dsec-dualtoggle.h"

#include <Adafruit_NeoPixel.h>
#include <MIDI.h>
#include "MUX74HC4067.h"
#include <Adafruit_NeoPixel.h>



Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 8, NEO_GRB + NEO_KHZ800);
uint8_t R = 255;
uint8_t G = 255;
uint8_t B = 255;

DSecDualToggle mainToggles[8] = DSecDualToggle();

// where is the mux?
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

	for(int i = 0; i < 10; i++)
		strip.setPixelColor(i,R,G,B);

	strip.show();

	mux.signalPin(SIG, INPUT, DIGITAL);

}

void loop() {
	// thingie.loop();

	for(int i = 0; i < 10; i++)
		strip.setPixelColor(i,R,G,B);

	R += mainToggles[0].getState();
	G += mainToggles[1].getState();

	Serial.print(mainToggles[0].getState());
	Serial.print(',');
	Serial.println(mainToggles[1].getState());

	// if (R > 0)
	// 	R--;
	//
	// if (G > 0)
	// 	G--;
	//
	// if (B > 0)
	// 	B--;

	strip.show();






	delay(2);


	checkSwitchStates();

}


void checkSwitchStates() {

	int data;
	// int SwitchStates[16];

	for (byte i = 0; i < 16; ++i) {

		// Reads from channel i and returns HIGH or LOW
		//int i = 12;
		data = mux.read(i);

		// if ( data == HIGH ) {
		// 	SwitchStates[i] = 1;
		// 	//Serial.print("1");
		// }
		// else if ( data == LOW ) {
		// 	SwitchStates[i] = 0;
		// 	//Serial.print("0");
		// }

		// @todo need some sort of a map for relating these back to their pins since the pins are a lil randomish

		// we need to know if it relates to the UP or DOWN position and targetSwitch -- 0-7
		// current seems to be even / odd so we could do %2 == 0 for the first part at least

		int8_t targetSwitch = -1;

		switch(i) {

			case 5:
			case 4:
				targetSwitch = 0;
				break;

			case 3:
			case 2:
				targetSwitch = 1;
				break;

		}


		// these are the UP,DOWN pins in order switches 0-7
		// 5,4
		// 3,2
		// 1,0
		// 11,10
		// 9,8
		// 7,6
		// 13,12
		// 15,14

		// We are up, and high vs we are down and high
		if (targetSwitch > 0 && (i == 5 || i == 3))
			mainToggles[targetSwitch].setUpState( data == HIGH );
		else if (targetSwitch > 0)
			mainToggles[targetSwitch].setDownState( data == HIGH );

		// Serial.print(i);
		// Serial.print("=");
		// Serial.print(SwitchStates[i]);
		//
		// if (i < 15)
		// 	Serial.print(" | ");

	}

	// for(int i = 0; i < 2; i++) {
	// 	mainToggles[i]
	// }

	Serial.println("");
	delay(20);

}
