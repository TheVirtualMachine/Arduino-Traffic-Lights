#include <Servo.h>
#include "pitches.h"

// The traffic light structure. This is made of a red, yellow, and green light.
struct TrafficLight {
	int redPin;
	int yellowPin;
	int greenPin;

	bool red;
	bool yellow;
	bool green;
};

// Define the light colours.
enum lightColours {
    RED,
    YELLOW,
    GREEN
};

const int NOTE_REST = 0;

unsigned int currentNote = 0; // The index of current note being played in the arrays.
unsigned long noteEndTime = 0; // The time in milliseconds to stop the current note.

// Notes in the melody.
const int melody[] = { NOTE_C2, NOTE_DS4, NOTE_DS4, NOTE_C3, NOTE_DS4, NOTE_DS4, NOTE_AS3, NOTE_C3, NOTE_DS4, NOTE_DS4, NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_F2, NOTE_F4, NOTE_F4, NOTE_F2, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_F4, NOTE_F4, NOTE_DS2, NOTE_D2, NOTE_C2, NOTE_C4, NOTE_C2, NOTE_DS4, NOTE_DS4, NOTE_C3, NOTE_DS4, NOTE_DS4, NOTE_AS3, NOTE_C3, NOTE_DS4, NOTE_DS4, NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_F2, NOTE_F4, NOTE_F4, NOTE_F2, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_F4, NOTE_F4, NOTE_DS2, NOTE_D2, NOTE_C2, NOTE_C4, NOTE_DS3, NOTE_DS3, NOTE_AS2, NOTE_AS2, NOTE_C3, NOTE_C3, NOTE_DS3, NOTE_DS3, NOTE_REST, NOTE_DS3, NOTE_DS3, NOTE_REST, NOTE_DS3, NOTE_DS3, NOTE_F2, NOTE_F4, NOTE_F4, NOTE_F2, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_F4, NOTE_G2, NOTE_DS2, NOTE_D2, NOTE_C2, NOTE_C4, NOTE_DS3, NOTE_DS3, NOTE_AS2, NOTE_AS2, NOTE_C3, NOTE_C3, NOTE_DS3, NOTE_DS3, NOTE_REST, NOTE_DS3, NOTE_DS3, NOTE_REST, NOTE_DS3, NOTE_DS3, NOTE_F2, NOTE_F4, NOTE_F4, NOTE_F2, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_F4, NOTE_G2, NOTE_DS2, NOTE_D2, NOTE_C2, NOTE_C4, NOTE_F2, NOTE_F2, NOTE_GS2, NOTE_GS2, NOTE_C3, NOTE_C3, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_D4, NOTE_DS4, NOTE_DS4, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_F2, NOTE_F2, NOTE_GS2, NOTE_GS2, NOTE_C3, NOTE_C3, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_D4, NOTE_DS4, NOTE_DS4, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_GS2, NOTE_GS2, NOTE_G2, NOTE_G2, NOTE_F2, NOTE_F2, NOTE_DS4, NOTE_DS4, NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_DS2, NOTE_DS2, NOTE_D2, NOTE_D2, NOTE_C2, NOTE_C2, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_GS2, NOTE_GS2, NOTE_G2, NOTE_G2, NOTE_F2, NOTE_F2, NOTE_DS4, NOTE_DS4,  NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_DS3, NOTE_DS3, NOTE_AS2, NOTE_AS2, NOTE_C3, NOTE_C3, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4,  NOTE_GS2, NOTE_GS2, NOTE_G2, NOTE_G2, NOTE_F2, NOTE_F2, NOTE_DS4, NOTE_DS4, NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_DS2, NOTE_DS2, NOTE_D2, NOTE_D2, NOTE_C2, NOTE_C2, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_GS2, NOTE_GS2, NOTE_G2, NOTE_G2, NOTE_F2, NOTE_F2, NOTE_DS4, NOTE_DS4,  NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_REST, NOTE_DS4, NOTE_DS4, NOTE_DS3, NOTE_DS3, NOTE_AS2, NOTE_AS2, NOTE_C3, NOTE_C3, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_C4, NOTE_C4};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
const int noteDurations[] = { 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8,  8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 4, 8, 8};

unsigned char lightState; // The current state of the traffic lights, in the range [0, 5].

unsigned long previousMillis; // The time since we last changed the light.

