int doubleRed = 13; // Output pin to the two red lights.
int doubleYellow = 12; // Output pin to the two yellow lights.
int doubleGreen = 11; // Output pin to the two green lights.

int singleRed = 10; // Output pin to the single red light.
int singleYellow = 9; // Output pin to the single yellow light.
int singleGreen = 8; // Output pin to the single green light.

// The setup function runs once when you press reset or power the board
void setup() {
	
	// Set the lights to 5v.
	pinMode(doubleRed, OUTPUT); // Initialize digital pin as an output.
	pinMode(doubleYellow, OUTPUT); // Initialize digital pin as an output.
	pinMode(doubleGreen, OUTPUT); // Initialize digital pin as an output.
	pinMode(singleRed, OUTPUT); // Initialize digital pin as an output.
	pinMode(singleYellow, OUTPUT); // Initialize digital pin as an output.
	pinMode(singleGreen, OUTPUT); // Initialize digital pin as an output.

	// Turn off all of the lights at the start.
	digitalWrite(doubleRed, LOW);
	digitalWrite(doubleYellow, LOW);
	digitalWrite(doubleGreen, LOW);
	digitalWrite(singleRed, LOW);
	digitalWrite(singleYellow, LOW);
	digitalWrite(singleGreen, LOW);
}

// The loop function runs over and over again forever
void loop() {
	// 2G 1R
	digitalWrite(doubleRed, LOW);
	digitalWrite(doubleGreen, HIGH);
	digitalWrite(singleRed, HIGH);

	delay(3000);

	// 2Y 1R
	digitalWrite(doubleGreen, LOW);
	digitalWrite(doubleYellow, HIGH);

	delay(1000);

	// 2R 1R
	digitalWrite(doubleYellow, LOW);
	digitalWrite(doubleRed, HIGH);

	delay(1000);

	// 2R 1G
	digitalWrite(doubleRed, HIGH);
	digitalWrite(singleRed, LOW);
	digitalWrite(singleGreen, HIGH);

	delay(3000);
	
	// 2R 1Y
	digitalWrite(singleGreen, LOW);
	digitalWrite(singleYellow, HIGH);
	
	delay(1000);
	
	// 2R 1R
	digitalWrite(singleYellow, LOW);
	digitalWrite(singleRed, HIGH);

	delay(1000);
}

