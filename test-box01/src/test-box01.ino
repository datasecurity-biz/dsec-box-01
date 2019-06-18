#include <Arduino.h>
#include "dsec-box-01.h"

DSecBox01 box;

/**
 * Initial setup
 */
void setup() {

	box = DSecBox01();

	// @todo make this more configurable
	// box01 thingie needs some boiler plate to set up which pins do what
	// thingie.setup( blah blah )

	box.setup();

}

/**
 *
 */
void loop() {

	box.loop();

}