int delayTime; // How long to wait before changing the light.

const int RED_TIME = 2500; // How long to stay at a red light.
const int YELLOW_TIME = 3000; // How long to stay at a yellow light.
const int GREEN_TIME = 5000; // How long to stay at a green light.

const int DOUBLE_RED = 13; // Output pin to the two red lights.
const int DOUBLE_YELLOW = 12; // Output pin to the two yellow lights.
const int DOUBLE_GREEN = 11; // Output pin to the two green lights.

const int SINGLE_RED = 10; // Output pin to the single red light.
const int SINGLE_YELLOW = 9; // Output pin to the single yellow light.
const int SINGLE_GREEN = 8; // Output pin to the single green light.

const int SERVO_CONTROL = 7; // The pin to control the servo.

const int STREET_LIGHT_PIN = 6; // The pin for the street light.

const int IR_OUTPUT = 5; // Pin for IR output.
const int IR_INPUT = A0; // Pin for IR input.

const int LDR_PIN = A1; // Pin for LDR input.

const int BUTTON_PIN = 4; // Pin for button input.

const int SPEAKER_PIN = 3; // Pin for the speaker.

Servo gate; // The gate servo.

struct TrafficLight singleLight; // The light that operates on its own.
struct TrafficLight doubleLight; // The two lights that operate together.

bool speedingUp; // If the button has been pressed during this state.

const int LIGHT_CUTOFF = 600; // Turn on the street light if the LDR reading exceeds this. This number was chosen based on empirical data.

// The setup function runs once when you press reset or power the board
void setup() {
	// Set the pins of the single light.
	singleLight.redPin = SINGLE_RED;
	singleLight.yellowPin = SINGLE_YELLOW;
	singleLight.greenPin = SINGLE_GREEN;

	// Set the pins of the double light.
	doubleLight.redPin = DOUBLE_RED;
	doubleLight.yellowPin = DOUBLE_YELLOW;
	doubleLight.greenPin = DOUBLE_GREEN;

	// Set the outputs to output mode.
	pinMode(doubleLight.redPin, OUTPUT);
	pinMode(doubleLight.yellowPin, OUTPUT);
	pinMode(doubleLight.greenPin, OUTPUT);
	pinMode(singleLight.redPin, OUTPUT);
	pinMode(singleLight.yellowPin, OUTPUT);
	pinMode(singleLight.greenPin, OUTPUT);
	pinMode(STREET_LIGHT_PIN, OUTPUT);
	pinMode(IR_OUTPUT, OUTPUT);

	// Set the inputs to input mode.
	pinMode(IR_INPUT, INPUT);
	pinMode(BUTTON_PIN, INPUT);

	// Set the variables to their inital values.
	lightState = 0;
	previousMillis = 0;
	delayTime = GREEN_TIME;
	speedingUp = false;

	// Turn off all of the lights at the start.
	digitalWrite(DOUBLE_RED, LOW);
	digitalWrite(DOUBLE_YELLOW, LOW);
	digitalWrite(DOUBLE_GREEN, LOW);
	digitalWrite(SINGLE_RED, LOW);
	digitalWrite(SINGLE_YELLOW, LOW);
	digitalWrite(SINGLE_GREEN, LOW);

	digitalWrite(IR_OUTPUT, HIGH);

	gate.attach(SERVO_CONTROL);
	gate.write(0);

	Serial.begin(9600);
	Serial.print(sizeof(melody));
}

// Returns if it's dark right now, based on the cutoff.
void updateStreetLight() {
	int lightLevel = analogRead(LDR_PIN);
	printSensorReading("LDR", lightLevel);
	if (lightLevel > LIGHT_CUTOFF) { // If it's dark.
		digitalWrite(STREET_LIGHT_PIN, HIGH);
		printPinSet(STREET_LIGHT_PIN, HIGH);
	} else { // If it's bright.
		digitalWrite(STREET_LIGHT_PIN, LOW);
		printPinSet(STREET_LIGHT_PIN, LOW);
	}
}

// Print that a given pin is being set to a given level.
void printPinSet(int pin, int level) {
	Serial.print("Set pin ");
	Serial.print(pin);
	Serial.print(" to ");
	Serial.print(level);
	Serial.println(".");
}

// Print the reading of a given sensor.
void printSensorReading(const char* sensor, int reading) {
	Serial.print(sensor);
	Serial.print(" reading is: ");
	Serial.println(reading);
}

