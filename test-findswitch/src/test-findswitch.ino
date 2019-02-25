
	// 2,3,4,5,6,7,8 I believe these are all mux n' LED
uint8_t lowPin  = 9;
uint8_t highPin = 54;

void setup() {
	Serial.begin(9600);

	for(int curPin = lowPin; curPin <= highPin; curPin++) {
		pinMode(curPin, INPUT);
	}

}

void loop() {

	for(uint8_t curPin = lowPin; curPin <= highPin; curPin++) {
		int data = LOW;
		data = digitalRead( curPin );
		if (data == HIGH) {

			switch(curPin) {
				case 13:
				case 14:
				case 15:
				case 20:
				case 21:
				case 34:
				case 35:
				case 36:
				case 37:
					// no - these puppies must be LED or pots -- i see dem freakin out
					break;

				default:
					Serial.println( curPin );
					break;

			}

		}
	}

	delay(10);

}
