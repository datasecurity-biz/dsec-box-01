// Kelly's MIDI / hardware testing build:


#include <MIDI.h>
#include <Adafruit_NeoPixel.h>
#include "MUX74HC4067.h"

// Setup NeoPixel stuff
#define PIN 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);

long lastSentMS = 0;

int numButtons = 4;
int numPots = 4;
int numSwitches = 9;

// Arrays to define Arduino Pins for I/O
int button[] = {22, 23, 24, 25};
int LED[] = {34, 35, 36, 37};
int POT[] = {A3, A2, A1, A0};

// Arrays to save states of given I/O devices
int buttonStates[] = {0, 0, 0, 0};
int LEDStates[] = {LOW, LOW, LOW, LOW};
int POTStates[] = {0, 0, 0, 0};
int SwitchStates[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Ints for saving current states of pots, buttons, within check phases
int buttonCurrent;
int potCurrent;

// Define MUX74HC4067 device pins as such: (EN, S0, S1, S2, S3)
MUX74HC4067 mux(7, 6, 5, 4, 3);
// Set SIG Pin from MUX74HC4067
#define SIG 2

// Create a MIDI instance
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI);

// set to true to have midi events represented with the neopixels
bool midiDebug = true;

void setup() {
	// Initializes serial port
	Serial.begin(9600);
	while ( !Serial ) ;

	// Initialize all NeoPixels to 'off'
	strip.begin();
	strip.show();

	// Sets Input Pins for Buttons, Button LEDS, and Pots ¡¡SWITCHES DONE VIA MUX BELOW!!
	initDevices();

	// Flash the button LEDs, end in off
	flashButtonLEDs();

	// Configures how the SIG pin will be interfaced
	mux.signalPin(SIG, INPUT, DIGITAL);

	// Launch MIDI and listen to all channels
	MIDI.begin(MIDI_CHANNEL_OMNI);
	// Set MIDI ON/OFF function names
	if (midiDebug) {
		MIDI.setHandleNoteOn(MidiNoteOnDEBUG);
		MIDI.setHandleNoteOff(MidiNoteOffDEBUG);
	}
	else {
		MIDI.setHandleNoteOn(MidiNoteOn);
		MIDI.setHandleNoteOff(MidiNoteOff);
	}

	// Flash the NeoPixels to finalize setup, end in off
	flashRGB();
}

void loop() {

	checkButtonStates();
	checkPotStates();
	//checkSwitchStates();
//Serial.println();

//  midiOnThings();
//  MIDI.read();
//  midiOffThings();

//  midiNoteDebug();
//  MIDI.read();
//  delay(5);

//  Serial.println( );
	// Serial.println(POTStates[0]);

	if (millis() - lastSentMS > map(POTStates[3],0,127,100,10)) {

		MIDI.sendNoteOn(map(POTStates[0], 0, 127,36,48), 100, 8); // POTStates[2]);

//    Serial.print(POTStates[0]);
//    Serial.print(",");
//    Serial.print(POTStates[1]);
//    Serial.print(",");
//    Serial.print(POTStates[2]);
//    Serial.println();

		lastSentMS = millis();

	}

		MIDI.read();


//  delay(50);

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
	for (uint16_t i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		strip.show();
		delay(wait);
	}
}

//MIDI STUFF
void midiOnThings() {
	MIDI.sendNoteOn(42, 127, 1);
	Serial.println("sent Midi Note ON");
}

void midiOffThings() {
	MIDI.sendNoteOff(42, 0, 1);
	Serial.println("sent Midi Note OFF");
}


// What to do if a midi note ON message comes
void MidiNoteOn(byte chan, byte pitch, byte velocity) {

}
// What to do if a midi note OFF message comes
void MidiNoteOff(byte chan, byte pitch, byte velocity) {

}


