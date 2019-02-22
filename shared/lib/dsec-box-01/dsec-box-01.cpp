


void setup() {

	Serial.begin(9600);
	while ( !Serial ) ;

	// Initialize all NeoPixels to 'off'
	strip.begin();
	strip.show();

	for(int i = 0; i < 10; i++)
		strip.setPixelColor(i,R,G,B);

	strip.show();

}

void loop() {

	for(int i = 0; i < 10; i++)
		strip.setPixelColor(i,R,G,B);

	if (R > 0)
		R--;

	if (G > 0)
		G--;

	if (B > 0)
		B--;

	strip.show();

	delay(2);

}