// Set the specified light to the specified colour.
void setLight(TrafficLight light, enum lightColours colour) {
	digitalWrite(light.redPin, LOW);
	digitalWrite(light.yellowPin, LOW);
	digitalWrite(light.greenPin, LOW);

	printPinSet(light.redPin, LOW);
	printPinSet(light.yellowPin, LOW);
	printPinSet(light.greenPin, LOW);

	if (colour == RED) {
		digitalWrite(light.redPin, HIGH);
		printPinSet(light.redPin, HIGH);
	} else if (colour == YELLOW) {
		digitalWrite(light.yellowPin, HIGH);
		printPinSet(light.yellowPin, HIGH);
	} else {
		digitalWrite(light.greenPin, HIGH);
		printPinSet(light.greenPin, HIGH);
	}
}

/*
 * Update the traffic lights depending on the value of lightState.
 * Set delayTime to the appropriate amount for the lightState.
 * Reset lightState to 0 if it's greater than or equal to 5.
 */
void updateLights() {
	if (lightState == 0) {
		setLight(doubleLight, RED);
		setLight(singleLight, GREEN);
		delayTime = GREEN_TIME;
	} else if (lightState == 1) {
		setLight(doubleLight, RED);
		setLight(singleLight, YELLOW);
		delayTime = YELLOW_TIME;
	} else if (lightState == 2) {
		setLight(doubleLight, RED);
		setLight(singleLight, RED);
		delayTime = RED_TIME;
	} else if (lightState == 3) {
		setLight(doubleLight, GREEN);
		setLight(singleLight, RED);
		delayTime = GREEN_TIME;
	} else if (lightState == 4) {
		setLight(doubleLight, YELLOW);
		setLight(singleLight, RED);
		delayTime = YELLOW_TIME;
	} else {
		setLight(doubleLight, RED);
		setLight(singleLight, RED);
		delayTime = RED_TIME;
		lightState = 0;
	}
	if (speedingUp && lightState != 3) { // If we are speeding up and it's not time for the pedestrians to cross.
		delayTime /= 2; // Half the delay.
	} else {
		speedingUp = false; // Stop speeding up.
	}
}

// Return whether or not the button is down.
bool isButtonDown() {
	return digitalRead(BUTTON_PIN) == HIGH;
}

// Open the gate.
void openGate() {
	gate.write(90);
}

// Close the gate.
void closeGate() {
	gate.write(0);
}

// Read the IR sensor and update the gate accordingly.
void updateGate() {
	int irReading = analogRead(IR_INPUT);		
	printSensorReading("IR", irReading);
	if (irReading >= 1005) {
		openGate();
	} else {
		closeGate();
	}
}

// Play the next note in the song.
void updateMusic() {
	noTone(SPEAKER_PIN); // Ensure no tone is playing.

	if (currentNote >= (sizeof(melody) / sizeof(unsigned long))) // If we have reached the end of the song.
		currentNote = 0;

	int noteDuration = 1600 / noteDurations[currentNote];

	if (speedingUp) // If we are speeding up the lights, speed up the song.
		noteDuration /= 2;

	if (melody[currentNote] == NOTE_REST) { // If this note is a rest, don't play anything.
		noteEndTime = millis() + noteDuration * 1.30; // Set the time for when to play the next note to noteDuration + 30%.
	} else {
		tone(SPEAKER_PIN, melody[currentNote], noteDuration);
		noteEndTime = millis() + noteDuration * 1.30; // Set the time for when to play the next note to noteDuration + 30%.
	}
	currentNote++;
}


// The loop function runs over and over again forever
void loop() {
	unsigned long currentMillis = millis();
	if (isButtonDown() && !speedingUp) { // If the button has been pressed.
		speedingUp = true;
		if (lightState == 3) // If the pedestrians can cross.
			speedingUp = false; // Stop speeding up.
		else // If the pedestrians cannot cross.
			delayTime -= (delayTime - (currentMillis - previousMillis)) / 2; // Subtract half of the time remaining from the light.
	}

	if (currentMillis - previousMillis >= delayTime) {
		previousMillis = millis();
		lightState++;
		updateLights();
	}
	updateGate();
	updateStreetLight();
	
	if (millis() >= noteEndTime) {
		updateMusic();
	}
}
