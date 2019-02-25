
#include "dsec-dualtoggle.h"

#include <Adafruit_NeoPixel.h>
#include <MIDI.h>
#include "MUX74HC4067.h"
#include <Adafruit_NeoPixel.h>



Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, 8, NEO_GRB + NEO_KHZ800);
int8_t R = 0;
int8_t G = 0;
int8_t B = 0;

// 8 toggles left to right
DSecDualToggle mainToggles[8];// = DSecDualToggle();

// one toggle up top right
DSecDualToggle topToggle      = DSecDualToggle();

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

	// UP, DOWN pins switches from 0-7
	// 5,4
	// 3,2
	// 1,0
	// 11,10
	// 9,8
	// 7,6
	// 13,12
	// 15,14


}

void loop() {
	// thingie.loop();

	// something like this :

	int changededness = R + G + B;

	R += mainToggles[0].getState();
	G += mainToggles[1].getState();
	B += mainToggles[2].getState();

	if (R < 0)
		R = 0;

	if (G < 0)
		G = 0;

	if (B < 0)
		B = 0;

	if (R > 255)
		R = 255;

	if (G > 255)
		G = 255;

	if (B > 255)
		B = 255;



	if (R + G + B != changededness) {

		for(int i = 0; i < 10; i++)
			strip.setPixelColor(i,R,G,B);

		strip.show();
	}

	// delay(2);

	readInterfaceState();

}


void readInterfaceState() {

	int8_t data;

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
			case  1 : Serial.print("^"); break;
			case  0 : Serial.print("-"); break;
			case -1 : Serial.print("v"); break;
		}

	}

	Serial.print(" ");

	switch( topToggle.getState() ) {
		case  1 : Serial.print("^"); break;
		case  0 : Serial.print("-"); break;
		case -1 : Serial.print("v"); break;
	}

	Serial.println("");

	// delay(20);

}