/// MIDI DEBUGGING
void midiNoteDebug() {

	for (int i = 0; i < numButtons; i++) {
		int OnOff = buttonStates[i];
		int pitch = POTStates[i];
//    Serial.print(OnOff);
//    Serial.print(" x ");
//    Serial.print(pitch);
//    Serial.print(" x ");
//    Serial.println(i);

		if (OnOff == 1) {
			MIDI.sendNoteOn(pitch, 127, i+1);
		}
		else if (OnOff == 0) {
			MIDI.sendNoteOff(pitch, 0, i+1);
		}
	}

}

// What to do if a midi note ON message comes in DEBUG mode
void MidiNoteOnDEBUG(byte chan, byte pitch, byte velocity){
	Serial.print("GOT MIDI ON ");
	Serial.print("chan ");
	Serial.print(chan);
	Serial.print("pitch ");
	Serial.print(pitch);
	Serial.print("velocity ");
	Serial.print(velocity);
	Serial.println();

	for(int i = 0; i < 11; i++) {
		strip.setPixelColor(map(pitch,36,51,0,10), pitch, velocity*2, pitch*2);
	}
	strip.show();



}

// What to do if a midi note OFF message comes in DEBUG mode
void MidiNoteOffDEBUG(byte chan, byte pitch, byte velocity){
	Serial.print("GOT MIDI OFF");
	Serial.print("chan ");
	Serial.print(chan);
	Serial.print("pitch ");
	Serial.print(pitch);
	Serial.print("velocity ");
	Serial.print(velocity);
	Serial.println();

	for(int i = 0; i < 11; i++) {
		strip.setPixelColor(map(pitch,36,51,0,10), 0, 0, 0);
	}
	strip.show();
}

void checkButtonStates() {
	//Serial.print(" Button Sates:");
	for (int i = 0; i < numButtons; i++) {
		buttonCurrent = digitalRead(button[i]);
		if (buttonCurrent == HIGH) {
			digitalWrite(LED[i], LOW);
			//MIDI.sendNoteOn(60 + i, 127, 1);
		}
		else {
			digitalWrite(LED[i], HIGH);
			//MIDI.sendNoteOff(60 + i, 0, 1);
		}
		buttonStates[i] = buttonCurrent;
		//Serial.print(buttonCurrent);
		//Serial.print("|");

	}
}

void checkPotStates() {
	//Serial.print(" POT Sates: ");
	for (int i = 0; i < numPots; i++) {
		int potRead = analogRead(POT[i]);
//    Serial.print(i);
//    Serial.print("@");
//    Serial.print(potRead);
		potCurrent = map(potRead,0,1023,0,127);
//    Serial.print("->");
//    Serial.println(potCurrent);
		POTStates[i] = potCurrent;
		//Serial.print(potCurrent);
		//Serial.print("|");
	}
}

void checkSwitchStates() {

	Serial.print(" Switch Sates: ");
	int data;
	for (byte i = 0; i < 16; ++i)
	{
		// Reads from channel i and returns HIGH or LOW
		//int i = 12;
		data = mux.read(i);
		if ( data == HIGH ) {
			SwitchStates[i] = 1;
			//Serial.print("1");
		}
		else if ( data == LOW ) {
			SwitchStates[i] = 0;
			//Serial.print("0");
		}
		Serial.print(SwitchStates[i]);
		Serial.print("|");
		delay(20);
	}

}

void initDevices() {

	for (int i = 0; i < numButtons; i++) {
		pinMode(button[i], INPUT);
		pinMode(LED[i], OUTPUT);
	}
	for (int i = 0; i < numPots; i++) {
		pinMode(POT[i], INPUT);
	}

}

void flashButtonLEDs() {

	for (int i = 0; i < 4; i++) {
		digitalWrite(LED[i], HIGH);
		delay(100);
		digitalWrite(LED[i], LOW);
		delay(100);
	}

}

void flashRGB() {

	colorWipe(strip.Color(255, 0, 0), 10); // Red
	colorWipe(strip.Color(0, 255, 0), 10); // Green
	colorWipe(strip.Color(0, 0, 255), 10); // Blue
	colorWipe(strip.Color(0, 0, 0), 10); // off

}
