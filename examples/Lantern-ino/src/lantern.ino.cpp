#include "Lantern.h"
#include "avr/power.h"

void buttonStateChangeISR();

Lantern lantern;

void setup() {

#ifdef SIMPLE_LOGGER_APPENDER_ENABLED
	Serial.begin(9600);
#else
	power_usart0_disable(); // 0.1 mA saved
#endif

	pinMode(BATTERY_SENSING_PIN, INPUT);
	pinMode(TEMPERATURE_SENSING_PIN, INPUT);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonStateChangeISR,
			CHANGE);

	lantern.setup();
}

void loop() {
	lantern.loop(WDTO_X);
}

void buttonStateChangeISR() {
	digitalRead(BUTTON_PIN) == LOW ?
			lantern.button.setState(ButtonState::PRESSED) :
			lantern.button.setState(ButtonState::RELEASED);
}
